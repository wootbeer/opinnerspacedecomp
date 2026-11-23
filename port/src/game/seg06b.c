/* INSPACE.EXE segment 6 (selector 1028), the part compiled with /G2
 * (6:5d58 onwards has no 32-bit instructions). */
#include "game.h"

                                 

/* 6:626c */
void fn_06_626c(void)
{
    fn_06_7266();
    fn_06_717a();
    if (g_94d8) {
        if (g_6b04) {
            GlobalUnlock(g_94d8);
            g_6b04 = 0;
        }
        GlobalFree(g_94d8);
        g_94d8 = 0;
    }
}

/* 6:717a */
void fn_06_717a(void)
{
    if (g_94de) {
        GlobalUnlock(g_94de);
        GlobalFree(g_94de);
        g_94de = 0;
        g_6af8 = 0;
    }
}

/* Sine of an angle in degrees, from the quarter-wave table [inferred]. */
/* 6:71b2 */
int16_t fn_06_71b2(int16_t deg)
{
    int16_t d;

    d = (deg + 360) % 360;
    if (d < 90)
        return g_0f00[d];
    if (d < 180)
        return g_0f00[180 - d];
    if (d < 270)
        return -g_0f00[d - 180];
    return -g_0f00[360 - d];
}

/* Cosine of an angle in degrees [inferred]. */
/* 6:720c */
int16_t fn_06_720c(int16_t deg)
{
    int16_t d;

    d = (deg + 360) % 360;
    if (d < 90)
        return g_0f00[90 - d];
    if (d < 180)
        return -g_0f00[d - 90];
    if (d < 270)
        return -g_0f00[270 - d];
    return g_0f00[d - 270];
}

/* 6:72d8 */
void fn_06_72d8(int16_t n, int16_t m)
{
    int16_t i;

    fn_06_7266();
    g_94ce = n;
    g_94d0 = m;
    switch (g_9208) {
    case 0:
        g_94d2 = 7;
        g_94d4 = 7;
        g_94d6 = 5;
        break;
    case 1:
        g_94d2 = 7;
        g_94d4 = 10;
        g_94d6 = 5;
        break;
    case 2:
        g_94d2 = 8;
        g_94d4 = 13;
        g_94d6 = 6;
        break;
    case 3:
        g_94d2 = 10;
        g_94d4 = 15;
        g_94d6 = 6;
        break;
    }
    g_94da = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (int32_t)g_94ce * 0x229);
    g_6b08 = (REC_229 *)GlobalLock(g_94da);
    g_94dc = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (int32_t)g_94d0 * 0x4b0);
    g_6b0c = (REC_4B0 *)GlobalLock(g_94dc);
    for (i = 0; i < g_94d0; i++)
        g_6b0c[i].b[0] = 0;
    for (i = 0; i < g_94ce; i++)
        g_6b08[i].f_002 = 0;
    g_9330 = 0;
}

/* 6:7266 */
void fn_06_7266(void)
{
    if (g_94da) {
        if (g_6b08) {
            GlobalUnlock(g_94da);
            g_6b08 = 0;
        }
        GlobalFree(g_94da);
        g_94da = 0;
    }
    if (g_94dc) {
        if (g_6b0c) {
            GlobalUnlock(g_94dc);
            g_6b0c = 0;
        }
        GlobalFree(g_94dc);
        g_94dc = 0;
    }
}

/* 6:8eb4 */
void fn_06_8eb4(void)
{
    if (g_94e0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
        g_6afc = 0;
        g_94e0 = 0;
    }
}

/* 6:92b8 */
int16_t fn_06_92b8(void)
{
    char path[110];
    OFSTRUCT of;

    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    lstrcat(path, "demogame.sav");
    return OpenFile(path, &of, 0x200);
}

/* 6:9932 */
void fn_06_9932(HGLOBAL h, HFILE f, int16_t keep)
{
    _lclose(f);
    if (h) {
        GlobalUnlock(h);
        GlobalFree(h);
    }
    if (!keep) {
        if (g_94ae) {
            GlobalUnlock(g_94ae);
            GlobalFree(g_94ae);
            g_94ae = 0;
            g_69f4 = 0;
        }
        if (g_95a4) {
            GlobalUnlock(g_95a4);
            GlobalFree(g_95a4);
            g_95a4 = 0;
            g_6e24 = 0;
        }
    }
}

/* Writes n bytes in chunks of 0x7fff; returns n, or 0 on error [inferred]. */
/* 6:9e66 */
DWORD fn_06_9e66(HFILE f, char *buf, DWORD n)
{
    DWORD total;
    char *p;

    total = n;
    p = buf;
    while (n > 0x7fff) {
        if (_lwrite(f, (LPCSTR)p, 0x7fff) != 0x7fff)
            return 0;
        n -= 0x7fff;
        p += 0x7fff;
    }
    if (_lwrite(f, (LPCSTR)p, (UINT)n) != (UINT)n)
        return 0;
    return total;
}

/* 6:73d6 */
void fn_06_73d6(int16_t i)
{
    g_6b0c[i].b[0] = 0;
}

/* Reads the "Complex" setting and sets the difficulty values [inferred]. */

/* Saves the race data to <dir><name>.rac [inferred]. */
/* 6:8dfe */
int16_t fn_06_8dfe(int16_t i)
{
    int16_t unused1;
    int16_t unused2;
    HFILE hf;
    DWORD size;
    char path[114];
    OFSTRUCT of;
    char unused3[10];

    lstrcpy(path, g_900a);
    lstrcat(path, g_a12c[i]);
    lstrcat(path, ".rac");
    hf = OpenFile(path, &of, OF_CREATE | OF_READWRITE);
    if (hf == -1)
        return 0;
    size = g_94c8 * 0x42;
    if (fn_06_9e66(hf, (char *)g_6afc, size) == 0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
        g_94e0 = 0;
        _lclose(hf);
        return 0;
    }
    _lclose(hf);
    hf = 0;
    return 1;
}

/* Returns 1 when the file is missing or does not start with the
 * expected signature g_939a [inferred]. */
/* 6:8776 */
int16_t fn_06_8776(LPSTR path)
{
    OFSTRUCT of;
    HGLOBAL h;
    int32_t *p;
    int16_t r;
    DWORD size;
    HFILE hf;

    hf = OpenFile(path, &of, OF_READ);
    if (hf == -1)
        return 1;
    h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1a9L);
    GlobalLock(h);
    size = GlobalSize(h);
    GlobalUnlock(h);
    if (fn_14_4006(hf, (char *)(p = (int32_t *)GlobalLock(h = GlobalReAlloc(h, size, GMEM_MOVEABLE | GMEM_ZEROINIT))), size) == 0)
        r = 1;
    else {
        r = 0;
        if (*p == g_939a)
            r = 1;
    }
    GlobalUnlock(h);
    GlobalFree(h);
    _lclose(hf);
    return r;
}

/* 6:8684 */
void fn_06_8684(int16_t i, int16_t j)
{
    g_6b08[i].f_049[j] = g_6b08[i].f_013;
    g_6b08[i].f_085[j] = g_6b08[i].f_017;
    g_6b08[i].f_0c1[j] = rand() % 1024 - (g_6b08[i].f_01b >> 2) - 512;
    g_6b08[i].f_0fd[j] = rand() % 1024 - (g_6b08[i].f_01f >> 2) - 512;
    g_6b08[i].f_02b[j] = 0;
}

