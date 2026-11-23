/* INSPACE.EXE segment 11 (selector 1050). */
#include "inspace.h"

/* 0x15a-byte records at DS:7090, indexed by g_9646 (same layout as
 * seg04.c's REC_15A) [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p004[0x0a - 4];
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p014[0x18 - 0x14];
    int f18;                    /* +18 */
    char p01a[0x1e - 0x1a];
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26[3];                 /* +26: [3] is f2c */
    int f2c;                    /* +2c */
    int f2e;                    /* +2e */
    char p030[0x32 - 0x30];
    int f32;                    /* +32 */
    char p034[0x4e - 0x34];
    int f4e;                    /* +4e */
    char p050[0x52 - 0x50];
    int f52;                    /* +52 */
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    char p058[0x84 - 0x58];
    unsigned long f84;          /* +84 */
    char p088[0x8c - 0x88];
    long f8c;                   /* +8c */
    DWORD f90;                  /* +90 */
    DWORD f94;                  /* +94 */
    char p098[0xb8 - 0x98];
    char fb8[0x13];             /* +b8 */
    char fcb;                   /* +cb */
    char p0cc[0xce - 0xcc];
    int fce;                    /* +ce */
    char p0d0[0xda - 0xd0];
    int fda;                    /* +da */
    char p0dc[0xe2 - 0xdc];
    char fe2;                   /* +e2 */
    char p0e3[0xe7 - 0xe3];
    char fe7;                   /* +e7 */
    char fe8;                   /* +e8 */
    char fe9;                   /* +e9 */
    char fea;                   /* +ea */
    char feb;                   /* +eb */
    char p0ec[0x147 - 0xec];
    char f147;                  /* +147 */
    char p148[0x14a - 0x148];
    POINT f14a;                 /* +14a */
    long f14e;                  /* +14e */
    unsigned long f152;         /* +152 */
    char p156[0x15a - 0x156];
} REC_15A;
extern REC_15A g_7090[];

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[4];
    POINT f04;                  /* +04: position [inferred] */
    char p08[0x0c - 8];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;                    /* +18 */
    char p1a[0x22 - 0x1a];
    int f22;                    /* +22 */
    char p24[0x26 - 0x24];
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    char p2a[0x2e - 0x2a];
    char f2e;                   /* +2e */
    char p2f[0x44 - 0x2f];
    int f44;                    /* +44 */
    int f46;                    /* +46 */
    char p48[0x4c - 0x48];
    COLORREF f4c;               /* +4c */
    char f50;                   /* +50 */
    char p51[0x54 - 0x51];
    char f54;                   /* +54 */
    char p55[0x62 - 0x55];
    void (far pascal *f62)(int type, int n, HDC dc);   /* +62: draw [inferred] */
    char p66[0x70 - 0x66];
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0x1e-byte records at DS:6e38 [inferred]. */
typedef struct {
    int  f00;                   /* +00 */
    int  f02;                   /* +02 */
    int  f04;                   /* +04 */
    char p06[0x0c - 6];
    COLORREF f0c;               /* +0c */
    char p10[0x16 - 0x10];
    POINT f16;                  /* +16 */
    char p1a[0x1e - 0x1a];
} REC1E;
extern REC1E g_6e38[];

extern int g_001a;
extern HWND g_0a7a;
extern HWND g_0a7c;
extern HWND g_0a7e;
extern int g_13de;
extern int g_1034;
extern int g_1040;
extern HBITMAP g_5036;
extern int g_8e5a;
extern int g_93c0;
extern int g_93d8;
extern int g_93da;
extern int g_9e49;
extern int g_1dcc[];
extern int g_6b54[];
extern int g_500a;
extern int g_5024;
extern int g_8e62;
extern int g_8ff4;
extern int g_90f4;
extern int g_9130;                  /* subgame_active */
extern int g_9208;
extern int g_92e4;
extern int g_93aa;
extern int g_93d6;
extern int g_93de;
extern int g_9462;
extern char g_94e4[22];
extern char g_94fa[22];
extern int g_9646;
extern int g_952e;
extern int g_968e;

extern int g_0a62;
extern int g_0a76;
extern char g_1018[5][5];
extern int g_103e;
extern int g_1042;
extern int g_1044;
extern int g_1046;
extern unsigned long g_1e50;
extern unsigned long g_5028;
extern int g_1852;
extern HBITMAP g_5040;
extern int g_6e52;
extern int g_6e54;
extern int g_9134;
extern int g_93a6;
extern int g_952c;

/* inspace.h declares g_1e4c as long; here it is used as a far pointer. */
#define g_1e4c_ptr (*(unsigned far **)&g_1e4c)
#define g_1e4c_cp (*(char far **)&g_1e4c)

extern int g_0a72;
extern int g_0a74;
extern char g_93e0[];               /* run-time buffer (BSS) */
extern int g_9318;
extern int g_9322;
extern int g_9324;
extern int g_93c6;
extern HDC g_93ce;
extern HDC g_93d0;
extern int g_94a8;
extern int g_9524;
extern char g_9eb9[];
extern char g_9ebc[];

extern long g_0a64;
extern long g_0a68;
extern long g_0a6c;
extern int g_90ee;
extern HFONT g_90fe;
extern long g_501c;
extern long g_5020;
extern RECT g_5048;
extern int g_5050;
extern int g_5052;
extern HBITMAP g_503c;
extern HBITMAP g_503e;
extern unsigned long g_1e68;
extern long g_1e58;
extern long g_5018;
extern int g_104c;
extern int g_90ea;
extern int g_90f0;
extern int g_93b8;
extern int g_93dc;
extern int g_951c;
extern POINT g_5054[];
extern int g_9316;
extern int g_9326;
extern int g_9406[];
extern int g_9ea2;
extern HBITMAP g_5030[12];
extern HBITMAP g_93c8;
extern HBITMAP g_93ca;
extern HDC g_93cc;
extern HPALETTE g_93d2;
extern HBITMAP g_9400;
extern HBITMAP g_9402;
extern HPALETTE g_9404;
extern HBRUSH g_5004[];

/* 0x50-byte records at DS:2f58 (same as seg04.c's REC_50) [inferred]. */
typedef struct {
    char p00[6];
    int f06;                    /* +06 */
    char p08[0x42 - 8];
    int f42;                    /* +42 */
    char p44[0x50 - 0x44];
} REC_50;
extern REC_50 g_2f58[];
extern int g_9432;
extern int g_3a38[];
extern int g_9522;
extern int g_094e;
extern unsigned long g_5014;
extern int g_1858[];
extern int g_9320;
extern int g_951a;
extern int g_8f64;
int far fn_13_65f2(int a);
extern HBITMAP g_5038;
extern char g_9eb4;
extern int g_238c;
extern int g_238e;
extern int g_9138;
void far fn_07_1208(void);
void far fn_06_0ef8(unsigned long v, char far *buf);
void far fn_10_740c(void);
HBITMAP far fn_10_6d38(LPCSTR s);
HBITMAP far fn_10_6c02(int a, int b, int c);
/* 0x7c-byte records behind the far pointer at DS:6e24 [inferred]. */
typedef struct {
    char p00[0x32];
    char f32;                   /* +32 */
    char f33;                   /* +33 */
    char p34[0x7c - 0x34];
} REC_7C;
extern REC_7C far *g_6e24;
extern int g_1048;
extern int g_104a;
extern int g_104e;
extern int g_913e;
extern int g_668a;
extern int g_9ea0;
extern int g_1318;
extern int g_92e8;
extern int g_931c;
void far fn_04_2da2(void);
void far fn_13_adbe(int n, int a, int b);
void far fn_13_b6f2(int n, int r);
void far fn_12_6d64(int n, int k);
void far fn_10_744c(int a);
extern int g_93c2;
extern int g_1868;
extern int g_934e;
extern int g_92d4;
extern int g_95b8;
extern int g_91f8;
extern int g_8e5e;
extern int g_90f8;
extern int g_920c;
extern int g_9516;
extern DWORD g_6e28;
extern long g_120e;
extern int g_1212;
extern long g_939a;
extern long g_939e;
extern int g_8f70;
int far fn_10_82a2(int a);
long far fn_10_804c(int a);
void far fn_10_7480(int a, int b);
void far fn_15_1584(int a);
int far fn_06_930a(void);
void far fn_10_885e(int a);
int far fn_10_80a8(void);
int far fn_06_92b8(void);
void far fn_10_38e0(void);
void far fn_15_0cb0(void);
void far fn_06_1d9a(void);
extern DWORD g_2408;
extern int g_9416;
extern DWORD g_8e30;
typedef struct {                /* 0x34-byte records, field at DS:3d54 */
    long f00;
    char p04[0x34 - 4];
} REC_34;
extern REC_34 g_3d54[];
extern HBITMAP g_5042;
extern HBITMAP g_5044;
extern HBITMAP g_5046;
/* inspace.h declares g_05a0 as long; here it is two ints (world width and
 * height [inferred]). */
