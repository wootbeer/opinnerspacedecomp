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
    g_1d20.left = GetPrivateProfileInt(g_9690, "ShowLeft", 0, g_96a9);
    g_1d20.top = GetPrivateProfileInt(g_9690, "ShowTop", 0, g_96a9);
    g_1d20.right = GetPrivateProfileInt(g_9690, "ShowRight", 0, g_96a9);
    g_1d20.bottom = GetPrivateProfileInt(g_9690, "ShowBottom", 0, g_96a9);
    if (g_1d20.right <= 0) {
        w = GetSystemMetrics(SM_CXSCREEN) * 4 / 5;
        h = GetSystemMetrics(SM_CYSCREEN) * 4 / 5;
        g_1d20.left = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        g_1d20.top = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
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
    g_8f72 = GetPrivateProfileInt(g_9690, "IconWnd", 1, g_96a9);
    g_0b6e = GetPrivateProfileInt(g_9690, "VScale", 0, g_96a9);
    g_8f74 = GetPrivateProfileInt(g_9690, "SmWnd", 0, g_96a9);
    g_95f8 = GetPrivateProfileInt(g_9690, "SScale", 0, g_96a9);
    g_9298 = GetPrivateProfileInt(g_9690, "ShowLaunch", 2, g_96a9);
    g_90f6 = GetPrivateProfileInt(g_9690, "Menu", 0, g_96a9);
    g_1dd4 = GetPrivateProfileInt(g_9690, "RadarLeft", 0, g_96a9);
    g_1dd6 = GetPrivateProfileInt(g_9690, "RadarTop", 0, g_96a9);
    g_1ddc = GetPrivateProfileInt(g_9690, "WatchLeft", 0, g_96a9);
    g_1dde = GetPrivateProfileInt(g_9690, "WatchTop", 0, g_96a9);
    g_1de0 = GetPrivateProfileInt(g_9690, "WatchRight", g_1ddc + 280, g_96a9);
    g_1de4.left = GetPrivateProfileInt(g_9690, "IconLeft", GetSystemMetrics(SM_CXSCREEN) - 48, g_96a9);
    if (GetSystemMetrics(SM_CXSCREEN) - 10 < g_1de4.left)
        g_1de4.left = GetSystemMetrics(SM_CXSCREEN) - 10;
    g_1de4.top = GetPrivateProfileInt(g_9690, "IconTop", 0, g_96a9);
    g_1dec = GetPrivateProfileInt(g_9690, "SmLeft", 0, g_96a9);
    if (GetSystemMetrics(SM_CXSCREEN) - 10 < g_1dec)
        g_1dec = GetSystemMetrics(SM_CXSCREEN) - 10;
    g_1dee = GetPrivateProfileInt(g_9690, "SmTop", 0, g_96a9);
    g_1dc4 = GetPrivateProfileInt(g_9690, "HelpLeft", 0, g_96a9);
    g_1dc6 = GetPrivateProfileInt(g_9690, "HelpTop", 0, g_96a9);
}

/* Writes the window layout settings that changed to the INI file
 * [inferred]. */