/* Loads the race data from <dir><name>.rac [inferred]. */
/* 6:8b90 */
int16_t fn_06_8b90(int16_t i)
{
    int16_t unused1;
    int16_t unused2;
    HFILE hf;
    DWORD size;
    char path[114];
    char unused4[20];
    OFSTRUCT of;
    char unused3[10];

    lstrcpy(path, g_900a);
    lstrcat(path, g_a12c[i]);
    lstrcat(path, ".rac");
    hf = OpenFile(path, &of, OF_READ);
    if (hf != -1) {
        size = _filelength(hf);
        g_94c8 = size / 0x42;
        size = g_94c8 * 0x42;
    } else {
        g_94c8 = 0;
        size = 0x42;
    }
    if (g_94e0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
    }
    g_94e0 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
    g_6afc = (REC_42 *)GlobalLock(g_94e0);
    if (!g_94e0)
        return 0;
    if (hf != -1) {
        if (fn_14_4006(hf, (char *)g_6afc, size) == 0) {
            GlobalUnlock(g_94e0);
            GlobalFree(g_94e0);
            if (hf != -1)
                _lclose(hf);
            return 0;
        }
        _lclose(hf);
        hf = 0;
    }
    return 1;
}

/* Deletes the *.ded files that carry the signature g_939a [inferred]. */
/* 6:7042 */
void fn_06_7042(void)
{
    int16_t unused1;
    int16_t unused2;
    HFILE hf;
    int16_t r;
    char unused3[20];
    struct find_t ft;
    HGLOBAL h;
    int32_t *p;
    char path[110];
    char unused4[110];
    OFSTRUCT of;
    int32_t sig;

    lstrcpy(path, g_8f7a);
    lstrcat(path, g_96c5);
    lstrcat(path, "*.ded");
    h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x62L);
    p = (int32_t *)GlobalLock(h);
    for (r = _dos_findfirst(path, _A_RDONLY, &ft); r == 0; r = _dos_findnext(&ft)) {
        lstrcpy(path, g_8f7a);
        lstrcat(path, g_96c5);
        lstrcat(path, ft.name);
        hf = OpenFile(path, &of, OF_READ);
        if (hf != -1 && fn_14_4006(hf, (char *)p, 0x26L) != 0) {
            sig = *p;
            _lclose(hf);
            if (sig == g_939a)
                OpenFile(path, &of, OF_DELETE);
        }
    }
    GlobalUnlock(h);
    GlobalFree(h);
}

/* Finds or adds the race record for player n's name and stores a new
 * best value v in slot [j][k] [inferred]. */
/* 6:8cb2 */
int16_t fn_06_8cb2(int16_t unused, int16_t n, uint16_t v, int16_t j, int16_t k)
{
    char name[30];
    int16_t i;

    lstrcpy(name, g_96d2[g_7090[n].f_04e].f_70);
    for (i = 0; i < (int16_t)g_94c8 && lstrcmp(g_6afc[i].f_00, name); i++)
        ;
    if (i == g_94c8) {
        g_94c8++;
        GlobalUnlock(g_94e0);
        g_94e0 = GlobalReAlloc(g_94e0, g_94c8 * 0x42, GMEM_MOVEABLE | GMEM_ZEROINIT);
        g_6afc = (REC_42 *)GlobalLock(g_94e0);
        lstrcpy(g_6afc[i].f_00, g_96d2[g_7090[n].f_04e].f_70);
    }
    if (v && (g_6afc[i].f_32[j][k] > v || g_6afc[i].f_32[j][k] == 0)) {
        g_6afc[i].f_32[j][k] = v;
        if (n == g_9646 && flow_interactive)
            fn_17_8e60(n, g_6afc[i].f_14[j]);
        else
            lstrcpy(g_6afc[i].f_14[j], "----");
    }
    return i;
}

/* Starts a new particle/explosion in a free slot [inferred]. */
/* 6:84fc */
int16_t fn_06_84fc(int16_t a, int16_t x, int16_t y, int16_t dx, int16_t dy, int16_t w, int16_t h,
                   int16_t c, int16_t d, int16_t e)
{
    int16_t unused1;
    int16_t i;
    int16_t unused2;
    int16_t snd;

    if (!g_94da)
        return 1;
    if (g_94c4)
        return 0;
    c = c * 600 / g_0010;
    c = c < 28 ? 28 : c;
    c = c > 29 ? 29 : c;
    for (i = 0; i < g_94ce; i++) {
        if (g_6b08[i].f_002)
            continue;
        if (rand() % 3)
            snd = 0x4e;
        else
            snd = 0x1b;
        if (g_9330 && !subgame_active)
            fn_10_754a(snd, 6, e, 1);
        else
            fn_10_754a(snd, 0, 0, 0);
        g_6b08[i].f_000 = 0;
        g_6b08[i].f_027 = 0;
        g_6b08[i].f_029 = 0;
        g_6b08[i].f_002 = a;
        g_6b08[i].f_005 = d;
        g_6b08[i].f_007 = 0;
        g_6b08[i].f_013 = (int32_t)x << 8;
        g_6b08[i].f_017 = (int32_t)y << 8;
        g_6b08[i].f_01b = dx;
        g_6b08[i].f_01f = dy;
        g_6b08[i].f_00b = w;
        g_6b08[i].f_00d = h;
        g_6b08[i].f_011 = 0;
        g_6b08[i].f_00f = c;
        g_6b08[i].f_001 = e;
        return 1;
    }
    return 0;
}

                                 

/* Builds the champions list from the save files (*.sav, *.ded, *.don),
 * best score first, and fills the list box g_9488 or the table at
 * g_6b04 [inferred]. */