#define g_05a0_lo (((int *)&g_05a0)[0])
#define g_05a2 (((int *)&g_05a0)[1])
extern int g_93d4;
extern int g_93bc;
extern HBITMAP g_503a;
extern DWORD g_502c;
extern int g_1840[];
void far fn_03_06ec(int n, int kind, int target, int d);

/* 0xad-byte records; lowest field seen at DS:96ea (seg04.c bases them at
 * 96f0) [inferred]. */
#pragma pack(1)
typedef struct {
    char f00;                   /* +00 */
    char p01;
    char f02;                   /* +02 */
    char p03[0x06 - 3];
    int f06;                    /* +06 */
    char p08[0x0a - 8];
    int f0a[4];                 /* +0a */
    char p12[0x1e - 0x12];
    int f1e;                    /* +1e */
    char p20[0x34 - 0x20];
    int f34;                    /* +34 */
    char p36[0x6c - 0x36];
    char f6c[0x91 - 0x6c];      /* +6c: name [inferred] */
    long f91;                   /* +91 */
    char p95[0xad - 0x95];
} REC_AD;
#pragma pack()
extern REC_AD g_96ea[];
extern DWORD g_8e28;

long far pascal fn_11_1ab6(long x);
long far pascal fn_11_1b44(long y);
void far fn_18_0d4e(int msg, int wparam, long lparam);
HBITMAP far world_map(int w, int h, int a, int b, int c, int d, int e);
void far fn_06_0f1a(int v, LPSTR buf);
void far fn_02_088e(void);
int far fn_03_065e(int a, int b, int c);
void far fn_03_045a(int a);
void far fn_16_638a(int a, int b, int c, int d);
void far fn_16_614c(int msg, int wparam, long lparam);
int far fn_10_6b54(void);
int far fn_09_88ba(int x);
void far fn_10_949c(HDC dc, int a, int b, int c, int d, int e);
void far fn_12_2556(int type, int n);
void far fn_07_13b2(char kind, int type, int n);
void far fn_06_0eb8(long v, char far *buf);
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
void far fn_06_1c72(int a);
void far fn_09_0d6c(void);
void far fn_06_626c(void);

void far fn_13_4eec(int i, int d);
void far fn_10_7328(int a, LPSTR s, long b, char c, char d, int e, int f,
                    int g, int h);
void far fn_10_754a(int a, int b, int c, int d);
void far pascal fn_13_1318(int type, int n, int t, int k);

void far fn_11_0978(void);
void far fn_11_9daa(int type, int n);
void far fn_11_7902(int msg, int key, long lparam);
void far fn_11_1ef6(int force);
void far fn_11_2dac(HDC dc, int digit, int on, int i);
void far fn_11_2154(char align, long color, int x, int y, LPSTR s);

/* Not yet decompiled: stubs so calls to them compile as near calls. */
void far fn_11_05fe(int a) { }
void far fn_11_33cc(void) { }
HBITMAP far fn_11_2ff6(int a) { return 0; }
void far pascal fn_11_4e0a(int a) { }
void far fn_11_238e(HWND hwnd, HDC dc) { }
void far fn_11_41bc(HDC dc, int a, int b) { }
void far pascal fn_11_6b64(int msg, int wparam, long lparam) { }
void far pascal fn_11_7c12(int k, int type, int n) { }
void far pascal fn_11_b09c(int n, int a) { }
void far fn_11_0afe(void) { }
void far fn_11_8a42(int type, int n) { }
void far fn_11_947a(int type, int n, int k) { }
void far fn_11_9fdc(int type, int n) { }
void far fn_11_9078(int type, int n) { }

/* @addr 11:2120 */
int far fn_11_2120(void)
{
    if (g_500a == 0 || g_9130 != 0 || g_90f4 != 1 && g_90f4 != 7)
        return 0;
    return 1;
}

/* @addr 11:72b2 */
void far fn_11_72b2(void)
{
    if (g_7090[g_9646].fe2 == 0 && fn_10_6b54() == 0xa7)
        g_8ff4 = 0;
}

/* @addr 11:3396 */
void far fn_11_3396(void)
{
    if (++g_93de >= ((8 - g_9208) * 16 >> 6) * g_93d6) {
        g_93de = 0;
        fn_11_33cc();
    }
}

/* @addr 11:ae94 */
void far fn_11_ae94(void)
{
    if (g_92e4 == 0) {
        if (g_7090[g_9646].fcb > 1)
            g_7090[g_9646].f18 = 1;
        else
            g_7090[g_9646].f18 = 0;
    }
}

/* @addr 11:7b7a */
void far fn_11_7b7a(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1)
                    fn_06_1c72(1);
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:78bc */
void far fn_11_78bc(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 0) {
                    g_13de = 1;
                    g_968e = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:7b30 */
void far fn_11_7b30(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 4) {
                    fn_09_0d6c();
                    fn_06_626c();
                    g_001a = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:7bbc */
void far fn_11_7bbc(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1 && g_90f4 != 7)
                    g_93aa = 0x12;
                break;
            case 0x20:
                g_9462 = -1;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:b306 */
int far fn_11_b306(int c)
{
    int i;

    if (g_94fa[0] != 'Y') {
        for (i = 1; i < 0x16; i++)
            if (g_94fa[i] == c)
                return g_94e4[i];
    }
    return c;
}

/* @addr 11:04ea */
void far fn_11_04ea(void)
{
    char buf[20];
    long color;
    int k;

    if (g_5018 != g_1e58) {
        g_5018 = g_1e58;
        if (g_5018 == 0)
            lstrcpy(buf, "000");
        else
            fn_06_0eb8(g_1e58, buf);
        if (g_951c) {
            if (g_104c)
                color = 0x02ffc800L;
            else
                color = 0x02ffffffL;
        } else if (g_90f0)
            color = 0x0200a0ffL;
        else
            color = 0x000080ffL;
        if (g_90ea < 0x294) {
            k = 2;
            fn_11_2154(2, color, g_93dc + g_93b8 - k, g_8e5a + 0x2d, buf);
        } else if (g_90ea < 0x2f8) {
            k = 1;
            fn_10_94c4(k, 2, color, g_93dc + g_93b8 - k, g_8e5a + 0x31, buf);
        } else {
            k = 3;
            fn_10_94c4(0, 2, color, g_93dc + g_93b8 - k, g_8e5a + 0x31, buf);
        }
    }
}

/* @addr 11:04a0 */
void far fn_11_04a0(int a)
{
    if (fn_11_2120()) {
        switch (a) {
        case 0:
            fn_11_04ea();
            break;
        case 1:
            fn_11_05fe(0);
            break;
        case 6:
            fn_11_0978();
            break;
        case 7:
            fn_11_1ef6(0);
            break;
        }
    }
}

/* @addr 11:02f0 */
void far fn_11_02f0(void)
{
    if (g_0a7a) {
        DestroyWindow(g_0a7a);
        g_0a7a = 0;
    }
    if (g_0a7c) {
        DestroyWindow(g_0a7c);
        g_0a7c = 0;
    }
    if (g_0a7e) {
        DestroyWindow(g_0a7e);
        g_0a7e = 0;
    }
}

/* @addr 11:2ce6 */
void far fn_11_2ce6(HDC dc, int i)
{
    switch (i) {
    case 0:
        g_6e38[i].f16.x = 2;
        g_6e38[i].f16.y = 0x11;
        break;
    case 1:
        g_6e38[i].f16.x = g_5024 - 0x38;
        g_6e38[i].f16.y = 2;
        break;
    case 2:
        g_6e38[i].f16.x = 2;
        g_6e38[i].f16.y = 2;
        break;
    }
    if (g_6e38[i].f04) {
        if (g_6e38[i].f02 != g_6e38[i].f00) {
            fn_11_2dac(dc, g_6e38[i].f02, 0, i);
            g_6e38[i].f02 = g_6e38[i].f00;
        }
        fn_11_2dac(dc, g_6e38[i].f00, 1, i);
    } else {
        if (g_6e38[i].f02 != g_6e38[i].f00) {
            fn_11_2dac(dc, g_6e38[i].f02, 0, i);
            g_6e38[i].f02 = g_6e38[i].f00;
        }
        fn_11_2dac(dc, g_6e38[i].f00, 0, i);
    }
}

/* @addr 11:3ed8 */
void far fn_11_3ed8(int i)
{
    HDC dc;
    HWND hwnd;

    g_6e38[i].f04 = g_6e38[i].f04 == 0;
    if (i == 2)
        hwnd = g_95fc;
    else
        hwnd = g_0a7c;
    fn_11_2ce6(dc = GetDC(hwnd), i);
    ReleaseDC(hwnd, dc);
}

/* @addr 11:4db0 */
void far fn_11_4db0(void)
{
    if (g_9134 == 0 && g_7090[g_9646].f84 < g_1e50) {
        if (GetAsyncKeyState(0x10) & 0x8000 || GetAsyncKeyState(0x20) & 0x8000
            || g_1042)
            fn_11_4e0a(g_9646);
    }
}

/* @addr 11:785e */
void far fn_11_785e(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_93a6 == 0)
                    fn_16_638a(0, 0, 0, 1);
                break;
            }
            break;
        }
        if (g_952c)
            fn_16_614c(msg, key, lparam);
        g_8e62 = 0;
    }
}