/* 6:033e */
void fn_06_033e(void)
{
    char buf[12];

    SetCursor(LoadCursor(NULL, IDC_WAIT));
    fn_06_0f1a(g_0020, buf);
    WritePrivateProfileString(g_9690, "Full", buf, g_96a9);
    fn_06_0f1a(g_90f6, buf);
    WritePrivateProfileString(g_9690, "Menu", buf, g_96a9);
    if (g_012a) {
        fn_06_0f1a(g_1dd4, buf);
        WritePrivateProfileString(g_9690, "RadarLeft", buf, g_96a9);
        fn_06_0f1a(g_1dd6, buf);
        WritePrivateProfileString(g_9690, "RadarTop", buf, g_96a9);
    }
    if (g_8fea) {
        fn_06_0f1a(g_1ddc, buf);
        WritePrivateProfileString(g_9690, "WatchLeft", buf, g_96a9);
        fn_06_0f1a(g_1de0, buf);
        WritePrivateProfileString(g_9690, "WatchRight", buf, g_96a9);
        fn_06_0f1a(g_1dde, buf);
        WritePrivateProfileString(g_9690, "WatchTop", buf, g_96a9);
    }
    fn_06_0f1a(g_8f72, buf);
    WritePrivateProfileString(g_9690, "IconWnd", buf, g_96a9);
    fn_06_0f1a(g_0b6e, buf);
    WritePrivateProfileString(g_9690, "VScale", buf, g_96a9);
    fn_06_0f1a(g_8f74, buf);
    WritePrivateProfileString(g_9690, "SmWnd", buf, g_96a9);
    fn_06_0f1a(g_95f8, buf);
    WritePrivateProfileString(g_9690, "SScale", buf, g_96a9);
    if (g_8fee) {
        fn_06_0f1a(g_1de4.left, buf);
        WritePrivateProfileString(g_9690, "IconLeft", buf, g_96a9);
        fn_06_0f1a(g_1de4.top, buf);
        WritePrivateProfileString(g_9690, "IconTop", buf, g_96a9);
    }
    if (g_8ff0) {
        fn_06_0f1a(g_1dec, buf);
        WritePrivateProfileString(g_9690, "SmLeft", buf, g_96a9);
        fn_06_0f1a(g_1dee, buf);
        WritePrivateProfileString(g_9690, "SmTop", buf, g_96a9);
    }
    if (g_0128) {
        fn_06_0f1a(g_1dc4, buf);
        WritePrivateProfileString(g_9690, "HelpLeft", buf, g_96a9);
        fn_06_0f1a(g_1dc6, buf);
        WritePrivateProfileString(g_9690, "HelpTop", buf, g_96a9);
    }
    if (g_8f6a) {
        fn_06_0f1a(g_1d20.left, buf);
        WritePrivateProfileString(g_9690, "ShowLeft", buf, g_96a9);
        fn_06_0f1a(g_1d20.right, buf);
        WritePrivateProfileString(g_9690, "ShowRight", buf, g_96a9);
        fn_06_0f1a(g_1d20.top, buf);
        WritePrivateProfileString(g_9690, "ShowTop", buf, g_96a9);
        fn_06_0f1a(g_1d20.bottom, buf);
        WritePrivateProfileString(g_9690, "ShowBottom", buf, g_96a9);
    }
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    g_8ff0 = g_8fee = g_8fea = g_012a = g_012c = g_8f6a = g_0128 = 0;
}

/* 6:02ca */
void fn_06_02ca(void)
{
    SetClassWord(g_0016, GCW_HICON, LoadIcon(g_8e66, "GAME"));
    g_131a = GetPrivateProfileInt(g_9690, "Aux", 0, g_96a9);
    if (!g_90f8)
        g_8f70 = GetPrivateProfileInt(g_9690, "QuickIntro", 0, g_96a9);
    g_8fec = GetPrivateProfileInt(g_9690, "Rate", 0, g_96a9);
}

/* Reads the paths from INSPACE.INI; runs GRMSETUP.EXE when the INI is
 * missing, or regenerates it [inferred]. */
/* 6:06d8 */
int16_t fn_06_06d8(char *exe)
{
    int16_t i;
    char path[140];
    OFSTRUCT of;

    lstrcpy(g_96a9, "INSPACE.INI");
    GetPrivateProfileString(g_9690, "Path", "", g_8f7a, 109, g_96a9);
    GetPrivateProfileString(g_9690, "LocalPath", "", g_9078, 109, g_96a9);
    for (i = lstrlen(exe) - 1; i > 0; i--) {
        if (exe[i] == '\\')
            break;
        exe[i] = 0;
    }
    GetWindowsDirectory(path, 110);
    lstrcat(path, "\\");
    lstrcat(path, g_96a9);
    if (OpenFile(path, &of, OF_EXIST) == -1) {
        lstrcpy(path, exe);
        lstrcat(path, "GRMSETUP.EXE");
        if (OpenFile(path, &of, OF_EXIST) != -1) {
            WinExec(path, SW_SHOW);
            return 0;
        }
    }
    if (!g_8f7a[0]) {
        MessageBox(g_0016, "Some game settings are missing. Will attempt to regenerate INSPACE.INI. For best results, reinstall from installer.",
                   g_9690, MB_ICONEXCLAMATION);
        lstrcpy(g_8f7a, exe);
        WritePrivateProfileString(g_9690, "Path", g_8f7a, g_96a9);
        lstrcpy(path, g_8f7a);
        lstrcpy(g_9078, g_8f7a);
        WritePrivateProfileString(g_9690, "LocalPath", g_9078, g_96a9);
        lstrcat(path, "SHIPS\\");
        WritePrivateProfileString(g_9690, "ShipPath", path, g_96a9);
        lstrcpy(path, g_8f7a);
        lstrcat(path, "SOUNDS\\");
        WritePrivateProfileString(g_9690, "SndPath", path, g_96a9);
        lstrcpy(path, g_8f7a);
        lstrcat(path, "GAMES\\");
        WritePrivateProfileString(g_9690, "RacePath", path, g_96a9);
        WritePrivateProfileString(g_9690, "Dead", "RETIRED", g_96a9);
        WritePrivateProfileString(g_9690, "Games", "GAMES", g_96a9);
        WritePrivateProfileString(g_9690, "Language", "ENG", g_96a9);
        WritePrivateProfileString(g_9690, "MainShip", "TRANSFORMER", g_96a9);
        WritePrivateProfileString(g_9690, "ThePlayer", "your name", g_96a9);
    }
    if (g_8f7a[lstrlen(g_8f7a) - 1] != '\\')
        lstrcat(g_8f7a, "\\");
    GetPrivateProfileString(g_9690, "Dead", "", g_96c5, 11, g_96a9);
    lstrcat(g_96c5, "\\");
    GetPrivateProfileString(g_9690, "Games", "", g_96b8, 11, g_96a9);
    lstrcat(g_96b8, "\\");
    GetPrivateProfileString(g_9690, "RacePath", "", g_900a, 109, g_96a9);
    if (g_900a[lstrlen(g_900a) - 1] != '\\')
        lstrcat(g_900a, "\\");
    return 1;
}

