/* INSPACE.EXE segment 6 (selector 1028): 6:0000-6:12b6, one source file
 * (6:12b6-6:1c72 is in seg06c.c, 6:1c72-6:5d58 in seg06d.c, the rest,
 * compiled with /G2, in seg06b.c). */
#include "game.h"

/* Reads the window layout settings from the INI file [inferred]. */
/* 6:0000 */
void fn_06_0000(void)
{
    int16_t d;
    int16_t h;
    int16_t w;

    g_0020 = fn_06_1290("Full", 1);
    g_1d20.left = GetPrivateProfileInt(app_name, "ShowLeft", 0, ini_name);
    g_1d20.top = GetPrivateProfileInt(app_name, "ShowTop", 0, ini_name);
    g_1d20.right = GetPrivateProfileInt(app_name, "ShowRight", 0, ini_name);
    g_1d20.bottom = GetPrivateProfileInt(app_name, "ShowBottom", 0, ini_name);
    if (g_1d20.right <= 0) {
        w = (int16_t)(GetSystemMetrics(SM_CXSCREEN) * 4) / 5;
        h = (int16_t)(GetSystemMetrics(SM_CYSCREEN) * 4) / 5;
        g_1d20.left = (int16_t)(GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        g_1d20.top = (int16_t)(GetSystemMetrics(SM_CYSCREEN) - h) / 2;
        g_1d20.right = w + g_1d20.left;
        g_1d20.bottom = h + g_1d20.top;
    }
    if ((d = GetSystemMetrics(SM_CXSCREEN) - g_1d20.right) < 0) {
        g_1d20.right += d;
        g_1d20.left += d;
    }
    if ((d = GetSystemMetrics(SM_CYSCREEN) - g_1d20.bottom) < 0) {
        g_1d20.bottom += d;
        g_1d20.bottom += d;
    }
    g_8f72 = GetPrivateProfileInt(app_name, "IconWnd", 1, ini_name);
    g_0b6e = GetPrivateProfileInt(app_name, "VScale", 0, ini_name);
    g_8f74 = GetPrivateProfileInt(app_name, "SmWnd", 0, ini_name);
    g_95f8 = GetPrivateProfileInt(app_name, "SScale", 0, ini_name);
    g_9298 = GetPrivateProfileInt(app_name, "ShowLaunch", 2, ini_name);
    g_90f6 = GetPrivateProfileInt(app_name, "Menu", 0, ini_name);
    g_1dd4 = GetPrivateProfileInt(app_name, "RadarLeft", 0, ini_name);
    g_1dd6 = GetPrivateProfileInt(app_name, "RadarTop", 0, ini_name);
    g_1ddc = GetPrivateProfileInt(app_name, "WatchLeft", 0, ini_name);
    g_1dde = GetPrivateProfileInt(app_name, "WatchTop", 0, ini_name);
    g_1de0 = GetPrivateProfileInt(app_name, "WatchRight", g_1ddc + 280, ini_name);
    g_1de4.left = GetPrivateProfileInt(app_name, "IconLeft", GetSystemMetrics(SM_CXSCREEN) - 48, ini_name);
    if (GetSystemMetrics(SM_CXSCREEN) - 10 < g_1de4.left)
        g_1de4.left = GetSystemMetrics(SM_CXSCREEN) - 10;
    g_1de4.top = GetPrivateProfileInt(app_name, "IconTop", 0, ini_name);
    g_1dec = GetPrivateProfileInt(app_name, "SmLeft", 0, ini_name);
    if (GetSystemMetrics(SM_CXSCREEN) - 10 < g_1dec)
        g_1dec = GetSystemMetrics(SM_CXSCREEN) - 10;
    g_1dee = GetPrivateProfileInt(app_name, "SmTop", 0, ini_name);
    g_1dc4 = GetPrivateProfileInt(app_name, "HelpLeft", 0, ini_name);
    g_1dc6 = GetPrivateProfileInt(app_name, "HelpTop", 0, ini_name);
}

/* Writes the window layout settings that changed to the INI file
 * [inferred]. */
/* 6:033e */
void fn_06_033e(void)
{
    char buf[12];

    SetCursor(LoadCursor(NULL, IDC_WAIT));
    fn_06_0f1a(g_0020, buf);
    WritePrivateProfileString(app_name, "Full", buf, ini_name);
    fn_06_0f1a(g_90f6, buf);
    WritePrivateProfileString(app_name, "Menu", buf, ini_name);
    if (g_012a) {
        fn_06_0f1a(g_1dd4, buf);
        WritePrivateProfileString(app_name, "RadarLeft", buf, ini_name);
        fn_06_0f1a(g_1dd6, buf);
        WritePrivateProfileString(app_name, "RadarTop", buf, ini_name);
    }
    if (g_8fea) {
        fn_06_0f1a(g_1ddc, buf);
        WritePrivateProfileString(app_name, "WatchLeft", buf, ini_name);
        fn_06_0f1a(g_1de0, buf);
        WritePrivateProfileString(app_name, "WatchRight", buf, ini_name);
        fn_06_0f1a(g_1dde, buf);
        WritePrivateProfileString(app_name, "WatchTop", buf, ini_name);
    }
    fn_06_0f1a(g_8f72, buf);
    WritePrivateProfileString(app_name, "IconWnd", buf, ini_name);
    fn_06_0f1a(g_0b6e, buf);
    WritePrivateProfileString(app_name, "VScale", buf, ini_name);
    fn_06_0f1a(g_8f74, buf);
    WritePrivateProfileString(app_name, "SmWnd", buf, ini_name);
    fn_06_0f1a(g_95f8, buf);
    WritePrivateProfileString(app_name, "SScale", buf, ini_name);
    if (g_8fee) {
        fn_06_0f1a(g_1de4.left, buf);
        WritePrivateProfileString(app_name, "IconLeft", buf, ini_name);
        fn_06_0f1a(g_1de4.top, buf);
        WritePrivateProfileString(app_name, "IconTop", buf, ini_name);
    }
    if (g_8ff0) {
        fn_06_0f1a(g_1dec, buf);
        WritePrivateProfileString(app_name, "SmLeft", buf, ini_name);
        fn_06_0f1a(g_1dee, buf);
        WritePrivateProfileString(app_name, "SmTop", buf, ini_name);
    }
    if (g_0128) {
        fn_06_0f1a(g_1dc4, buf);
        WritePrivateProfileString(app_name, "HelpLeft", buf, ini_name);
        fn_06_0f1a(g_1dc6, buf);
        WritePrivateProfileString(app_name, "HelpTop", buf, ini_name);
    }
    if (g_8f6a) {
        fn_06_0f1a(g_1d20.left, buf);
        WritePrivateProfileString(app_name, "ShowLeft", buf, ini_name);
        fn_06_0f1a(g_1d20.right, buf);
        WritePrivateProfileString(app_name, "ShowRight", buf, ini_name);
        fn_06_0f1a(g_1d20.top, buf);
        WritePrivateProfileString(app_name, "ShowTop", buf, ini_name);
        fn_06_0f1a(g_1d20.bottom, buf);
        WritePrivateProfileString(app_name, "ShowBottom", buf, ini_name);
    }
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    g_8ff0 = g_8fee = g_8fea = g_012a = g_012c = g_8f6a = g_0128 = 0;
}

/* 6:02ca */
void fn_06_02ca(void)
{
    SetClassWord(main_window, GCW_HICON, LoadIcon(g_8e66, "GAME"));
    g_131a = GetPrivateProfileInt(app_name, "Aux", 0, ini_name);
    if (!g_90f8)
        g_8f70 = GetPrivateProfileInt(app_name, "QuickIntro", 0, ini_name);
    g_8fec = GetPrivateProfileInt(app_name, "Rate", 0, ini_name);
}

/* Reads the paths from INSPACE.INI; runs GRMSETUP.EXE when the INI is
 * missing, or regenerates it [inferred]. */
/* 6:06d8 */
int16_t fn_06_06d8(char *exe)
{
    int16_t i;
    char path[140];
    OFSTRUCT of;

    lstrcpy(ini_name, "INSPACE.INI");
    GetPrivateProfileString(app_name, "Path", "", g_8f7a, 109, ini_name);
    GetPrivateProfileString(app_name, "LocalPath", "", g_9078, 109, ini_name);
    for (i = lstrlen(exe) - 1; i > 0; i--) {
        if (exe[i] == '\\')
            break;
        exe[i] = 0;
    }
    GetWindowsDirectory(path, 110);
    lstrcat(path, "\\");
    lstrcat(path, ini_name);
    if (OpenFile(path, &of, OF_EXIST) == -1) {
        lstrcpy(path, exe);
        lstrcat(path, "GRMSETUP.EXE");
        if (OpenFile(path, &of, OF_EXIST) != -1) {
            WinExec(path, SW_SHOW);
            return 0;
        }
    }
    if (!g_8f7a[0]) {
        MessageBox(main_window, "Some game settings are missing. Will attempt to regenerate INSPACE.INI. For best results, reinstall from installer.",
                   app_name, MB_ICONEXCLAMATION);
        lstrcpy(g_8f7a, exe);
        WritePrivateProfileString(app_name, "Path", g_8f7a, ini_name);
        lstrcpy(path, g_8f7a);
        lstrcpy(g_9078, g_8f7a);
        WritePrivateProfileString(app_name, "LocalPath", g_9078, ini_name);
        lstrcat(path, "SHIPS\\");
        WritePrivateProfileString(app_name, "ShipPath", path, ini_name);
        lstrcpy(path, g_8f7a);
        lstrcat(path, "SOUNDS\\");
        WritePrivateProfileString(app_name, "SndPath", path, ini_name);
        lstrcpy(path, g_8f7a);
        lstrcat(path, "GAMES\\");
        WritePrivateProfileString(app_name, "RacePath", path, ini_name);
        WritePrivateProfileString(app_name, "Dead", "RETIRED", ini_name);
        WritePrivateProfileString(app_name, "Games", "GAMES", ini_name);
        WritePrivateProfileString(app_name, "Language", "ENG", ini_name);
        WritePrivateProfileString(app_name, "MainShip", "TRANSFORMER", ini_name);
        WritePrivateProfileString(app_name, "ThePlayer", "your name", ini_name);
    }
    if (g_8f7a[lstrlen(g_8f7a) - 1] != '\\')
        lstrcat(g_8f7a, "\\");
    GetPrivateProfileString(app_name, "Dead", "", g_96c5, 11, ini_name);
    lstrcat(g_96c5, "\\");
    GetPrivateProfileString(app_name, "Games", "", g_96b8, 11, ini_name);
    lstrcat(g_96b8, "\\");
    GetPrivateProfileString(app_name, "RacePath", "", g_900a, 109, ini_name);
    if (g_900a[lstrlen(g_900a) - 1] != '\\')
        lstrcat(g_900a, "\\");
    return 1;
}

/* 6:09f8 */
int16_t fn_06_09f8(void)
{
    if (!SetTimer(main_window, 1, 1000, NULL)) {
        fn_02_094c(0x844);
        MessageBox(main_window, g_8e68, app_name, MB_ICONEXCLAMATION);
        PostMessage(main_window, WM_DESTROY, 0, 0L);
        return 0;
    }
    SetClassWord(main_window, GCW_HICON, LoadIcon(g_8e66, "GAME"));
    return 1;
}

/* 6:0a6c */
void fn_06_0a6c(void)
{
    char buf[10];

    g_8ffc = g_8ffa;
    if (g_8ffc > 1200)
        g_9004 = g_8ffc / 50;
    else if (g_8ffc > 850)
        g_9004 = g_8ffc / 150;
    else
        g_9004 = 0;
    g_9002 = g_9004;
    g_9006 = 10;
    if (g_8ffc > 360)
        g_9006 = g_8ffc / 38;
    else
        g_9006 = 7;
    g_9006 = min(g_9006, 10);
    g_9006 = max(g_9006, 7);
    fn_06_0b3e();
    g_9156 = GetPrivateProfileInt(app_name, "Size", 1, ini_name);
    g_9150 = 4 - g_9156;
    g_9152 = g_9154;
    fn_06_0f1a(g_8ffc, buf);
    WritePrivateProfileString(app_name, "Calibrate", buf, ini_name);
}

/* Reads the game settings from the INI file [inferred]. */
/* 6:0b3e */
void fn_06_0b3e(void)
{
    int16_t i;
    int16_t r;
    int16_t x;
    int16_t unused;
    int16_t border;
    int16_t menu;
    char key[148];
    char num[20];
    int16_t unused2;

    g_8ffa = GetPrivateProfileInt(app_name, "GameSpeed", 20000, ini_name);
    if (g_8ffa == 20000)
        g_8ffa = g_8ffc;
    frame_rate = GetPrivateProfileInt(app_name, "FrameRateSet", 36, ini_name);
    g_059e = frame_rate / 4;
    frame_ms = 1000 / frame_rate;
    i = 10000 / frame_rate;
    r = i % 10;
    if (r > 4)
        frame_ms++;
    frame_min_ms = frame_ms - 1;
    for (i = 0; i < 4; i++) {
        lstrcpy(key, "JBtn");
        fn_06_0f1a(i, num);
        lstrcat(key, num);
        g_1dcc[i] = GetPrivateProfileInt(app_name, key, i, ini_name);
    }
    g_8ff4 = GetPrivateProfileInt(app_name, "JoyStick", 0, ini_name);
    g_931e = GetPrivateProfileInt(app_name, "Quick", 0, ini_name);
    g_9208 = GetPrivateProfileInt(app_name, "Detail", 3, ini_name);
    g_8fe8 = GetPrivateProfileInt(app_name, "Enhance", 1, ini_name);
    g_920a = GetPrivateProfileInt(app_name, "MixChannels", x = 1, ini_name);
    if (!g_90f8)
        g_8f70 = GetPrivateProfileInt(app_name, "QuickIntro", 0, ini_name);
    g_0742 = GetPrivateProfileInt(app_name, "BadVideo", 1, ini_name);
    fn_06_11ec();
    g_8ff6 = GetPrivateProfileInt(app_name, "Braking", 0, ini_name);
    g_131c = GetPrivateProfileInt(app_name, "ShipAnim", 1, ini_name);
    border = GetPrivateProfileInt(app_name, "Border", 1, ini_name);
    menu = GetPrivateProfileInt(app_name, "Menu", 0, ini_name);
    if (border != g_0a78 || menu != g_90f6) {
        g_0a78 = border;
        if (g_90f6 = menu)
            SetWindowWord(main_window, GWW_ID, g_90fa);
        else
            SetWindowWord(main_window, GWW_ID, 0);
        DrawMenuBar(main_window);
        g_1d4a = 0x244;
        g_1038 = 1;
        PostMessage(main_window, WM_PAINT, 0, 0L);
    }
    fn_06_0daa();
}

/* 6:0daa */
void fn_06_0daa(void)
{
    int16_t v;

    if (g_8ffc > 600) {
        g_1df4 = 120;
        g_8f76 = g_8ffa / 28;
    } else if (g_8ffc > 500) {
        g_1df4 = 130;
        g_8f76 = g_8ffa / 80;
    } else if (g_8ffc > 250) {
        g_1df4 = 140;
        g_8f76 = g_8ffa / 80;
    } else {
        g_1df4 = 150;
        g_8f76 = 0;
    }
    g_9008 = min(g_8ffa / 65, 26);
    g_9008 = max(g_9008, 11);
    g_9008 = 4;
    switch (g_9208) {
    case 0:
        g_9154 = 4;
        g_8ffe = 3;
        break;
    case 1:
        g_9154 = 7;
        g_8ffe = 2;
        break;
    case 2:
        g_9154 = 13;
        g_8ffe = 1;
        break;
    case 3:
        g_9154 = 18;
        g_8ffe = 1;
        break;
    }
    v = GetPrivateProfileInt(app_name, "Bright", 0, ini_name);
    if (v)
        g_9154--;
    if (v != g_8ff2) {
        g_8ff2 = v;
        fn_10_4dfe();
    }
    g_8f78 = g_8f76;
}

/* 6:0eb8 */
void fn_06_0eb8(int32_t v, char *buf)
{
    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    fn_06_10ce(v, buf);
}

/* 6:0ef8 */
void fn_06_0ef8(uint32_t v, char *buf)
{
    buf[0] = 0;
    fn_06_10ce(v, buf);
}

/* 6:10aa */
void fn_06_10aa(uint16_t v, char *buf)
{
    buf[0] = 0;
    fn_06_10ce(v, buf);
}

/* 6:0f1a */
void fn_06_0f1a(int16_t v, char *buf)
{
    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    fn_06_10ce(v, buf);
}

/* Formats v / div as "int.frac", the fraction cut to width digits [inferred]. */
/* Long version of fn_06_1010 [inferred]. */
/* 6:0f54 */
void fn_06_0f54(int32_t v, int16_t div, int16_t width, char *buf)
{
    char tmp[16];
    int32_t r;

    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    tmp[0] = 0;
    fn_06_10ce(v / div, tmp);
    lstrcat(buf, tmp);
    lstrcat(buf, ".");
    tmp[0] = 0;
    r = v % div;
    fn_06_10ce(r, tmp);
    tmp[width] = 0;
    lstrcat(buf, tmp);
}

/* 6:1010 */
void fn_06_1010(int16_t v, int16_t div, int16_t width, char *buf)
{
    char tmp[16];
    int16_t r;

    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    tmp[0] = 0;
    fn_06_10ce(v / div, tmp);
    lstrcat(buf, tmp);
    lstrcat(buf, ".");
    tmp[0] = 0;
    r = v % div;
    fn_06_10ce(r, tmp);
    tmp[width] = 0;
    lstrcat(buf, tmp);
}

/* Appends the decimal digits of v to buf (after a "-" already there).
 * Quirk: exactly 1000000000 counts as 9 digits. [inferred] */
/* 6:10ce */
void fn_06_10ce(uint32_t v, char *buf)
{
    int16_t unused1;
    int16_t unused2;
    int16_t i;
    int16_t pos;
    int16_t n;
    int16_t off;

    if (buf[0])
        off = 1;
    else
        off = 0;
    if (v > 1000000000)
        n = 10;
    else if (v >= 100000000)
        n = 9;
    else if (v >= 10000000)
        n = 8;
    else if (v >= 1000000)
        n = 7;
    else if (v >= 100000)
        n = 6;
    else if (v >= 10000)
        n = 5;
    else if (v >= 1000)
        n = 4;
    else if (v >= 100)
        n = 3;
    else if (v >= 10)
        n = 2;
    else
        n = 1;
    buf[off + n] = 0;
    pos = n + off - 1;
    for (i = 0; i < n; i++, pos--) {
        buf[pos] = (char)(v % 10) + '0';
        v /= 10;
    }
}

/* 6:11ec */
void fn_06_11ec(void)
{
    g_8ff8 = GetPrivateProfileInt(app_name, "Complex", 0, ini_name);
    switch (g_8ff8) {
    case 0:
        g_932a = 130;
        g_9000 = 0;
        break;
    case 1:
        g_932a = 220;
        g_9000 = 0;
        break;
    case 2:
        g_932a = 310;
        g_9000 = 1;
        break;
    case 3:
        g_932a = 420;
        g_9000 = 2;
        break;
    case 4:
        g_932a = 2000;
        g_9000 = 2;
        break;
    }
    if (g_91f8 < 10)
        g_932a = min(g_932a / 2 + g_91f8 * g_932a / 20, g_932a);
}

/* 6:1290 */
int16_t fn_06_1290(LPCSTR key, int16_t def)
{
    return GetPrivateProfileInt(app_name, key, def, ini_name);
}