/* @addr 11:170a */
int far fn_11_170a(int reset)
{
    int r;

    if (reset)
        g_1852 = -1;
    if (++g_1852 > 6)
        g_1852 = 0;
    switch (g_1852) {
    case 0:
    case 4:
        r = 0;
        break;
    case 2:
    case 5:
        r = 2;
        break;
    case 1:
    case 3:
    case 6:
        r = 1;
        break;
    }
    return r;
}

/* @addr 11:2f8c */
void far fn_11_2f8c(void)
{
    int unused;

    if (g_5040) {
        DeleteObject(g_5040);
        g_5040 = 0;
    }
    if (g_7090[g_9646].f18)
        g_5040 = fn_11_2ff6(g_7090[g_9646].fb8[g_7090[g_9646].f18]);
    if (g_0a7e)
        PostMessage(g_0a7e, WM_PAINT, 0, 0L);
}

/* @addr 11:3e6e */
void far fn_11_3e6e(void)
{
    HDC dc;
    RECT rc;

    if (g_0a76 != 4) {
        dc = GetDC(g_0a7c);
        GetClientRect(g_0a7c, &rc);
        PatBlt(dc, 0, 0, rc.right, rc.bottom, WHITENESS);
        ReleaseDC(g_0a7c, dc);
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    }
}

/* @addr 11:772e */
void far fn_11_772e(int a, int b)
{
    g_0a62 = 1;
    if (g_0a76 != 2) {
        g_0a76 = 2;
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        if (fn_03_065e(g_6e54, g_6e52, b) == 0)
            goto done;
        return;
    } else if (a) {
        g_6e54 = 3;
        g_6e52 = 0;
    }
done:
    fn_03_045a(b);
}

/* @addr 11:7588 */
void far fn_11_7588(int n)
{
    if ((g_1e4c_cp + 4)[n] == g_6b54[n] && g_1dcc[n] != 0 && g_1dcc[n] != 3)
        return;
    g_6b54[n] = (g_1e4c_cp + 4)[n];
    if (g_6b54[n] == 0)
        return;
    switch (g_1dcc[n]) {
    case 0:
        g_1042 = 1;
        break;
    case 1:
        PostMessage(g_0016, 0x101, 0xd, 0L);
        break;
    case 2:
        PostMessage(g_0016, 0x100, 9, 0L);
        break;
    case 3:
        g_103e = 1;
        break;
    case 4:
        PostMessage(g_0016, 0x100, 0x48, 0L);
        break;
    case 5:
        PostMessage(g_0016, 0x100, 0x52, 0L);
        break;
    case 6:
        PostMessage(g_0016, 0x101, 0x14, 0L);
        break;
    }
}

/* @addr 11:7650 */
void far fn_11_7650(int a, int b)
{
    int unused;

    if (g_9134 == 0 && (b != 0 || g_1034 == 0)) {
        if (a > -1 && g_1df8[g_9324][g_9646].f28 == a)
            g_1040 = 1;
        else {
            g_1040 = 0;
            if (a > -1 && g_1df8[g_9324][g_9646].f28 != a) {
                if (fn_09_88ba(g_1df8[g_9324][g_9646].f28 - a) > 8) {
                    if (g_1df8[g_9324][g_9646].f28 < a)
                        g_1044 = 1;
                    else
                        g_1046 = 1;
                } else {
                    if (g_1df8[g_9324][g_9646].f28 < a)
                        g_1046 = 1;
                    else
                        g_1044 = 1;
                }
            }
        }
    }
}

/* @addr 11:7504 */
void far fn_11_7504(void)
{
    unsigned a, b;
    int i;
    unsigned x, y;
    int v;

    if (g_8ff4) {
        g_103e = 0;
        g_1042 = 0;
        g_1044 = 0;
        g_1046 = 0;
        for (i = 0; i < 4; i++)
            fn_11_7588(i);
        a = g_1e4c_ptr[0];
        b = g_1e4c_ptr[1];
        x = a / 0x3444 > 4 ? 4 : a / 0x3444;
        y = b / 0x3444 > 4 ? 4 : b / 0x3444;
        v = g_1018[y][x];
        fn_11_7650(v, 1);
    }
}

