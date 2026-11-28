/* Music on Android's own synthesizer (Sonivox): the .MID file played by
 * an android.media.MediaPlayer, driven through JNI from the game's
 * thread.  MediaPlayer plays the file to its end; a piece that ends
 * earlier is stopped when platform_music_ended finds play past its end
 * (it is asked with every round of input events), so it may sound a few
 * tens of milliseconds longer.  While the app is in the background (the
 * game's thread is held in SDL's event pump) the music is paused. */
#include <SDL3/SDL.h>
#include <jni.h>
#include <stdarg.h>

#include "platform/music.h"

static struct {
    jclass type;
    jmethodID create, set_data_source, prepare, seek_to, start, pause, position,
              is_playing, set_volume, release;
} jm;

static struct {
    jobject player;             /* a global reference */
    uint32_t to;                /* where play ends (0: the file's end) */
    int playing;
    int held;                   /* paused for the background */
} mp;

/* Clears a Java exception the last call threw: 1 if there was one. */
static int failed(JNIEnv *env)
{
    if (!(*env)->ExceptionCheck(env))
        return 0;
    (*env)->ExceptionDescribe(env);
    (*env)->ExceptionClear(env);
    return 1;
}

static int call(jmethodID method, ...)
{
    JNIEnv *env = SDL_GetAndroidJNIEnv();
    va_list args;

    va_start(args, method);
    (*env)->CallVoidMethodV(env, mp.player, method, args);
    va_end(args);
    return !failed(env);
}

static int call_int(jmethodID method)
{
    JNIEnv *env = SDL_GetAndroidJNIEnv();
    jint r = (*env)->CallIntMethod(env, mp.player, method);

    return failed(env) ? 0 : r;
}

static int call_bool(jmethodID method)
{
    JNIEnv *env = SDL_GetAndroidJNIEnv();
    jboolean r = (*env)->CallBooleanMethod(env, mp.player, method);

    return !failed(env) && r;
}

static int find_methods(JNIEnv *env)
{
    static const struct {
        jmethodID *id;
        const char *name, *signature;
    } methods[] = {
        {&jm.create, "<init>", "()V"},
        {&jm.set_data_source, "setDataSource", "(Ljava/lang/String;)V"},
        {&jm.prepare, "prepare", "()V"},
        {&jm.seek_to, "seekTo", "(I)V"},
        {&jm.start, "start", "()V"},
        {&jm.pause, "pause", "()V"},
        {&jm.position, "getCurrentPosition", "()I"},
        {&jm.is_playing, "isPlaying", "()Z"},
        {&jm.set_volume, "setVolume", "(FF)V"},
        {&jm.release, "release", "()V"},
    };
    jclass local;
    size_t i;

    if (jm.type)
        return 1;
    local = (*env)->FindClass(env, "android/media/MediaPlayer");
    if (failed(env) || !local)
        return 0;
    for (i = 0; i < SDL_arraysize(methods); i++) {
        *methods[i].id = (*env)->GetMethodID(env, local, methods[i].name, methods[i].signature);
        if (failed(env) || !*methods[i].id)
            return 0;
    }
    jm.type = (*env)->NewGlobalRef(env, local);
    (*env)->DeleteLocalRef(env, local);
    return jm.type != NULL;
}

/* Pauses the music while the app is in the background. */
static bool SDLCALL on_event(void *user, SDL_Event *e)
{
    (void)user;
    if (e->type == SDL_EVENT_DID_ENTER_BACKGROUND && mp.playing && !mp.held)
        mp.held = call(jm.pause);
    if (e->type == SDL_EVENT_DID_ENTER_FOREGROUND && mp.held)
        mp.held = !call(jm.start);
    return true;
}

static void android_close(void)
{
    JNIEnv *env = SDL_GetAndroidJNIEnv();

    if (!mp.player)
        return;
    SDL_RemoveEventWatch(on_event, NULL);
    call(jm.release);
    (*env)->DeleteGlobalRef(env, mp.player);
    SDL_zero(mp);
}

static int android_open(const char *path, const char *soundfont)
{
    JNIEnv *env = SDL_GetAndroidJNIEnv();
    jobject local;
    jstring jpath;
    int ok;

    (void)soundfont;
    SDL_zero(mp);
    if (!env || !find_methods(env))
        return 0;
    local = (*env)->NewObject(env, jm.type, jm.create);
    if (failed(env) || !local)
        return 0;
    mp.player = (*env)->NewGlobalRef(env, local);
    (*env)->DeleteLocalRef(env, local);
    jpath = (*env)->NewStringUTF(env, path);
    ok = jpath && call(jm.set_data_source, jpath) && call(jm.prepare);
    (*env)->DeleteLocalRef(env, jpath);
    SDL_AddEventWatch(on_event, NULL);
    if (!ok) {
        SDL_Log("music: MediaPlayer cannot play %s", path);
        android_close();
    }
    return ok;
}

static void android_play(uint32_t from, uint32_t to)
{
    if (from != PLATFORM_MUSIC_HERE)
        call(jm.seek_to, (jint)from);
    mp.to = to;
    mp.held = 0;
    mp.playing = call(jm.start);
}

static void android_pause(void)
{
    if (mp.playing && !mp.held)
        call(jm.pause);
    mp.playing = 0;
    mp.held = 0;
}

static int android_ended(void)
{
    if (!mp.playing || mp.held)
        return 0;
    if (call_bool(jm.is_playing) && (!mp.to || (uint32_t)call_int(jm.position) < mp.to))
        return 0;
    android_pause();
    return 1;
}

static void android_volume(uint16_t left, uint16_t right)
{
    call(jm.set_volume, (jfloat)(left / 65535.0), (jfloat)(right / 65535.0));
}

const MusicBackend music_android = {
    android_open, android_play, android_pause, android_ended, android_close, android_volume,
};