/* 6:6576 */
void fn_06_6576(void)
{
    int16_t k;
    int16_t i;
    HFILE hf;
    int16_t r;
    int16_t n;
    int16_t m;
    int16_t start;
    int32_t t;
    DWORD size;
    int16_t unused1;
    int16_t unused2;
    int16_t v;
    struct find_t ft;
    HGLOBAL h;
    REC_31 *p;
    char path[110];
    char line[110];
    OFSTRUCT of;

    fn_14_3eda();
    if (!g_6af8) {
        g_94de = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x31L);
        g_6af8 = GlobalLock(g_94de);
        g_94c6 = 0;
        h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x31L);
        p = (REC_31 *)GlobalLock(h);
        p->f_1e = g_1e58;
        p->f_00 = g_939a;
        p->f_22 = ((REC_7CB_seg06b *)g_6e24)[g_931c].f_00;
        p->f_24 = g_91f8;
        v = LO16(g_939e);
        p->f_18 = v >> 8;
        p->f_19 = v;
        p->f_1a = VIEW(char, g_939e, 2);
        t = fn_10_804c(0);
        v = (int16_t)t;
        p->f_1b = v >> 8;
        p->f_1c = v;
        p->f_1d = LOBYTE(HIWORD(t));
        lstrcpy(p->f_04, g_380c);
        lstrcpy(p->f_26, "--");
        p->f_30 = 0;
        n = 1;
        for (i = 0; i < 3; i++) {
            lstrcpy(path, g_9078);
            if (i == 0) {
                lstrcat(path, g_96b8);
                lstrcat(path, "*.sav");
            } else {
                lstrcat(path, g_96c5);
                if (i == 2)
                    lstrcat(path, "*.don");
                else
                    lstrcat(path, "*.ded");
            }
            r = _dos_findfirst(path, _A_RDONLY, &ft);
            while (r == 0) {
                n++;
                lstrcpy(path, g_9078);
                if (i == 0)
                    lstrcat(path, g_96b8);
                else
                    lstrcat(path, g_96c5);
                lstrcat(path, ft.name);
                GlobalUnlock(h);
                h = GlobalReAlloc(h, size = (uint16_t)((n + 1) * 0x31), GMEM_MOVEABLE | GMEM_ZEROINIT);
                p = (REC_31 *)GlobalLock(h);
                if ((hf = OpenFile(path, &of, OF_READ)) == -1)
                    return;
                if (fn_14_4006(hf, (char *)&p[n - 1], 0x26L) == 0)
                    return;
                if (p[n - 1].f_00 == g_939a && p[n - 1].f_1e <= g_1e58)
                    p[n - 1].f_00 = 0;
                lstrcpy(path, ft.name);
                for (k = 0; k < 4; k++)
                    path[lstrlen(path) - 1] = 0;
                lstrcpy(p[n - 1].f_26, path);
                p[n - 1].f_30 = i;
                _lclose(hf);
                r = _dos_findnext(&ft);
            }
        }
        for (i = 0; i < n; i++) {
            int16_t best;
            int32_t bestval;
            int32_t sig;

            best = -1;
            bestval = -1;
            for (k = 0; k < n; k++) {
                if (!p[k].f_00 || p[k].f_1e < 0)
                    continue;
                if (p[k].f_1e <= bestval)
                    continue;
                bestval = p[k].f_1e;
                best = k;
            }
            if (best == -1)
                break;
            if (best == 0)
                g_93a2 = i + 1;
            sig = p[best].f_00;
            if (best == 0)
                start = 0;
            else
                start = 1;
            for (k = start; k < n; k++)
                if (p[k].f_00 == sig && p[k].f_1e >= 0)
                    p[k].f_1e = -1 - p[k].f_1e;
        }
        for (k = 0; k < n; k++)
            if (p[k].f_1e < 0)
                p[k].f_1e = -1 - p[k].f_1e;
        for (i = m = 0; i < n; i++) {
            int32_t bestval;
            int16_t best;
            int32_t sig;

            best = -1;
            bestval = -1;
            for (k = 0; k < n; k++) {
                if (!p[k].f_00)
                    continue;
                if (p[k].f_1e <= bestval)
                    continue;
                bestval = p[k].f_1e;
                best = k;
            }
            if (best == -1)
                break;
            size = (uint16_t)((g_94c6 + 1) * 0x31);
            GlobalUnlock(g_94de);
            g_94de = GlobalReAlloc(g_94de, size, GMEM_MOVEABLE | GMEM_ZEROINIT);
            g_6af8 = GlobalLock(g_94de);
            ((REC_31 *)g_6af8)[g_94c6].f_1e = p[best].f_1e;
            ((REC_31 *)g_6af8)[g_94c6].f_00 = p[best].f_00;
            ((REC_31 *)g_6af8)[g_94c6].f_22 = p[best].f_22;
            if (p[best].f_22 > g_95aa - 1 || !fn_14_455c(p[best].f_22)) {
                p[best].f_22 = 0;
                ((REC_31 *)g_6af8)[g_94c6].f_22 = 0;
            }
            ((REC_31 *)g_6af8)[g_94c6].f_24 = p[best].f_24;
            ((REC_31 *)g_6af8)[g_94c6].f_18 = p[best].f_18;
            ((REC_31 *)g_6af8)[g_94c6].f_19 = p[best].f_19;
            ((REC_31 *)g_6af8)[g_94c6].f_1a = p[best].f_1a;
            ((REC_31 *)g_6af8)[g_94c6].f_1b = p[best].f_1b;
            ((REC_31 *)g_6af8)[g_94c6].f_1c = p[best].f_1c;
            ((REC_31 *)g_6af8)[g_94c6].f_1d = p[best].f_1d;
            lstrcpy(((REC_31 *)g_6af8)[g_94c6].f_04, p[best].f_04);
            lstrcpy(((REC_31 *)g_6af8)[g_94c6].f_26, p[best].f_26);
            ((REC_31 *)g_6af8)[g_94c6].f_30 = p[best].f_30;
            g_94c6++;
            sig = p[best].f_00;
            if (best == 0)
                start = 0;
            else
                start = 1;
            for (k = start; k < n; k++)
                if (p[k].f_00 == sig)
                    p[k].f_00 = 0;
        }
        GlobalUnlock(h);
        GlobalFree(h);
    }
    for (i = 0; i < g_94c6; i++) {
        if (g_947a[7]) {
            lstrcpy(line, "");
            fn_06_0f1a(i + 1, path);
            lstrcat(line, path);
            lstrcat(line, " - ");
            lstrcat(line, ((REC_31 *)g_6af8)[i].f_04);
            lstrcat(line, " - ");
            lstrcat(line, g_6e20[((REC_31 *)g_6af8)[i].f_22].f_0a);
            lstrcat(line, "\t230");
            fn_06_0eb8(((REC_31 *)g_6af8)[i].f_1e, path);
            lstrcat(line, path);
            lstrcat(line, "\t292");
            fn_06_0f1a(((REC_31 *)g_6af8)[i].f_18 + 1, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(((REC_31 *)g_6af8)[i].f_19, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(((REC_31 *)g_6af8)[i].f_1a, path);
            lstrcat(line, path);
            lstrcat(line, " - ");
            fn_06_0f1a(((REC_31 *)g_6af8)[i].f_1b + 1, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(((REC_31 *)g_6af8)[i].f_1c, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(((REC_31 *)g_6af8)[i].f_1d, path);
            lstrcat(line, path);
            lstrcat(line, "\t415");
            switch (((REC_31 *)g_6af8)[i].f_30) {
            case 0:
                LoadString(g_9212, 0x839, path, 40);
                break;
            case 1:
                LoadString(g_9212, 0x83a, path, 40);
                break;
            case 2:
                LoadString(g_9212, 0x83b, path, 40);
                break;
            }
            lstrcat(line, path);
            lstrcat(line, "\t475");
            lstrcat(line, "(");
            lstrcat(line, ((REC_31 *)g_6af8)[i].f_26);
            lstrcat(line, ")");
            SendMessage(g_947a[7], 0x401, 0, (LPARAM)(LPSTR)line);
        } else if (g_90f4 == 5) {
            if (g_93a2 < 8 && i < 10 || i < 3
                || i > g_93a2 - 5 && i < g_93a2 + 3) {
                g_6b04[m].f_2c = i + 1;
                g_6b04[m].f_28 = ((REC_31 *)g_6af8)[i].f_1e;
                lstrcpy(g_6b04[m].f_00, ((REC_31 *)g_6af8)[i].f_04);
                lstrcat(g_6b04[m].f_00, " - ");
                lstrcat(g_6b04[m].f_00, g_6e20[((REC_31 *)g_6af8)[i].f_22].f_0a);
                m++;
            }
        }
    }
    fn_14_4074();
}

/* Fills the save summary record [inferred]. */
/* 6:8eea */
void fn_06_8eea(REC_SAVE_seg06b *p)
{
    int16_t i;
    int16_t j;
    int16_t n;
    int16_t sum;
    int32_t t;
    int16_t v;

    p->f_170 = 0;
    if (g_7090[g_9646].f_0e4) {
        p->f_170 = !g_7090[g_9646].f_0ac;
        p->f_170 += !g_7090[g_9646].f_0ad * 2;
    }
    p->f_171 = g_9156;
    p->f_026 = g_7090[g_9646].f_05d;
    p->f_028 = g_7090[g_9646].f_05e;
    p->f_024 = g_91f8;
    p->f_02a = g_94a2;
    p->f_02c = g_931c;
    p->f_02e = g_9432;
    p->f_030 = g_964a;
    p->f_032 = g_94a4;
    p->f_034 = g_931a;
    p->f_01e = g_1e58;
    p->f_16a = g_5078;
    p->f_18b = g_05a8;
    p->f_15c = g_7090[g_9646].f_0d0;
    p->f_15a = g_7090[g_9646].f_0d2;
    p->f_162 = (int16_t)((g_7090[g_9646].f_0dc = min(g_7090[g_9646].f_0dc, 327670L)) / 10);
    p->f_164 = g_7090[g_9646].f_0ce;
    p->f_172 = g_7090[g_9646].f_018;
    p->f_022 = ((REC_7CB_seg06b *)g_6e24)[g_931c].f_00;
    p->f_160 = 0;
    p->f_16e = g_9134;
    p->f_16f = g_94ac;
    p->f_166 = g_93ac;
    p->f_168 = g_94ca;
    p->f_18f = g_9346;
    p->f_18a = g_967c;
    for (i = 0; i < 10; i++) {
        p->f_174[i] = g_a14d[i];
        p->f_17e[i] = g_a157[i];
    }
    p->f_000 = g_939a;
    v = LO16(g_939e);
    p->f_018 = v >> 8;
    p->f_019 = v;
    p->f_01a = VIEW(char, g_939e, 2);
    t = fn_10_804c(0);
    p->f_01b = HIBYTE(LOWORD(t));
    p->f_01c = LOBYTE(LOWORD(t));
    p->f_01d = LOBYTE(HIWORD(t));
    for (i = 0; i < g_94a4; i++)
        if (((REC_297B *)g_69f4)[i].f_1d0 == 2)
            p->f_160++;
    lstrcpy(p->f_004, g_380c);
    if (g_96d2[g_7090[g_9646].f_04e].f_28 == -1)
        n = 3;
    else
        n = 4;
    for (i = sum = 0; i < n; i++)
        sum += g_7090[g_9646].f_026[i];
    sum /= n;
    if (sum > 70)
        p->f_15e = 100;
    else if (sum > 45)
        p->f_15e = 101;
    else if (sum > 27)
        p->f_15e = 102;
    else
        p->f_15e = 103;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            p->f_036[i][j] = g_3824[i][j];
        for (j = 0; j < 3; j++) {
            p->f_0b6[i][j] = g_4eec[i][j];
            p->f_0e6[i][j] = g_4fd0[i][j];
            p->f_116[i][j] = g_6b10[i][j];
        }
        p->f_146[i] = g_6b40[i];
    }
    p->f_156 = g_945c;
    p->f_158 = g_945e;
    p->f_190[0] = g_a1cd / 128;
    p->f_190[1] = g_a1cd % 128;
    p->f_190[6] = g_a1cf;
    for (i = 2; i < 6; i++)
        p->f_190[i] = (g_a18f + 2)[i];
    p->f_173 = g_1318;
}

/* Saves the game (mode 0: .sav, 1: .ded, 2: .don) [inferred]. */
/* 6:885c */
int16_t fn_06_885c(int16_t ask, int16_t mode)
{
    int16_t i;
    int16_t unused1;
    HFILE hf;
    int16_t unused2;
    int16_t unused3;
    DWORD size;
    char path[110];
    char name[20];
    char tmp[100];
    OFSTRUCT of;
    HGLOBAL h;
    void *p;
    int16_t done;
    int16_t n;

    if (mode && g_1e58 < 1000)
        return 0;
    if (!g_920c && flow_interactive) {
        if (ask && !mode)
            fn_16_68d6(g_0016, 0x914, -1);
        return 0;
    }
    fn_06_7042();
    lstrcpy(path, g_9078);
    if (mode)
        lstrcat(path, g_96c5);
    else
        lstrcat(path, g_96b8);
    if (ask) {
        GetPrivateProfileString(g_9690, "Restore", "", name, 9, g_96a9);
        if (mode && name[3] == ' ') {
            lstrcpy(tmp, g_380c);
            tmp[7] = 0;
            lstrcpy(name, tmp);
            for (i = 0; i < lstrlen(name); i++)
                if (name[i] == ' ')
                    name[i] = 0;
        }
        lstrcat(path, name);
    } else if (flow_interactive)
        lstrcat(path, "lastgame");
    else
        lstrcat(path, "demogame");
    if (mode == 2)
        lstrcat(path, ".don");
    else if (mode)
        lstrcat(path, ".ded");
    else
        lstrcat(path, ".sav");
    if (mode) {
        n = done = 0;
        do {
            done = fn_06_8776(path);
            if (!done) {
                lstrcpy(path, g_8f7a);
                lstrcat(path, g_96c5);
                name[5] = 0;
                lstrcat(path, name);
                fn_06_0f1a(++n, tmp);
                lstrcat(path, tmp);
                if (mode == 2)
                    lstrcat(path, ".don");
                else
                    lstrcat(path, ".ded");
            }
        } while (!done);
    }
    hf = OpenFile(path, &of, OF_CREATE | OF_READWRITE);
    if (hf == -1)
        return 0;
    h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1a9L);
    p = GlobalLock(h);
    if (!p) {
        GlobalFree(h);
        _lclose(hf);
        return 0;
    }
    fn_06_8eea(p);
    if (!h || !g_94ae || !g_95a4) {
        _lclose(hf);
        return 0;
    }
    if (!fn_06_9e66(hf, (char *)p, size = GlobalSize(h))
        || !fn_06_9e66(hf, (char *)g_6e24, size = GlobalSize(g_95a4))
        || !mode && !fn_06_9e66(hf, (char *)g_69f4, size = GlobalSize(g_94ae))) {
        GlobalUnlock(h);
        GlobalFree(h);
        _lclose(hf);
        return 0;
    }
    _lclose(hf);
    GlobalUnlock(h);
    GlobalFree(h);
    h = 0;
    p = 0;
    return 1;
}

/* Moves and draws every active effect; returns 1 when none is active
 * [inferred]. */
/* 6:73f6 */
int16_t fn_06_73f6(void)
{
    int16_t j;
    int16_t cnt;
    int16_t bi;                     /* brush index */
    int16_t last;
    int16_t row;
    int16_t col;
    int16_t base;
    int16_t k;
    int16_t x;
    int16_t y;
    HGDIOBJ old;
    int16_t done;
    int16_t u1c;

    if (!g_94dc)
        return 1;
    done = 1;
    for (k = 0; k < g_94d0; k++) {
        if (((REC_FX *)g_6b0c)[k].f_004 - ((REC_FX *)g_6b0c)[k].f_005 == -4)
            fn_06_73d6(k);
        else if (((REC_FX *)g_6b0c)[k].f_000) {
            done = 0;
            if (((REC_FX *)g_6b0c)[k].f_004 <= ((REC_FX *)g_6b0c)[k].f_005 && ((REC_FX *)g_6b0c)[k].f_004 + 4 > ((REC_FX *)g_6b0c)[k].f_005) {
                cnt = ((REC_FX *)g_6b0c)[k].f_002 * ((REC_FX *)g_6b0c)[k].f_002;
                for (j = 0; j < cnt; j++)
                    PatBlt(g_13dc, ((REC_FX *)g_6b0c)[k].f_00c[((REC_FX *)g_6b0c)[k].f_00a + j], ((REC_FX *)g_6b0c)[k].f_12c[((REC_FX *)g_6b0c)[k].f_00a + j],
                           4, 4, BLACKNESS);
                ((REC_FX *)g_6b0c)[k].f_005++;
                ((REC_FX *)g_6b0c)[k].f_00a += g_94d6;
                if (((REC_FX *)g_6b0c)[k].f_00a > g_94d6 * 3)
                    ((REC_FX *)g_6b0c)[k].f_00a = 0;
            }
            if (((REC_FX *)g_6b0c)[k].f_004 > ((REC_FX *)g_6b0c)[k].f_005) {
                bi = ((REC_FX *)g_6b0c)[k].f_001 + ((REC_FX *)g_6b0c)[k].f_005 * 9 / ((REC_FX *)g_6b0c)[k].f_004;
                old = SelectObject(g_13dc, g_3b4c[bi]);
                last = ((REC_FX *)g_6b0c)[k].f_002 - 1;
                cnt = (last + 1) * (last + 1);
                for (base = row = 0; base < cnt; row++, base += ((REC_FX *)g_6b0c)[k].f_002)
                    for (col = 0; col < ((REC_FX *)g_6b0c)[k].f_002; col++) {
                        j = col + base;
                        PatBlt(g_13dc, ((REC_FX *)g_6b0c)[k].f_00c[((REC_FX *)g_6b0c)[k].f_00a + j], ((REC_FX *)g_6b0c)[k].f_12c[((REC_FX *)g_6b0c)[k].f_00a + j],
                               4, 4, BLACKNESS);
                        x = (int16_t)(((REC_FX *)g_6b0c)[k].f_390[j] >> 8);
                        y = (int16_t)(((REC_FX *)g_6b0c)[k].f_420[j] >> 8);
                        if (((REC_FX *)g_6b0c)[k].f_24c[j] > 0) {
                            if (((REC_FX *)g_6b0c)[k].f_24c[j] <= 4) {
                                switch (((REC_FX *)g_6b0c)[k].f_24c[j]) {
                                case 1:
                                    old = SelectObject(g_13dc, GetStockObject(GRAY_BRUSH));
                                    break;
                                case 2:
                                    old = SelectObject(g_13dc, GetStockObject(WHITE_BRUSH));
                                    break;
                                case 3:
                                    old = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
                                    break;
                                case 4:
                                    old = SelectObject(g_13dc, GetStockObject(BLACK_BRUSH));
                                    break;
                                }
                                PatBlt(g_13dc, x, y, 4, 4, PATCOPY);
                                SelectObject(g_13dc, old);
                                ((REC_FX *)g_6b0c)[k].f_24c[j]++;
                            }
                        } else {
                            if (col == 0 || col == last || row == 0 || row == last)
                                PatBlt(g_13dc, x, y, 2, 2, PATCOPY);
                            else if (col == 1 || last - col - 1 == 0 || row == 1 || last - row - 1 == 0)
                                PatBlt(g_13dc, x, y, 3, 3, PATCOPY);
                            else
                                PatBlt(g_13dc, x, y, 4, 4, PATCOPY);
                            if (((REC_FX *)g_6b0c)[k].f_004 - 8 <= ((REC_FX *)g_6b0c)[k].f_005 && ((REC_FX *)g_6b0c)[k].f_004 - 4 >= ((REC_FX *)g_6b0c)[k].f_005
                                && ((REC_FX *)g_6b0c)[k].f_005 - ((REC_FX *)g_6b0c)[k].f_004 + rand() % 4 + 4 >= 0) {
                                if (((REC_FX *)g_6b0c)[k].f_006 > 1000)
                                    ((REC_FX *)g_6b0c)[k].f_24c[j] = 1;
                                else
                                    ((REC_FX *)g_6b0c)[k].f_005 = ((REC_FX *)g_6b0c)[k].f_004 - 2;
                            }
                        }
                        ((REC_FX *)g_6b0c)[k].f_00c[((REC_FX *)g_6b0c)[k].f_00a + j] = x;
                        ((REC_FX *)g_6b0c)[k].f_12c[((REC_FX *)g_6b0c)[k].f_00a + j] = y;
                        ((REC_FX *)g_6b0c)[k].f_390[j] += ((REC_FX *)g_6b0c)[k].f_270[j];
                        ((REC_FX *)g_6b0c)[k].f_420[j] += ((REC_FX *)g_6b0c)[k].f_300[j];
                        ((REC_FX *)g_6b0c)[k].f_270[j] -= ((REC_FX *)g_6b0c)[k].f_270[j] >> ((REC_FX *)g_6b0c)[k].f_008;
                        ((REC_FX *)g_6b0c)[k].f_300[j] -= ((REC_FX *)g_6b0c)[k].f_300[j] >> ((REC_FX *)g_6b0c)[k].f_008;
                    }
                SelectObject(g_13dc, old);
                ((REC_FX *)g_6b0c)[k].f_005++;
                ((REC_FX *)g_6b0c)[k].f_00a += g_94d6;
                if (((REC_FX *)g_6b0c)[k].f_00a > g_94d6 * 3)
                    ((REC_FX *)g_6b0c)[k].f_00a = 0;
            }
        }
    }
    return done;
}

/* Updates the fireworks rockets and their sparks; returns 1 when none
 * is active [inferred]. */
/* 6:7c14 */
int16_t fn_06_7c14(void)
{
    int16_t unused1;
    int16_t i;
    int16_t j;
    int16_t x;
    int16_t y;
    int16_t px;
    int16_t py;
    int16_t unused2;
    int16_t unused3;
    HBRUSH old;
    int16_t done;

    if (!g_94da)
        return 1;
    done = 1;
    for (i = 0; i < g_94ce; i++) {
        if (g_6b08[i].f_002) {
            done = 0;
            if (g_6b08[i].f_007 >= 1)
                PatBlt(g_13dc, g_6b08[i].f_023, g_6b08[i].f_025, 4, 4, BLACKNESS);
            if (g_6b08[i].f_005 > 0) {
                x = g_6b08[i].f_013 >> 8;
                y = g_6b08[i].f_017 >> 8;
                if (y)
                    PatBlt(g_13dc, x, y, 4, 4, WHITENESS);
                if (g_6b08[i].f_001 >= 0 && !g_9330
                    && (y < HI16(g_90ea) / 4 || x < 0 || x > LO16(g_90ea)))
                    g_6b08[i].f_005 = 0;
                if (y > HI16(g_90ea) * 3 / 4 && g_6b08[i].f_01f > 0)
                    g_6b08[i].f_005 = 0;
                g_6b08[i].f_023 = x;
                g_6b08[i].f_025 = y;
                if (g_9330) {
                    if (subgame_active) {
                        g_6b08[i].f_013 = (int32_t)g_1df8[18]->f_00.x << 8;
                        g_6b08[i].f_017 = (int32_t)g_1df8[18]->f_00.y << 8;
                        g_6b08[i].f_01b = (int32_t)(g_1df8[18]->f_0c >> g_9150) << 2;
                        g_6b08[i].f_01b = (int32_t)(g_1df8[18]->f_0e >> g_9150) << 2;  /* sic */
                        if (!g_1df8[18]->f_1a)
                            g_6b08[i].f_005 = 0;
                    } else {
                        g_6b08[i].f_013 = (int32_t)g_1df8[6][g_6b08[i].f_001].f_00.x << 8;
                        g_6b08[i].f_017 = (int32_t)g_1df8[6][g_6b08[i].f_001].f_00.y << 8;
                        g_6b08[i].f_01b = (int32_t)(g_1df8[6][g_6b08[i].f_001].f_0c >> g_9150) << 2;
                        g_6b08[i].f_01b = (int32_t)(g_1df8[6][g_6b08[i].f_001].f_0e >> g_9150) << 2;  /* sic */
                        if (g_1df8[6][g_6b08[i].f_001].f_18)
                            g_6b08[i].f_005 = 0;
                    }
                } else {
                    g_6b08[i].f_013 += g_6b08[i].f_01b;
                    g_6b08[i].f_017 += g_6b08[i].f_01f;
                    g_6b08[i].f_01b += (g_6b08[i].f_01b >> g_6b08[i].f_00b)
                                   - (g_6b08[i].f_01b >> g_6b08[i].f_00d);
                    g_6b08[i].f_01f += (g_6b08[i].f_01f >> g_6b08[i].f_00b)
                                   - (g_6b08[i].f_01f >> g_6b08[i].f_00d) + g_6b08[i].f_00f;
                }
            }
            if (g_6b08[i].f_005 <= 0) {
                if (!g_6b08[i].f_000) {
                    g_6b08[i].f_000 = 1;
                    if (g_6b08[i].f_001 <= 0 || rand() % 100 > 90 || g_9330) {
                        if (!subgame_active)
                            fn_06_78ea(rand() % 2 * 10, (int16_t)(g_6b08[i].f_013 >> 8), (int16_t)(g_6b08[i].f_017 >> 8),
                                       (int16_t)(g_6b08[i].f_01b >> 8), (int16_t)(g_6b08[i].f_01f >> 8),
                                       rand() % 1000 + 4000, 4, 50 - rand() % 10);
                    } else {
                        fn_06_84fc(g_6b08[i].f_002, (int16_t)(g_6b08[i].f_013 >> 8), (int16_t)(g_6b08[i].f_017 >> 8),
                                   rand() % 1600 + (int16_t)g_6b08[i].f_01b - 800,
                                   rand() % 1600 + (int16_t)g_6b08[i].f_01f - 800,
                                   g_6b08[i].f_00b, g_6b08[i].f_00d, g_6b08[i].f_00f,
                                   rand() % 10 + g_6b08[i].f_007 / 2, g_6b08[i].f_001 - 1);
                        if (rand() % 20 < 9)
                            fn_06_84fc(g_6b08[i].f_002, (int16_t)(g_6b08[i].f_013 >> 8), (int16_t)(g_6b08[i].f_017 >> 8),
                                       rand() % 1600 + (int16_t)g_6b08[i].f_01b - 800,
                                       rand() % 1600 + (int16_t)g_6b08[i].f_01f - 800,
                                       g_6b08[i].f_00b, g_6b08[i].f_00d, g_6b08[i].f_00f,
                                       rand() % 10 + g_6b08[i].f_007 / 2, g_6b08[i].f_001 - 1);
                        fn_06_78ea(rand() % 2 * 10, (int16_t)(g_6b08[i].f_013 >> 8), (int16_t)(g_6b08[i].f_017 >> 8),
                                   (int16_t)(g_6b08[i].f_01b >> 8), (int16_t)(g_6b08[i].f_01f >> 8), 800, 4,
                                   50 - rand() % 10);
                    }
                }
                if (g_6b08[i].f_005 < -g_94d2) {
                    g_6b08[i].f_002 = 0;
                    continue;
                }
            }
            for (j = 0; j < g_94d4; j++) {
                if (g_6b08[i].f_007 < j)
                    continue;
                if (g_6b08[i].f_02b[j] >= g_94d2) {
                    if (!g_6b08[i].f_000)
                        fn_06_8684(i, j);
                } else {
                    if (g_6b08[i].f_02b[j] >= 4)
                        PatBlt(g_13dc, g_6b08[i].f_139[g_6b08[i].f_029 + j],
                               g_6b08[i].f_1b1[g_6b08[i].f_029 + j], 2, 2, BLACKNESS);
                    if (g_6b08[i].f_02b[j] < g_94d2 - 4) {
                        px = g_6b08[i].f_049[j] >> 8;
                        py = g_6b08[i].f_085[j] >> 8;
                        if (py) {
                            old = SelectObject(g_13dc,
                                               g_3b38[g_6b08[i].f_002 + g_6b08[i].f_02b[j]]);
                            PatBlt(g_13dc, px, py, 2, 2, PATCOPY);
                            SelectObject(g_13dc, old);
                        }
                        g_6b08[i].f_139[g_6b08[i].f_029 + j] = px;
                        g_6b08[i].f_1b1[g_6b08[i].f_029 + j] = py;
                        g_6b08[i].f_049[j] += g_6b08[i].f_0c1[j];
                        g_6b08[i].f_085[j] += g_6b08[i].f_0fd[j];
                    }
                    g_6b08[i].f_02b[j]++;
                }
            }
            g_6b08[i].f_029 += g_94d4;
            if (g_6b08[i].f_029 > g_94d4 * 3)
                g_6b08[i].f_029 = 0;
            g_6b08[i].f_007++;
            g_6b08[i].f_005--;
        }
    }
    return done;
}

/* Draws the champions table [inferred]. */
/* 6:62b6 */
void fn_06_62b6(void)
{
    int16_t i;
    int16_t unused;
    int16_t y;
    int16_t w;
    int16_t maxlen;
    int16_t off;
    int16_t n;
    char buf[40];
    char line[60];
    int16_t g;
    int16_t b;

    w = min(LO16(g_90ea) / 2 - 20, 360);
    maxlen = min((w - 33) * 2 / 18, 39);
    n = 10;
    off = 0;
    if (g_0010 < 480) {
        off = 15;
        n = g_0010 / 47;
    }
    LoadString(g_9212, 0x39d, buf, 40);
    fn_10_94c4(0, 6, RGB(255, 0, 0), LO16(g_90ea) / 2, HI16(g_90ea) / 2 + off - 175, buf);
    for (i = 0; i < n; i++) {
        y = i * 30 + HI16(g_90ea) / 2 + off - 130;
        fn_06_0f1a(g_6b04[i].f_2c, buf);
        if (!g_6b04[i].f_00[0])
            break;
        if (g_6b04[i].f_28 == g_1e58)
            g = b = 255;
        else {
            if (i < 3 && g_93a2 > 7)
                g = 255;
            else
                g = i * -255 / 10 + 230;
            b = 0;
        }
        fn_10_94c4(0, 2, PALETTERGB(255, g, b), LO16(g_90ea) / 2 - w + 7, y, buf);
        lstrcpy(buf, g_6b04[i].f_00);
        buf[maxlen] = 0;
        fn_10_94c4(0, 0, PALETTERGB(255, g, b), LO16(g_90ea) / 2 - w + 0x2e, y, g_6b04[i].f_00);
        fn_06_0eb8(g_6b04[i].f_28, buf);
        fn_10_94c4(0, 2, PALETTERGB(255, g, b), LO16(g_90ea) / 2 + w - 0x1e, y, buf);
    }
    LoadString(g_9212, 0x134, buf, 40);
    lstrcpy(line, buf);
    LoadString(g_9212, 0x80f, buf, 40);
    lstrcat(line, buf);
    lstrcat(line, ": ");
    fn_06_0eb8(g_1e58, buf);
    lstrcat(line, buf);
    fn_10_94c4(0, 6, PALETTERGB(255, 255, 255), LO16(g_90ea) / 2, y - off / 2 + 50, line);
}

/* Fireworks: launches new rockets until fireworks_end_ms, then shows the
 * champions table [inferred]. */
/* 6:5f7a */
void fn_06_5f7a(int16_t first)
{
    int16_t a;
    int16_t v;
    int16_t sw;
    int16_t ok;
    int16_t r1;
    int16_t r2;

    if (first)
        g_1c3c = 0;
    if (g_1e50 < fireworks_end_ms) {
        if (first) {
            v = rand() % 200 + 100;
            fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2 - 200, HI16(g_90ea), v, -2500,
                       32, 32, 25, 0x8c, -1);
            fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2 + 200, HI16(g_90ea), v = -v, -2500,
                       32, 32, 25, 0xc3, -1);
            fireworks_next_launch_ms = g_1e50 + 1700;
        }
        if (fireworks_next_launch_ms < g_1e50) {
            ok = 0;
            switch (sw = rand() % 3) {
            case 0:
                ok = fn_06_84fc((rand() % 2 + 1) * 10, rand() % 400 + LO16(g_90ea) / 2 - 200,
                                HI16(g_90ea), 0, -2500, 32, 32, 25, rand() % 30 + 80, -1);
                break;
            case 1:
                ok = fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2, HI16(g_90ea), 300, -2500,
                                32, 32, 25, rand() % 25 + 40, rand() % 3);
                if (ok)
                    ok = fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2, HI16(g_90ea), 300, -2500,
                                    32, 32, 25, rand() % 25 + 40, rand() % 3);
                break;
            case 2:
                a = rand() % 2;
                v = rand() % LO16(g_90ea) + LO16(g_90ea);
                if (a)
                    v = -v;
                ok = fn_06_84fc((rand() % 2 + 1) * 10, a * LO16(g_90ea), HI16(g_90ea), v, -2500,
                                32, 32, 25, rand() % 58 + 30, 2);
                break;
            }
            if (ok) {
                if (rand() % 6 < 2 && sw != 1)
                    fireworks_next_launch_ms = g_1e50 + rand() % 700;
                else
                    fireworks_next_launch_ms = g_1e50 + rand() % 600 + 600;
            }
        }
    }
    r1 = fn_06_73f6();
    r2 = fn_06_7c14();
    if (fireworks_end_ms < g_1e50 && r2 && r1 && !g_1c3c) {
        g_1c3c = g_94c4 = 1;
        fn_06_62b6();
    }
}