/* @addr 11:22fa */
LONG far pascal fn_11_22fa(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT ps;
    HDC dc;
    int id;

    switch (msg) {
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        dc = BeginPaint(hwnd, &ps);
        fn_11_238e(hwnd, dc);
        EndPaint(hwnd, &ps);
        break;
    case WM_LBUTTONDBLCLK:
        id = GetDlgCtrlID(hwnd);
        if (id == 0xd2)
            g_93c6 = 1;
        else
            g_93c6 = 0;
        fn_02_088e();
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0L;
}

/* @addr 11:488c */
void far race_radar_background(int a)
{
    int i;

    world_map(g_0a72, g_0a74, a, g_9322, -1, -1, 1);
    if (g_94a8 == 0) {
        for (i = 0; i < g_9ebc[g_9322]; i++)
            world_map(g_0a72, g_0a74, a, g_9322, 8,
                      g_9eb9[g_9322] + g_9318 * 2 + i, 0);
    }
    BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
}

/* @addr 11:adf0 */
void far fn_11_adf0(void)
{
    int old;
    int unused;

    old = g_9524 = g_7090[g_9646].f18;
    if (g_7090[g_9646].fcb > 1) {
        g_9524++;
        if (g_7090[g_9646].fb8[g_9524] == 0)
            g_9524++;
        if (g_7090[g_9646].fcb <= g_9524) {
            if (g_9134)
                g_9524 = 0;
            else
                g_9524 = 1;
        }
        g_7090[g_9646].f18 = g_9524;
    } else
        g_7090[g_9646].f18 = 0;
    if (g_7090[g_9646].fb8[old] == 3)
        g_1df8[g_9324][g_9646].f50 = 0;
}

/* @addr 11:3f2e */
void far fn_11_3f2e(int v)
{
    char buf[8];

    if (v < -250)
        LoadString(g_9212, 0x244, g_93e0, 40);
    else if (v < -80)
        LoadString(g_9212, 0x245, g_93e0, 40);
    else if (v < 80)
        LoadString(g_9212, 0x246, g_93e0, 40);
    else if (v < 250)
        LoadString(g_9212, 0x247, g_93e0, 40);
    else
        LoadString(g_9212, 0x248, g_93e0, 40);
    if (v > 0)
        lstrcat(g_93e0, " +");
    else
        lstrcat(g_93e0, " ");
    fn_06_0f1a(v / 10, buf);
    lstrcat(g_93e0, buf);
}

/* @addr 11:4108 */
void far lap_timer(void)
{
    HDC dc;
    HFONT oldfont;
    COLORREF oldtext;
    COLORREF oldbk;

    dc = GetDC(g_0a7c);
    oldfont = SelectObject(dc, g_90fe);
    SetTextAlign(dc, 0);
    if (g_90ee == 1)
        oldtext = SetTextColor(dc, 0xffffffL);
    else
        oldtext = SetTextColor(dc, 0xff00L);
    oldbk = SetBkColor(dc, 0L);
    if (g_0a76 != 2)
        fn_11_41bc(dc, 0, 0);
    else
        fn_11_41bc(dc, 0, 1);
    SetBkColor(dc, oldbk);
    SetTextColor(dc, oldtext);
    SelectObject(dc, oldfont);
    ReleaseDC(g_0a7c, dc);
}

/* @addr 11:6aa8 */
void far pascal fn_11_6aa8(int msg, int wparam, long lparam)
{
    if (g_8e62) {
        if (g_9130)
            fn_18_0d4e(msg, wparam, lparam);
        else {
            if (msg == 0x101 || msg == 0x100)
                wparam = fn_11_b306(wparam);
            switch (g_90f4) {
            case 0:
                fn_11_7902(msg, wparam, lparam);
                break;
            case 1:
                fn_11_6b64(msg, wparam, lparam);
                break;
            case 3:
                fn_11_7bbc(msg, wparam, lparam);
                break;
            case 2:
                fn_11_7b7a(msg, wparam, lparam);
                break;
            case 6:
                fn_11_785e(msg, wparam, lparam);
                break;
            }
        }
        g_8e62 = 0;
    }
}

/* @addr 11:3914 */
void far pascal fn_11_3914(int type, int n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt))
        SetPixel(dc, pt.x, pt.y, g_1df8[type][n].f4c);
}

/* @addr 11:0894 */
void far fn_11_0894(void)
{
    HDC dc;
    HBITMAP oldbmp;
    HPALETTE oldpal;

    if (g_1e50 >= g_5028) {
        g_5028 = g_1e50 + 300;
        if (g_9e49 == 0 && g_9646 == g_952e)
            g_93d8 = g_93d8 == 0;
        else
            g_93d8 = 1;
        if (g_93da != g_93d8) {
            dc = CreateCompatibleDC(g_13dc);
            oldbmp = SelectObject(dc, g_5036);
            if (g_920e)
                oldpal = SelectPalette(dc, g_920e, 0);
            BitBlt(g_13dc, g_93c0, g_8e5a + 2, 20, 20, dc, g_93d8 * 20, 0,
                   SRCCOPY);
            if (oldpal)
                SelectPalette(dc, oldpal, 0);
            SelectObject(dc, oldbmp);
            DeleteDC(dc);
            g_93da = g_93d8;
        }
    }
}

/* @addr 11:39d8 */
void far pascal fn_11_39d8(int type, int n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt)) {
        SelectObject(dc, g_5004[g_1df8[type][n].f46]);
        PatBlt(dc, pt.x, pt.y, ((int)g_0a6c - 200) / 150 + 2,
               ((int)g_0a6c - 200) / 200 + 2, PATCOPY);
    }
}

/* @addr 11:3aca */
void far pascal fn_11_3aca(int type, int n, HDC dc)
{
    POINT pt;
    int first;

    if (n == -1) {
        n = g_9318 * 2;
        first = 1;
    } else
        first = 0;
    pt.x = fn_11_1ab6(g_1df8[type][n].f04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (g_9318 * 2 == n && !first)
        MoveTo(dc, pt.x, pt.y);
    else
        LineTo(dc, pt.x, pt.y);
}

/* @addr 11:3bae */
void far pascal fn_11_3bae(int type, int n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt)) {
        if (g_0a6c > 200) {
            SelectObject(dc, g_5004[g_1df8[type][n].f46]);
            PatBlt(dc, pt.x, pt.y, ((int)g_0a6c - 200) / 150 + 2,
                   ((int)g_0a6c - 200) / 150 + 2, PATCOPY);
        } else
            SetPixel(dc, pt.x, pt.y, g_1df8[type][n].f4c);
    }
}

/* @addr 11:01e0 */
void far fn_11_01e0(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (g_5004[i]) {
            DeleteObject(g_5004[i]);
            g_5004[i] = 0;
        }
    }
    if (g_93cc) {
        SelectObject(g_93cc, g_9400);
        DeleteDC(g_93cc);
        g_93cc = 0;
    }
    if (g_93ce) {
        if (g_9404)
            SelectPalette(g_93ce, g_9404, 0);
        SelectObject(g_93ce, g_9402);
        DeleteDC(g_93ce);
        g_93ce = 0;
    }
    if (g_93d0) {
        SelectObject(g_93d0, g_93ca);
        if (g_920e)
            SelectPalette(g_93d0, g_93d2, 0);
        DeleteDC(g_93d0);
        DeleteObject(g_93c8);
        g_93d0 = 0;
        g_93c8 = 0;
    }
    for (i = 0; i < 12; i++) {
        if (g_5030[i]) {
            DeleteObject(g_5030[i]);
            g_5030[i] = 0;
        }
    }
    fn_11_02f0();
}

/* @addr 11:367c */
void far fn_11_367c(void)
{
    HBRUSH old;
    int unused;
    int type;
    int i;

    SetRect(&g_5048, g_5050 - g_0a72 / 2 + 1, g_5052 - g_0a74 / 2 + 1,
            g_0a72 / 2 + g_5050 - 1, g_0a74 / 2 + g_5052 - 1);
    g_0a6c = 100;
    old = SelectObject(g_93ce, g_5004[0]);
    for (i = 0; i <= g_9316; i++)
        BitBlt(g_93ce, g_5054[i].x - 2, g_5054[i].y - 2, 5, 5,
               g_93d0, g_5054[i].x - 2, g_5054[i].y - 2, SRCCOPY);
    for (type = g_9326; type <= g_9324; type++) {
        if (type == 0xe) {
            for (i = 0; i < g_9406[type]; i++) {
                if (g_1df8[type][i].f18 == 0
                    && (type != 8 || g_9318 * 2 + g_9ea2 > i))
                    g_1df8[type][i].f62(type, i, g_93ce);
            }
        }
    }
    SelectObject(g_93ce, old);
}

/* @addr 11:4c72 */
int far fn_11_4c72(int n)
{
    if (g_7090[n].fe7 == 0)
        return 0;
    if ((n != g_9646 || g_9134) && g_1e68 - g_7090[n].f152 < 150)
        return 0;
    if (g_7090[n].fe8 == 0 && g_7090[n].f1e < 0x78)
        return 0;
    if (g_7090[n].feb == 0) {
        if (g_7090[n].fe8) {
            fn_12_2556(g_9324, n);
            g_7090[n].f2e = 2;
            fn_07_13b2(2, g_9324, n);
            g_7090[n].fe8 = 0;
            g_7090[n].f152 = g_1e68;
            return 1;
        }
        if (g_7090[n].f2c == 0)
            return 0;
        if ((n != g_9646 || g_9134) && g_7090[n].f2c <= 0x28)
            return 0;
        g_7090[n].f14a = g_1df8[g_9324][n].f04;
        g_7090[n].f14e = g_1e50;
        fn_12_2556(g_9324, n);
        g_7090[n].f2e = 2;
        fn_07_13b2(1, g_9324, n);
        g_7090[n].fe8 = 1;
        g_7090[n].f152 = g_1e68;
        return 1;
    }
    return 0;
}

