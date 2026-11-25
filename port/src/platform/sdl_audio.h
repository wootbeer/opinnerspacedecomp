/* Inside the SDL platform: the audio device that the effects and the
 * music (music_tsf.c) play into, each through an SDL audio stream bound
 * to it, mixed by SDL. */
#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include <SDL3/SDL_audio.h>

/* Opened on first use; 0 when there is no sound device. */
SDL_AudioDeviceID platform_sdl_audio_device(void);

#endif