/* 6:09f8 */
int16_t fn_06_09f8(void)
{
    if (!SetTimer(g_0016, 1, 1000, NULL)) {
        fn_02_094c(0x844);
        MessageBox(g_0016, g_8e68, g_9690, MB_ICONEXCLAMATION);
        PostMessage(g_0016, WM_DESTROY, 0, 0L);
        return 0;
    }
    SetClassWord(g_0016, GCW_HICON, LoadIcon(g_8e66, "GAME"));
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
    g_9156 = GetPrivateProfileInt(g_9690, "Size", 1, g_96a9);
    g_9150 = 4 - g_9156;
    g_9152 = g_9154;
    fn_06_0f1a(g_8ffc, buf);
    WritePrivateProfileString(g_9690, "Calibrate", buf, g_96a9);
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

    g_8ffa = GetPrivateProfileInt(g_9690, "GameSpeed", 20000, g_96a9);
    if (g_8ffa == 20000)
        g_8ffa = g_8ffc;
    g_059c = GetPrivateProfileInt(g_9690, "FrameRateSet", 36, g_96a9);
    g_059e = g_059c / 4;
    g_05c4 = 1000 / g_059c;
    i = 10000 / g_059c;
    r = i % 10;
    if (r > 4)
        g_05c4++;
    g_05c8 = g_05c4 - 1;
    for (i = 0; i < 4; i++) {
        lstrcpy(key, "JBtn");
        fn_06_0f1a(i, num);
        lstrcat(key, num);
        g_1dcc[i] = GetPrivateProfileInt(g_9690, key, i, g_96a9);
    }
    g_8ff4 = GetPrivateProfileInt(g_9690, "JoyStick", 0, g_96a9);
    g_931e = GetPrivateProfileInt(g_9690, "Quick", 0, g_96a9);
    g_9208 = GetPrivateProfileInt(g_9690, "Detail", 3, g_96a9);
    g_8fe8 = GetPrivateProfileInt(g_9690, "Enhance", 1, g_96a9);
    g_920a = GetPrivateProfileInt(g_9690, "MixChannels", x = 1, g_96a9);
    if (!g_90f8)
        g_8f70 = GetPrivateProfileInt(g_9690, "QuickIntro", 0, g_96a9);
    g_0742 = GetPrivateProfileInt(g_9690, "BadVideo", 1, g_96a9);
    fn_06_11ec();
    g_8ff6 = GetPrivateProfileInt(g_9690, "Braking", 0, g_96a9);
    g_131c = GetPrivateProfileInt(g_9690, "ShipAnim", 1, g_96a9);
    border = GetPrivateProfileInt(g_9690, "Border", 1, g_96a9);
    menu = GetPrivateProfileInt(g_9690, "Menu", 0, g_96a9);
    if (border != g_0a78 || menu != g_90f6) {
        g_0a78 = border;
        if (g_90f6 = menu)
            SetWindowWord(g_0016, GWW_ID, g_90fa);
        else
            SetWindowWord(g_0016, GWW_ID, 0);
        DrawMenuBar(g_0016);
        g_1d4a = 0x244;
        g_1038 = 1;
        PostMessage(g_0016, WM_PAINT, 0, 0L);
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
    v = GetPrivateProfileInt(g_9690, "Bright", 0, g_96a9);
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
    g_8ff8 = GetPrivateProfileInt(g_9690, "Complex", 0, g_96a9);
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
    return GetPrivateProfileInt(g_9690, key, def, g_96a9);
}