/* Changes letter case in place by mode [inferred]. */
/* @addr 11:3fd4 */
void far fn_11_3fd4(LPSTR s, int mode)
{
    int i;
    int unused;
    int j;
    int cap;

    cap = 1;
    for (i = unused = 0; i < lstrlen(s); i++) {
        switch (mode) {
        case 0:
            cap = 0;
            break;
        case 1:
            cap = 1;
            break;
        }
        if (cap) {
            if (s[i] < 0x7b && s[i] > 0x60)
                s[i] -= 0x20;
        } else {
            if (s[i] < 0x5b && s[i] > 0x40)
                s[i] += 0x20;
        }
        cap = 0;
        if (mode == 2 && s[i] == ' ')
            cap = 1;
        if (lstrlen(s) - 3 > i && s[i] == ' ' && s[i + 1] == 'I' && s[i + 2] == ' ')
            cap = 1;
        if (mode == 3 && (s[i] == '.' || s[i] == '!' || s[i] == '\r' || s[i] == '\n')) {
            cap = 1;
            for (j = i + 1; j < lstrlen(s); j++) {
                if (s[j] == ' ')
                    i++;
                else
                    break;
            }
        }
        if (s[i] == '(')
            i++;
    }
}

/* Builds two small bitmaps at start-up [inferred]. */
/* @addr 11:0344 */
void far fn_11_0344(void)
{
    int unused;
    HBITMAP old2;
    HBITMAP old1;
    HDC dc2;
    HDC dc1;
    int i;

    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, g_5030[0]);
    dc2 = CreateCompatibleDC(dc1);
    old2 = SelectObject(dc2, g_503c = CreateCompatibleBitmap(dc1, 0x54, 0x3d));
    fn_10_949c(dc2, 0, 0, 0x53, 0x3c, 2);
    for (i = 0; i < 4; i++) {
        fn_10_949c(dc2, 5, i * 14 + 5, 0x1c, 7, 3);
        BitBlt(dc2, 0x29, i * 14 + 5, 0x20, 0xb, dc1, 0, (i + 1) * 11, SRCCOPY);
    }
    SelectObject(dc2, old2);
    DeleteDC(dc2);
    dc2 = CreateCompatibleDC(dc1);
    old2 = SelectObject(dc2, g_503e = CreateCompatibleBitmap(dc1, 0x1e, 0x55));
    fn_10_949c(dc2, 0, 0, 0x1d, 0x54, 2);
    fn_10_949c(dc2, 6, 0x12, 0x10, 0x3e, 3);
    BitBlt(dc2, 5, 5, 0x15, 0xb, dc1, 0, 0, SRCCOPY);
    SelectObject(dc2, old2);
    DeleteDC(dc2);
    SelectObject(dc1, old1);
    DeleteDC(dc1);
}

/* Fire the current weapon of the player's ship [inferred]. */
/* @addr 11:ac86 */
void far fn_11_ac86(void)
{
    if (g_7090[g_9646].fea || g_7090[g_9646].fe8
        || g_1df8[g_9324][g_9646].f2e)
        return;
    if (g_2f58[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f42 == 0
        && g_7090[g_9646].f32 != 9)
        g_9432 += 3;
    fn_13_4eec(g_9646, 4);
    g_8e28 = g_1e50;
    if (g_2f58[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f06) {
        fn_11_7c12(g_7090[g_9646].fb8[g_7090[g_9646].f18], g_9324, g_9646);
        return;
    }
    switch (g_7090[g_9646].fb8[g_7090[g_9646].f18]) {
    case 5:
        fn_13_1318(g_9324, g_9646, 0x1e, 5);
        break;
    case 4:
        fn_13_1318(g_9324, g_9646, 0x1e, 4);
        break;
    case 1:
        fn_11_8a42(g_9324, g_9646);
        break;
    case 2:
        fn_11_947a(g_9324, g_9646, 2);
        break;
    case 15:
        fn_11_947a(g_9324, g_9646, 15);
        break;
    case 3:
        fn_11_9fdc(g_9324, g_9646);
        break;
    case 23:
        fn_11_9daa(g_9324, g_9646);
        break;
    case 13:
        fn_11_9078(g_9324, g_9646);
        break;
    }
}

/* @addr 11:4b00 */
int far fn_11_4b00(int n)
{
    if (g_7090[n].f2c < 0x32 && g_7090[n].fea == 0)
        return 0;
    if (g_7090[n].f10 < 7 && g_7090[n].f10 > 0)
        return 0;
    if ((n != g_9646 || g_9134 != 0) && g_1e68 - g_7090[n].f152 < 0x96)
        return 0;
    if (g_7090[n].fea) {
        g_7090[n].f10 = 6;
        g_9522 = -1;
        g_7090[n].f20 = g_1df8[g_9324][n].f22 - 2;
        g_7090[n].f22 = 1;
        g_7090[n].fea = 0;
    } else {
        g_9522 = g_7090[n].f10 = 1;
        g_7090[n].f20 = g_1df8[g_9324][n].f22 - 12;
        g_7090[n].f22 = 7;
        g_7090[n].fea = 1;
    }
    fn_10_7328(g_96ea[g_7090[n].f4e].f1e, g_96ea[g_7090[n].f4e].f6c,
               g_96ea[g_7090[n].f4e].f91, g_96ea[g_7090[n].f4e].f00,
               g_96ea[g_7090[n].f4e].f02, g_1df8[g_9324][n].f28, g_3a38[n],
               1, 0x63);
    g_7090[n].f152 = g_1e68;
    if (g_7090[n].f02)
        fn_11_b09c(n, 1);
    fn_10_754a(5, g_9324, n, 1);
    return 1;
}

/* @addr 11:37a0 */
void far pascal fn_11_37a0(int type, int n, HDC dc)
{
    POINT pt;

    if (type == 14 && g_7090[n].f147)
        return;
    pt.x = fn_11_1ab6(g_1df8[type][n].f04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt)) {
        if (type == 14 && n == g_9646)
            SelectObject(dc, GetStockObject(WHITE_BRUSH));
        else
            SelectObject(dc, g_5004[g_1df8[type][n].f46]);
        switch (type) {
        case 7:
            BitBlt(dc, pt.x - 2, pt.y - 2, 4, 4, g_93cc, 0x50, 0, MERGECOPY);
            break;
        default:
            BitBlt(dc, pt.x - 2, pt.y - 2, 5, 5, g_93cc,
                   g_1df8[type][n].f28 * 5, 0, MERGECOPY);
            break;
        }
    }
    if (g_094e)
        g_5054[n] = pt;
}

/* @addr 11:1d7c */
void far fn_11_1d7c(void)
{
    int j;
    int i;

    if (g_5014 >= g_1e68)
        return;
    g_5014 = g_1e68 + 180;
    for (i = 0; i <= g_9316; i++) {
        if (g_1858[i] > 0) {
            if (g_96ea[g_7090[i].f4e].f34 != 0 && (i == g_9646 || g_9130 == 0)
                && g_7090[i].f1e > 0x5a) {
                for (j = 0; j < 4; j++) {
                    if (g_96ea[g_7090[i].f4e].f0a[j] != -1
                        && g_7090[i].f26[j] < 0x52
                        && (j != 3 || g_7090[i].f26[j] != 0 && g_7090[i].f26[j] != 0x32)) {
                        if (i != g_9646 || j == 3)
                            g_7090[i].f26[j]++;
                        else
                            g_7090[i].f26[j] += 2;
                        if (g_9320 == 6)
                            g_7090[i].f26[j]++;
                        g_7090[i].f1e -= 2;
                    }
                }
            }
            g_7090[i].f8c = max((0x4b - g_7090[i].f26[1]) * 4, 0x1b) / 0x1b;
            g_1858[i]--;
        } else
            g_1858[i] = max(g_1df8[14][i].f44 / -75 + 9, 1);
    }
}

/* @addr 11:0978 */
void far fn_11_0978(void)
{
    int i;
    int v;
    HBRUSH oldbrush;
    HDC dc;
    HBITMAP oldbmp;
    HPALETTE oldpal;

    v = min(g_7090[g_9646].f1e / (g_96ea[g_7090[g_9646].f4e].f06 / 60), 59);
    if (v == g_93d4)
        return;
    g_93d4 = v;
    if (g_502c < g_1e50) {
        for (i = 250; i > 60; i -= 60) {
            if (g_1840[g_9646] >= i && g_7090[g_9646].f1e < i) {
                fn_03_06ec(g_9646, 7, 0, 9);
                g_502c = g_1e50 + 30000;
            }
        }
    }
    g_1840[g_9646] = g_7090[g_9646].f1e;
    if (g_93d4 < 60) {
        oldbrush = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
        PatBlt(g_13dc, g_93bc + 8, g_8e5a + 0x13, 0xe, 60 - g_93d4, PATCOPY);
        SelectObject(g_13dc, oldbrush);
    }
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_503a);
    if (g_920e)
        oldpal = SelectPalette(dc, g_920e, 0);
    BitBlt(g_13dc, g_93bc + 8, g_8e5a - g_93d4 + 0x4f, 0xd, g_93d4, dc, 0,
           60 - g_93d4, SRCCOPY);
    if (oldpal)
        SelectPalette(dc, oldpal, 0);
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
}