/* Starts the champions/fireworks screen (state 5) [inferred]. */
/* 6:5d58 */
void fn_06_5d58(void)
{
    DWORD t;
    POINT p;

    if (g_90f4 == 9)
        g_94cc = 1;
    else {
        g_94cc = 0;
        fn_10_744c(0x6e);
    }
    fn_10_7d58(LO16(g_90ea) / 2, HI16(g_90ea) / 2);
    fn_13_65f2(1);
    fn_11_02f0();
    g_1e7c = g_1e50 + 30000;
    g_90f4 = 5;
    PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    g_94d8 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1ccL);
    g_6b04 = (REC_2E *)GlobalLock(g_94d8);
    fn_06_6576();
    if (!g_94cc && (g_1e58 < 200000L || g_93a2 > 3))
        fn_10_7480(5, 1);
    else
        fn_10_7480(0xb, 1);
    if (!g_94cc)
        fn_06_885c(1, 1);
    if (g_94cc) {
        fireworks_end_ms = g_1e50 + 11000;
        fn_06_72d8(5, 5);
        p.y = 0;
        p.x = rand() % LO16(g_90ea) + LO16(g_90ea);
        fn_06_84fc((rand() % 2 + 1) * 10, p.y * LO16(g_90ea), HI16(g_90ea) + 100, p.x, -2500,
                   32, 32, 25, 0x26, 0);
        fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea), HI16(g_90ea) + 100, -p.x, -2500,
                   32, 32, 25, 0x15, 0);
    } else {
        if (g_93a2 > 10)
            fireworks_end_ms = g_1e50;
        else {
            if (g_93a2 == 1)
                t = 8800;
            else
                t = (12 - (int32_t)g_93a2) * 600UL;
            fireworks_end_ms = g_1e50 + t + 1000;
        }
        fn_06_72d8(3, 5);
    }
    g_94c4 = 0;
    fn_06_5f7a(1);
    g_1e7c = g_1e50 + 34000;
}