/* Turn the player's ship with the arrow keys [inferred]. */
/* @addr 11:592a */
void far fn_11_592a(void)
{
    int key;                    /* stored value is never read */

    if (g_1034 == 0)
        return;
    if (g_9320 == 6 && g_9eb4 == 0 || g_9134 || g_7090[g_9646].feb
        || g_7090[g_9646].f84 >= g_1e50)
        return;
    if ((key = GetAsyncKeyState(VK_RIGHT) & 0x8000) || g_1046) {
        if (GetAsyncKeyState(VK_MENU) & 0x8000) {
            g_7090[g_9646].f12++;
            if (g_7090[g_9646].f12 > 1)
                g_7090[g_9646].f12 = 1;
        } else {
            g_1df8[g_9324][g_9646].f26 = 0;
            g_7090[g_9646].f12 = 0;
            g_1df8[g_9324][g_9646].f28++;
            if (g_1df8[g_9324][g_9646].f28 > 15)
                g_1df8[g_9324][g_9646].f28 = 0;
        }
        if (g_238e == 0)
            fn_07_1208();
        g_9138 = 1;
    }
    if ((key = GetAsyncKeyState(VK_LEFT) & 0x8000) || g_1044) {
        if (GetAsyncKeyState(VK_MENU) & 0x8000) {
            g_7090[g_9646].f12--;
            if (g_7090[g_9646].f12 < -1)
                g_7090[g_9646].f12 = -1;
        } else {
            g_1df8[g_9324][g_9646].f26 = 0;
            g_7090[g_9646].f12 = 0;
            g_1df8[g_9324][g_9646].f28--;
            if (g_1df8[g_9324][g_9646].f28 < 0)
                g_1df8[g_9324][g_9646].f28 = 15;
        }
        if (g_238e == 0)
            fn_07_1208();
        g_9138 = 1;
    }
}

/* Draw a string with the digit/letter bitmap font [inferred].
 * Callers see a char first parameter (they push the literal), the body
 * reads it as int: old-style definition (warning C4028 expected). */
/* @addr 11:2154 */
void far fn_11_2154(align, color, x, y, s)
int align;
long color;
int x;
int y;
LPSTR s;
{
    HBRUSH oldbrush;
    HDC dc;
    HBITMAP oldbmp;
    int unused;
    int x0;
    int i;
    int w;
    int c;
    int cw;

    w = 10;
    switch (align) {
    case 0:
        x0 = x;
        break;
    case 6:
        x0 = x - lstrlen(s) * w / 2;
        break;
    case 2:
        x0 = x - lstrlen(s) * w;
        break;
    }
    oldbrush = SelectObject(g_13dc, CreateSolidBrush(color));
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_5038);
    for (i = 0; i < lstrlen(s); i++) {
        cw = 10;
        c = s[i];
        if (c > '/' && c < ':') {
            c -= '0';
            BitBlt(g_13dc, i * 10 + x0, y, 10, 10, dc, c * 10, 0, 0xc00746L);
        } else {
            switch (c) {
            case 'S':
                c = 5;
                break;
            case 'C':
                c = 0xb;
                break;
            case 'O':
                c = 0;
                break;
            case 'R':
                c = 0xc;
                break;
            case 'E':
                c = 0xd;
                break;
            default:
                c = 100;
                break;
            }
            if (c == 100)
                PatBlt(g_13dc, (i + 1) * 10 - cw + x0, y, cw, 10, BLACKNESS);
            else
                BitBlt(g_13dc, (i + 1) * 10 - cw + x0, y, cw, 10, dc,
                       (c + 1) * 10 - cw, 0, 0xc00746L);
        }
    }
    DeleteObject(SelectObject(g_13dc, oldbrush));
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
}

/* Redraw the weapon panel of ship n [inferred]. */
/* @addr 11:3cc2 */
void far fn_11_3cc2(int n)
{
    HDC dc1;
    HDC dc2;
    HBITMAP old1;
    HBITMAP old2;
    HBRUSH oldbrush;
    int i;
    int k;
    HDC dc3;
    HBITMAP old3;

    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, g_5030[0]);
    dc2 = CreateCompatibleDC(dc1);
    old2 = SelectObject(dc2, g_503c);
    for (i = 0; i < 4; i++) {
        if (i == 3) {
            if (g_7090[n].fe9)
                k = 5;
            else if (g_7090[n].fe7)
                k = 4;
            else
                k = g_96ea[g_7090[n].f4e].f0a[i];
        } else
            k = g_96ea[g_7090[n].f4e].f0a[i];
        if (k == -1) {
            oldbrush = SelectObject(dc2, GetStockObject(LTGRAY_BRUSH));
            PatBlt(dc2, 0x29, i * 14 + 5, 0x20, 0xb, PATCOPY);
            SelectObject(dc2, oldbrush);
        } else
            BitBlt(dc2, 0x29, i * 14 + 5, 0x20, 0xb, dc1, 0, (k + 1) * 11,
                   SRCCOPY);
    }
    SelectObject(dc2, old2);
    DeleteDC(dc2);
    SelectObject(dc1, old1);
    DeleteDC(dc1);
    if (g_951a) {
        dc3 = CreateCompatibleDC(g_13dc);
        old3 = SelectObject(dc3, g_503c);
        BitBlt(g_13dc, g_93c0, g_8e5a + 0x18, 0x54, 0x3d, dc3, 0, 0, SRCCOPY);
        SelectObject(dc3, old3);
        DeleteDC(dc3);
        fn_11_05fe(1);
    } else {
        fn_11_0afe();
        if (fn_13_65f2(0))
            g_8f64 = 1;
        else
            g_8f64 = 0;
    }
}

/* Format a race time (t in ticks [inferred]) as m:ss:cc or s.cc. */
/* @addr 11:4928 */
void far fn_11_4928(int mode, DWORD t, LPSTR out)
{
    DWORD mins;
    DWORD secs;
    DWORD t2;
    DWORD m;
    char buf[40];

    if (t == 0) {
        if (mode)
            lstrcpy(out, "---.---  ");
        else
            lstrcpy(out, "---:---:---  ");
        return;
    }
    t *= 278;
    t /= 10;
    lstrcpy(out, "");
    if (mode == 0) {
        mins = t / 60000;
        m = mins * 60000;
        t -= m;
        fn_06_0ef8(mins, buf);
        if (mins < 10)
            lstrcat(out, "0");
        lstrcat(out, buf);
        lstrcat(out, ":");
    }
    secs = t / 1000;
    m = secs * 1000;
    t -= m;
    fn_06_0ef8(secs, buf);
    if (secs < 10 && mode == 0)
        lstrcat(out, "0");
    lstrcat(out, buf);
    if (mode)
        lstrcat(out, ".");
    else
        lstrcat(out, ":");
    t2 = t;
    fn_06_0ef8(t2 / 10, buf);
    if (t < 100)
        lstrcat(out, "0");
    lstrcat(out, buf);
    if (mode == 1) {
        LoadString(g_9212, 0x30df, buf, 40);
        lstrcat(out, " ");
        lstrcat(out, buf);
    } else if (mode == 0)
        lstrcat(out, "  ");
}

/* Load the bitmaps and brushes of the cockpit panel [inferred]. */
/* @addr 11:0000 */
void far fn_11_0000(void)
{
    int unused;
    int g;

    if (g_5042 == 0) {
        fn_10_740c();
        g_501c = (long)g_05a0_lo * 100;
        g_5020 = (long)g_05a2 * 100;
        g_5042 = CreateCompatibleBitmap(g_13dc, g_0a72, g_0a74);
        g_5030[1] = fn_10_6d38("METAL");
        g_5030[2] = fn_10_6c02(0xfa, 0, -1);
        g_5030[3] = fn_10_6c02(0xf0, 0, -1);
        fn_10_740c();
        g_5044 = fn_10_6c02(0x2d, 0, -1);
        if (g_90f0)
            g_503a = fn_10_6c02(0x104, 0, -1);
        else
            g_503a = fn_10_6c02(0x104, 3, -1);
        g_5038 = fn_10_6d38("DIGITAL");
        g_5046 = fn_10_6d38("RADSHIP");
        g_5030[0] = fn_10_6d38("SYSTEMS");
        fn_10_740c();
        g_500a = CreatePatternBrush(g_5030[1]);
        if (g_90f0)
            g = 0x60;
        else
            g = 0x40;
        g_5004[0] = CreateSolidBrush(PALETTERGB(0, g, 0));
        g_5004[7] = CreateSolidBrush(PALETTERGB(0, 0xc8, 0xff));
        g_5004[6] = CreateSolidBrush(RGB(0x80, 0xa0, 0xff));
        if (g_90f0)
            g = 0x80;
        else
            g = 0x3f;
        g_5004[2] = CreateSolidBrush(PALETTERGB(0, g, 0xff));
        g_5004[4] = CreateSolidBrush(RGB(0xc0, 0xc0, 0xc0));
        g_5004[1] = CreateSolidBrush(RGB(0xff, 0xc0, 0x40));
        g_5004[5] = CreateSolidBrush(PALETTERGB(0xff, 0x40, 0));
        g_93ce = CreateCompatibleDC(g_13dc);
        g_9402 = SelectObject(g_93ce, g_5042);
        g_93cc = CreateCompatibleDC(g_13dc);
        g_9400 = SelectObject(g_93cc, g_5046);
        if (g_920e)
            g_9404 = SelectPalette(g_93ce, g_920e, 0);
        fn_10_740c();
        fn_11_0344();
        g_93d8 = 1;
    }
}

/* Draw one segment of a seven-segment digit [inferred]. */
/* @addr 11:2dac */
void far fn_11_2dac(HDC dc, int seg, int on, int i)
{
    POINT pt;
    HPEN old;

    pt = g_6e38[i].f16;
    if (on)
        old = SelectObject(dc, CreatePen(PS_SOLID, 1, g_6e38[i].f0c));
    else
        old = SelectObject(dc, GetStockObject(BLACK_PEN));
    switch (seg) {
    case 0:
        MoveTo(dc, pt.x + 14, pt.y);
        LineTo(dc, pt.x + 29, pt.y);
        break;
    case 1:
        MoveTo(dc, pt.x + 29, pt.y);
        LineTo(dc, pt.x + 43, pt.y);
        LineTo(dc, pt.x + 43, pt.y + 14);
        break;
    case 2:
        MoveTo(dc, pt.x + 43, pt.y + 14);
        LineTo(dc, pt.x + 43, pt.y + 29);
        break;
    case 3:
        MoveTo(dc, pt.x + 29, pt.y + 43);
        LineTo(dc, pt.x + 43, pt.y + 43);
        LineTo(dc, pt.x + 43, pt.y + 29);
        break;
    case 4:
        MoveTo(dc, pt.x + 14, pt.y + 43);
        LineTo(dc, pt.x + 29, pt.y + 43);
        break;
    case 5:
        MoveTo(dc, pt.x + 14, pt.y + 43);
        LineTo(dc, pt.x, pt.y + 43);
        LineTo(dc, pt.x, pt.y + 29);
        break;
    case 6:
        MoveTo(dc, pt.x, pt.y + 14);
        LineTo(dc, pt.x, pt.y + 29);
        break;
    case 7:
        MoveTo(dc, pt.x + 14, pt.y);
        LineTo(dc, pt.x, pt.y);
        LineTo(dc, pt.x, pt.y + 14);
        break;
    }
    if (on)
        DeleteObject(SelectObject(dc, old));
    else
        SelectObject(dc, old);
}

/* Cheat keys [inferred]. */
/* @addr 11:72e0 */
int far fn_11_72e0(int key)
{
    switch (key) {
    case 'r':
        g_6e24[g_931c].f32 = 6;
        fn_10_754a(0x20, g_9324, g_9646, 1);
        break;
    case 's':
        g_913e = 2;
        break;
    case 't':
        if (g_9316 < 8)
            fn_13_adbe(g_9646, 0x16, 0x6d);
        break;
    case 'u':
        g_104a = 1;
        fn_13_b6f2(g_9646, rand() % 10);
        break;
    case 'v':
        fn_12_6d64(g_9646, 0x16);
        fn_12_6d64(g_9646, 0x17);
        fn_12_6d64(g_9646, 0x1a);
        fn_10_744c(0x25);
        break;
    case 'w':
        g_104c = g_104c == 0;
        g_5018 = -1;
        break;
    case 'x':
        g_1048 = 0;
        break;
    case '1':
        if (g_9320 == 6) {
            fn_04_2da2();
            return g_7090[g_9646].fda - g_9ea0 - 1;
        }
        break;
    case '2':
        if (g_9320 == 7)
            g_668a = -1;
        break;
    case '3':
        if (g_9316 < 8)
            fn_13_adbe(g_9646, 4, 0x6a);
        break;
    case '4':
        if (g_9316 < 8)
            fn_13_adbe(g_9646, 3, 0x69);
        break;
    case '5':
        if (g_92e8) {
            g_1318 = 1;
            g_1df8[14][g_9646].f54 = 0;
            g_913e = 1;
            fn_03_06ec(g_9646, 7, 0, 0xb5);
        }
        break;
    case '6':
        g_7090[g_9646].f1e = min(g_96ea[g_7090[g_9646].f4e].f06,
                                 g_7090[g_9646].f1e + 250);
        fn_10_754a(0x71, g_9324, g_9646, 1);
        break;
    case '7':
        g_104e = g_104e == 0;
        break;
    case '8':
        g_7090[g_9646].fce += 100;
        fn_10_754a(0x23, g_9324, g_9646, 1);
        break;
    case '9':
        g_6e24[g_931c].f33 = 6;
        fn_10_754a(0x20, g_9324, g_9646, 1);
        break;
    }
}