/* Starts an effect record in the 1200-byte table at DS:6b0c: a grid of
 * n x n points around (x, y) [inferred: explosion/debris cloud]. */
/* 6:78ea */
void fn_06_78ea(int16_t kind, int16_t x, int16_t y, int16_t vx, int16_t vy, int16_t size, int16_t n,
                    int16_t c)
{
    int16_t unused;
    int16_t i;
    int16_t j;
    int16_t idx;
    int16_t k;

    if (!g_94dc || g_94c4)
        return;
    fn_10_744c(0x69);
    if (size < 1000 && (rand() & 1))
        fn_10_754a(8, x, y, 4);
    else
        fn_10_754a(0x45, x, y, 4);
    if (g_9330 && !subgame_active && g_92e8 && !g_913a && !g_1df8[14][g_9646].f_54) {
        g_88c8.x = x;
        g_88c8.y = y;
        g_88c8 = fn_08_2bbe(g_88c8);
        fn_18_0b1e();
        g_9664 = g_9666 = 0;
        g_913a = 1;
        fn_10_754a(0x27, g_88c8.x, g_88c8.y, 4);
        g_965e = 1;
    }
    for (k = 0; k < g_94d0; k++) {
        if (((REC_FX *)g_6b0c)[k].f_000)
            continue;
        ((REC_FX *)g_6b0c)[k].f_00a = 0;
        ((REC_FX *)g_6b0c)[k].f_008 = n;
        ((REC_FX *)g_6b0c)[k].f_001 = kind;
        ((REC_FX *)g_6b0c)[k].f_004 = c;
        ((REC_FX *)g_6b0c)[k].f_000 = 4;
        ((REC_FX *)g_6b0c)[k].f_005 = 0;
        ((REC_FX *)g_6b0c)[k].f_006 = size;
        ((REC_FX *)g_6b0c)[k].f_002 = (n + (size >> 9) - 2) & ~1;
        if (((REC_FX *)g_6b0c)[k].f_002 > g_94d6)
            ((REC_FX *)g_6b0c)[k].f_002 = g_94d6;
        if (((REC_FX *)g_6b0c)[k].f_002 < 4)
            ((REC_FX *)g_6b0c)[k].f_002 = 4;
        for (j = 0; j < ((REC_FX *)g_6b0c)[k].f_002; j++)
            for (i = 0; i < ((REC_FX *)g_6b0c)[k].f_002; i++) {
                idx = ((REC_FX *)g_6b0c)[k].f_002 * j + i;
                ((REC_FX *)g_6b0c)[k].f_24c[idx] = 0;
                ((REC_FX *)g_6b0c)[k].f_390[idx] = (int32_t)x << 8;
                ((REC_FX *)g_6b0c)[k].f_420[idx] = (int32_t)y << 8;
                ((REC_FX *)g_6b0c)[k].f_270[idx] = ((int32_t)((REC_FX *)g_6b0c)[k].f_006
                    * fn_06_71b2(i * 180 / (((REC_FX *)g_6b0c)[k].f_002 - 1) + 90) >> 8)
                    * fn_06_71b2(j * 90 / (((REC_FX *)g_6b0c)[k].f_002 - 1) + 45) >> 6;
                ((REC_FX *)g_6b0c)[k].f_270[idx] += vx << 8;
                ((REC_FX *)g_6b0c)[k].f_300[idx] = ((int32_t)((REC_FX *)g_6b0c)[k].f_006
                    * fn_06_71b2(j * 180 / (((REC_FX *)g_6b0c)[k].f_002 - 1) + 90) >> 8)
                    * fn_06_71b2(i * 90 / (((REC_FX *)g_6b0c)[k].f_002 - 1) + 45) >> 6;
                ((REC_FX *)g_6b0c)[k].f_300[idx] += vy << 8;
            }
        return;
    }
}

                                  
                                     