/* Draw the race clock (minutes and seconds) [inferred]. */
/* @addr 11:1ef6 */
void far fn_11_1ef6(int force)
{
    char buf[4];
    char sbuf[4];
    char mbuf[4];
    HBRUSH oldbrush;
    HDC dc;
    HBITMAP oldbmp;
    int unused;
    int i;
    int sec;
    int min;
    int a;
    int b;

    if (!fn_11_2120())
        return;
    g_934e = g_1e68 / 36;
    min = g_934e / 60;
    sec = g_934e % 60;
    if (sec != g_1868)
        force = 1;
    if (!force)
        return;
    g_1868 = sec;
    fn_06_0f1a(min, buf);
    if (min < 10) {
        lstrcpy(mbuf, " ");
        lstrcat(mbuf, buf);
    } else
        lstrcpy(mbuf, buf);
    fn_06_0f1a(sec, buf);
    if (sec < 10) {
        lstrcpy(sbuf, "0");
        lstrcat(sbuf, buf);
    } else
        lstrcpy(sbuf, buf);
    oldbrush = SelectObject(g_13dc, CreateSolidBrush(RGB(0, 0xff, 0)));
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_5038);
    for (i = 0; i < lstrlen(mbuf); i++) {
        b = 10;
        a = mbuf[i];
        if (a > '/' && a < ':')
            BitBlt(g_13dc, i * 10 + g_93c2 + 5, g_8e5a + 4, 10, 10, dc,
                   (a -= '0') * 10, 0, 0xc00746L);
        else
            PatBlt(g_13dc, i * 10 - b + g_93c2 + 15, g_8e5a + 4, b, 10,
                   BLACKNESS);
    }
    for (i = 0; i < lstrlen(sbuf); i++) {
        b = sbuf[i];
        if (b > '/' && b < ':') {
            b -= '0';
            BitBlt(g_13dc, (i + 3) * 10 + g_93c2, g_8e5a + 4, 10, 10, dc,
                   b * 10, 0, MERGECOPY);
        }
    }
    DeleteObject(SelectObject(g_13dc, oldbrush));
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
}

/* Key handler of the debriefing screen [inferred]. */
/* @addr 11:7902 */
void far fn_11_7902(int msg, int key, long lparam)
{
    int v;
    int r;

    if (g_8e62) {
        switch (msg) {
        case 0x101:
            if (g_90f8 && g_8e5e == 0)
                g_90f8 = 0;
            switch (key) {
            case 'S':
                fn_10_744c(0x6e);
                fn_10_744c(0x13);
                if (!fn_10_82a2(4))
                    break;
                fn_06_92b8();
            case 'D':
                fn_10_38e0();
            case 'C':
                g_939a = fn_10_804c(1);
                g_939e = fn_10_804c(0);
                if (g_95b8 >= 6 || g_120e != 0)
                    break;
                g_6e28 = g_1e50;
                g_95b8 = 5;
                if (key == 'D')
                    g_9516 = 1;
                else
                    g_9516 = 0;
                break;
            case 'R':
                if (g_920c == 0 || g_920c == 1) {
                    fn_10_744c(0x51);
                    if (fn_10_80a8())
                        fn_10_885e(0);
                }
                break;
            case 0x1b:
                fn_10_744c(0x6e);
                if (g_95b8 == 6) {
                    g_92d4 = 9;
                    break;
                }
                v = GetPrivateProfileInt(g_9690, "Accept", 0, g_96a9);
                if (g_920c == 2 && v != 42) {
                    fn_10_744c(0x13);
                    fn_10_82a2(0xb);
                    break;
                }
                if (g_90f4 == 1)
                    break;
                if (g_120e != 0 || g_1212 == 0)
                    break;
                if (g_95b8 < 6) {
                    g_92e4 = 0;
                    fn_10_744c(0x13);
                    r = fn_10_82a2(1);
                    if (r == 0)
                        break;
                    if (r == 2) {
                        if (!fn_06_930a())
                            return;
                    } else
                        fn_10_38e0();
                    fn_10_7480(-1, 1);
                    if (g_8f70 < 2) {
                        g_95b8 = 6;
                        fn_15_0cb0();
                    } else {
                        g_95b8 = 7;
                        if (g_92e4 == 0)
                            g_91f8 = 0;
                        fn_06_1d9a();
                        fn_06_1c72(1);
                    }
                } else if (g_95b8 == 6)
                    g_92d4 = 9;
                break;
            case ' ':
                if (g_95b8 < 6 && g_120e == 0)
                    g_6e28 = g_1e50;
                else if (g_92d4 < 2 && g_92d4 > 0)
                    fn_15_1584(1);
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:9daa */
void far fn_11_9daa(int type, int n)
{
    int i;

    if (g_238c)
        return;
    if (type == g_9324 && g_7090[n].f1e < 250)
        return;
    g_2408 = g_1e50 + 2000;
    *(long *)&g_238c = 0x60009L;    /* g_238c = 9, g_238e = 6 */
    for (i = 0; i <= g_9316; i++) {
        if (i == n && type == g_9324)
            continue;
        if (g_9130 && i != 0)
            continue;
        if (i & 1)
            g_1df8[g_9324][i].f26 = 1;
        else
            g_1df8[g_9324][i].f26 = -1;
        g_7090[i].fe2 = 1;
        g_7090[i].f84 = g_1e50 + 3500;
    }
    if (!g_9130) {
        for (i = 0; i < g_9416; i++) {
            if (i == n && type == 8)
                continue;
            if (i & 1)
                g_1df8[8][i].f26 = 1;
            else
                g_1df8[8][i].f26 = -1;
            g_3d54[i].f00 = g_1e50 + 3000;
        }
        fn_11_9078(type, n);
        if (g_92e8) {
            if (g_9316 == 0) {
                g_1df8[14][g_9646].f54 = 1;
                fn_13_adbe(g_9646, 0x13, 0xb4);
                for (i = 1; i < g_7090[g_9646].fcb; i++)
                    if (g_7090[g_9646].fb8[i] < 0x16)
                        fn_12_6d64(1, g_7090[g_9646].fb8[i]);
                g_7090[1].f24 = g_7090[1].f0a = g_7090[g_9646].f0a;
                g_1df8[14][1].f0c = g_1df8[14][1].f0e = g_7090[1].f1e = 0;
                g_8e30 = g_1e50 + 15000;
                g_7090[1].f00 = 0;
            } else {
                g_1df8[14][g_9646].f54 = 0;
                g_7090[1].f1e = g_96ea[g_7090[1].f4e].f06;
                g_7090[1].f54 = 14;
                g_7090[1].f56 = g_9646;
                g_7090[1].f52 = 2;
                g_7090[1].f94 = g_1e50 + 300;
            }
        }
    }
    if (type == g_9324)
        g_7090[n].f1e -= 200;
}

/* Slow down object n [inferred]. */
/* near-match 35%: 11:6874 (original multiplies with a 16-bit imul word
 * into dx:ax and pushes the divisor first; register/temp use differs) */
void far fn_11_6874(int n)
{
    int dy;
    int dx;

    if (g_1df8[g_9324][n].f0c == 0 && g_1df8[g_9324][n].f0e == 0)
        return;
    g_1df8[g_9324][n].f26 = 0;
    if (g_7090[n].f90 < g_1e50) {
        g_7090[n].f90 = g_1e50 + 250;
        if (g_7090[n].f02)
            fn_11_b09c(n, g_7090[n].f02 = 0);
    }
    dx = -((long)(g_1df8[g_9324][n].f44 / 30 + g_7090[n].f0c / 8
                  + g_7090[n].f0e + 30) * (long)g_1df8[g_9324][n].f0c
           / g_1df8[g_9324][n].f44);
    dy = -((long)(g_1df8[g_9324][n].f44 / 30 + g_7090[n].f0c / 8
                  + g_7090[n].f0e + 30) * (long)g_1df8[g_9324][n].f0e
           / g_1df8[g_9324][n].f44);
    if (fn_09_88ba(g_1df8[g_9324][n].f0c) < fn_09_88ba(dx))
        dx = -g_1df8[g_9324][n].f0c;
    if (fn_09_88ba(g_1df8[g_9324][n].f0e) < fn_09_88ba(dy))
        dy = -g_1df8[g_9324][n].f0e;
    if (dx == 0 && dy == 0) {
        if (g_1df8[g_9324][n].f0c > 0)
            dx = -1;
        else if (g_1df8[g_9324][n].f0c < 0)
            dx = 1;
        if (g_1df8[g_9324][n].f0e > 0)
            dy = -1;
        else if (g_1df8[g_9324][n].f0e < 0)
            dy = 1;
    }
    g_1df8[g_9324][n].f0c += dx;
    g_1df8[g_9324][n].f0e += dy;
}