/* Copies the object records into the far ship table (DS:6e24) and the
 * current mission record (DS:69f4), then saves [inferred]. rank stays
 * uninitialised when no band matches (as in the original). */
/* 6:99b6 */
void fn_06_99b6(void)
{
    int16_t i;
    int16_t me;                     /* copy of g_9646 */
    int16_t u8;
    int16_t ua;
    int16_t j;
    int16_t v;
    int16_t rank;
    int16_t u12;
    int16_t u14;
    int16_t u16;
    int16_t u18;
    int16_t found;

    if (g_91f8 > 0) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].f_0d6 == -1)
                continue;
            for (j = 0; j <= g_9316; j++)
                ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_3c[g_7090[j].f_0d6] = g_7090[i].f_062[j] / 10;
            for (j = 0; j < 4; j++)
                ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_38[j] = g_7090[i].f_026[j];
            if (!g_7090[i].flag)
                ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_38[0] = 0;
            for (j = 0; j < g_7090[i].cnt; j++) {
                ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_28[j] = g_7090[i].f_0b8[j];
                ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_1e[j] = g_7090[i].f_0ae[j];
            }
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_1d = g_7090[i].cnt;
            fn_14_421c(i);
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_06 = g_7090[i].f_082;
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_1c = g_7090[i].f_01e / 40;
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_74 = g_7090[i].f_024;
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_75 = LO8(g_7090[i].f_00a);
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_72 = g_7090[i].f_0ac;
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_73 = g_7090[i].f_0ad;
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_04 = g_7090[i].f_0ce;
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_02 = (int16_t)((g_7090[i].f_0dc = min(g_7090[i].f_0dc, 327670L)) / 10);
            v = (int16_t)((g_7090[i].f_0dc * 3 + g_7090[i].f_0d8) / 100);
            for (j = 1; j < 11; j++)
                if (g_0952[j] <= v && g_096c[j] > v) {
                    rank = j;
                    break;
                }
            ((REC_7C *)g_6e24)[g_7090[i].f_0d6].f_76 = rank;
            /* bare label: resets CL's register tracking (layout only) */
        reset:
            me = g_9646;
            if (!g_7090[i].flag || g_7090[i].f_082 < 0 || i == me) {
                for (j = 0; j < 8; j++)
                    if (((REC_297C *)g_69f4)[g_94a2].f_1c0[j] == g_7090[i].f_0d6)
                        ((REC_297C *)g_69f4)[g_94a2].f_1c0[j] = -1;
            } else {
                for (j = found = 0; j < 8; j++)
                    if (((REC_297C *)g_69f4)[g_94a2].f_1c0[j] == g_7090[i].f_0d6)
                        found = 1;
                if (!found)
                    for (j = 0; j < 8; j++)
                        if (((REC_297C *)g_69f4)[g_94a2].f_1c0[j] == -1) {
                            ((REC_297C *)g_69f4)[g_94a2].f_1c0[j] = g_7090[i].f_0d6;
                            break;
                        }
            }
        }
        g_931c = g_7090[g_9646].f_0d6;
        ((REC_297C *)g_69f4)[g_94a2].f_0a3 = 0;
        ((REC_297C *)g_69f4)[g_94a2].f_0a0 = 0;
        ((REC_297C *)g_69f4)[g_94a2].f_0a1 = 0;
        for (i = 0; i < g_9406[9]; i++)
            if (!g_1df8[9][i].f_18)
                ((REC_297C *)g_69f4)[g_94a2].f_0a3++;
        for (i = 0; i < g_9406[3]; i++) {
            if (g_1df8[3][i].f_44 == 350 && !g_1df8[3][i].f_18)
                ((REC_297C *)g_69f4)[g_94a2].f_0a0++;
            if (g_1df8[3][i].f_44 == 1400 && !g_1df8[3][i].f_18)
                ((REC_297C *)g_69f4)[g_94a2].f_0a1++;
        }
        for (i = 0; i < g_9406[8]; i++) {
            ((REC_297C *)g_69f4)[g_94a2].f_0ae[i] = g_1df8[8][i].f_1e;
            if (g_3d50[i].f_0a == -3)
                ((REC_297C *)g_69f4)[g_94a2].f_0ae[i] = -((REC_297C *)g_69f4)[g_94a2].f_0ae[i];
            ((REC_297C *)g_69f4)[g_94a2].f_0fe[i] = g_3d50[i].f_2e;
        }
    }
    fn_06_885c(1, 0);
}

/* Loads the saved game [inferred]. */
/* 6:930a */
int16_t fn_06_930a(void)
{
    int16_t i;
    int16_t j;
    HFILE hf;
    DWORD size;
    DWORD size2;
    char path[110];
    char name[20];
    char tmp[20];
    OFSTRUCT of;
    HGLOBAL h;
    REC_SAVE_seg06b *p;
    int16_t hi;
    int16_t lo;

    if (!g_920c && flow_interactive) {
        fn_16_68d6(g_0016, 0x915, -1);
        return 0;
    }
    g_939a = fn_10_804c(1);
    g_939e = fn_10_804c(0);
    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    if (flow_interactive) {
        GetPrivateProfileString(g_9690, "Restore", "", name, 9, g_96a9);
        lstrcat(path, name);
    } else
        lstrcat(path, "demogame");
    lstrcat(path, ".sav");
    hf = OpenFile(path, &of, OF_READ);
    if (hf == -1 || !(h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1a9L)))
        return 0;
    if (!(p = (REC_SAVE_seg06b *)GlobalLock(h))) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    size = GlobalSize(h);
    GlobalUnlock(h);
    if (!fn_14_4006(hf, (char *)(p = (REC_SAVE_seg06b *)GlobalLock(h = GlobalReAlloc(h, size, GMEM_MOVEABLE | GMEM_ZEROINIT))), size)) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    if (g_95a4) {
        GlobalUnlock(g_95a4);
        GlobalFree(g_95a4);
    }
    if (g_94ae) {
        GlobalUnlock(g_94ae);
        GlobalFree(g_94ae);
    }
    if (!(g_95a4 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size = (int32_t)(p->f_034 + 1) * 0x7c)))
        return 0;
    if (!(g_6e24 = GlobalLock(g_95a4))) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    size2 = GlobalSize(g_95a4);
    GlobalUnlock(g_95a4);
    if (!fn_14_4006(hf, (char *)(g_6e24 = GlobalLock(g_95a4 = GlobalReAlloc(g_95a4, size2, GMEM_MOVEABLE | GMEM_ZEROINIT))), size2)) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    if (!(g_94ae = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size = 0x297L * p->f_032)))
        return 0;
    if (!(g_69f4 = GlobalLock(g_94ae))) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    size2 = GlobalSize(g_94ae);
    GlobalUnlock(g_94ae);
    if (!fn_14_4006(hf, (char *)(g_69f4 = GlobalLock(g_94ae = GlobalReAlloc(g_94ae, size2, GMEM_MOVEABLE | GMEM_ZEROINIT))), size2)) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    if (p->f_171 != g_9156) {
        fn_06_0f1a(g_9156 = p->f_171, tmp);
        WritePrivateProfileString(g_9690, "Size", tmp, g_96a9);
        g_92e2 = 1;
    }
    g_939a = p->f_000;
    hi = p->f_01a;
    lo = (p->f_018 << 8) | p->f_019;
    g_939e = ((int32_t)hi << 16) | (uint16_t)lo;
    g_7090[0].f_05d = p->f_026;
    g_7090[0].f_05e = p->f_028;
    g_91f8 = p->f_024;
    g_94a2 = p->f_02a;
    if (!((REC_297C *)g_69f4)[g_94a2].f_0ad)
        ((REC_297C *)g_69f4)[g_94a2].f_0ad = 1;
    g_931c = p->f_02c;
    g_9432 = p->f_02e;
    g_964a = p->f_030;
    g_94a4 = p->f_032;
    g_931a = p->f_034;
    g_1e58 = p->f_01e;
    g_5078 = p->f_16a;
    g_93ac = p->f_166;
    g_94ca = p->f_168;
    g_9346 = p->f_18f;
    g_967c = p->f_18a;
    for (i = 0; i < 10; i++) {
        g_a14d[i] = p->f_174[i];
        g_a157[i] = p->f_17e[i];
    }
    g_a161 = p->f_188;
    g_a162 = p->f_189;
    g_7090[g_9646].f_018 = p->f_172;
    g_7090[0].f_0d2 = p->f_15a;
    g_7090[0].f_0d0 = p->f_15c;
    g_9134 = p->f_16e;
    if (!flow_interactive)
        g_9134 = 1;
    g_94ac = p->f_16f;
    g_05a8 = p->f_18b;
    lstrcpy(g_380c, p->f_004);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            g_3824[i][j] = p->f_036[i][j];
        for (j = 0; j < 3; j++) {
            g_4eec[i][j] = p->f_0b6[i][j];
            g_4fd0[i][j] = p->f_0e6[i][j];
            g_6b10[i][j] = p->f_116[i][j];
        }
        g_6b40[i] = p->f_146[i];
    }
    g_945c = p->f_156;
    g_945e = p->f_158;
    g_a1cd = p->f_190[0] << 7;
    g_a1cd += p->f_190[1];
    g_a1cf = p->f_190[6];
    for (i = 2; i < 6; i++)
        (g_a18f + 2)[i] = p->f_190[i];
    g_1318 = p->f_173;
    fn_14_3eda();
    for (i = 0; i < g_931a; i++) {
        if (((REC_7C *)g_6e24)[i].f_64 == 7)
            ((REC_7C *)g_6e24)[i].f_64 = 0;
        if (((REC_7C *)g_6e24)[i].f_00 >= g_95aa || !i && !fn_14_455c(((REC_7C *)g_6e24)[i].f_00))
            ((REC_7C *)g_6e24)[i].f_00 = 1;
    }
    fn_14_4074();
    g_104c[0].b = g_104c[0].a = g_951c = 0;
    g_92e4 = 1;
    if (p->f_15e < 100)
        for (i = 0; i < g_931a; i++)
            if (((REC_7C *)g_6e24)[i].f_02 < -15000)
                ((REC_7C *)g_6e24)[i].f_02 = (uint16_t)((REC_7C *)g_6e24)[i].f_02 / 10;
            else
                ((REC_7C *)g_6e24)[i].f_02 /= 10;
    fn_06_9932(h, hf, 1);
    return 1;
}
