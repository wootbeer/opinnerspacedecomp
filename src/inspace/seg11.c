/* INSPACE.EXE segment 11 (selector 1050). */
#include "inspace.h"

/* 0x15a-byte records at DS:7090, indexed by g_9646 (same layout as
 * seg04.c's REC_15A) [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p004[0x06 - 4];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    int f14;                    /* +14 */
    char p016[0x18 - 0x16];
    int f18;                    /* +18 */
    char p01a[0x1c - 0x1a];
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26[3];                 /* +26: [3] is f2c */
    int f2c;                    /* +2c */
    int f2e;                    /* +2e */
    char p030[0x32 - 0x30];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    int f3a;                    /* +3a */
    char p03c[0x3e - 0x3c];
    int f3e;                    /* +3e */
    int f40;                    /* +40 */
    char p042[0x4e - 0x42];
    int f4e;                    /* +4e */
    char p050[0x52 - 0x50];
    int f52;                    /* +52 */
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    char p058[0x60 - 0x58];
    char f60;                   /* +60 */
    char f61;                   /* +61 */
    char p062[0x84 - 0x62];
    unsigned long f84;          /* +84 */
    char p088[0x8c - 0x88];
    long f8c;                   /* +8c */
    DWORD f90;                  /* +90 */
    DWORD f94;                  /* +94 */
    char p098[0xa0 - 0x98];
    DWORD fa0;                  /* +a0 */
    char p0a4[0xae - 0xa4];
    char fae[0xb8 - 0xae];      /* +ae */
    char fb8[0x13];             /* +b8 */
    char fcb;                   /* +cb */
    char fcc;                   /* +cc */
    char p0cd;
    int fce;                    /* +ce */
    char p0d0[0xd6 - 0xd0];
    int fd6;                    /* +d6 */
    char p0d8[0xda - 0xd8];
    int fda;                    /* +da */
    char p0dc[0xe0 - 0xdc];
    char fe0;                   /* +e0 */
    char fe1;                   /* +e1 */
    char fe2;                   /* +e2 */
    char p0e3[0xe4 - 0xe3];
    char fe4;                   /* +e4 */
    char p0e5[0xe7 - 0xe5];
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
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    POINT f04;                  /* +04: position [inferred] */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x12 - 0x10];
    int f12;                    /* +12 */
    char p14[0x18 - 0x14];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[0x1e - 0x1c];
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    char p2a[0x2c - 0x2a];
    int f2c;                    /* +2c */
    char f2e;                   /* +2e */
    char f2f;                   /* +2f */
    char p30;
    char f31;                   /* +31: tether slot [inferred] */
    int f32;                    /* +32: tethered-to type [inferred] */
    int f34;                    /* +34: tethered-to index [inferred] */
    int f36;                    /* +36: tether type, -1 = none [inferred] */
    int f38;                    /* +38: tether slot/index [inferred] */
    char p3a[0x42 - 0x3a];
    int f42;                    /* +42 */
    int f44;                    /* +44 */
    int f46;                    /* +46 */
    int f48;                    /* +48 */
    char p4a[0x4c - 0x4a];
    COLORREF f4c;               /* +4c */
    char f50;                   /* +50 */
    char f51;                   /* +51 */
    char p52;
    char f53;                   /* +53 */
    char f54;                   /* +54 */
    char f55[0x5e - 0x55];      /* +55: per shot slot flags [inferred] */
    int (far *f5e)(int type, int idx, int amount);  /* +5e [inferred] */
    void (far pascal *f62)(int type, int n, HDC dc);   /* +62: draw [inferred] */
    void (far *f66)(int type, int idx);  /* +66 */
    char p6a[0x70 - 0x6a];
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
extern int g_93ba;
extern int g_93be;
extern int g_93c4;
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
extern int g_9324;
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
extern int g_95f6;
extern int g_94e2;
extern int g_9344;
extern int g_8ff6;
typedef struct { int f00; char p02[4]; POINT f06; char p0a[6]; } REC_4F30;
extern REC_4F30 g_4f30[];    /* 16-byte records [inferred] */
int far fn_06_720c(int deg);
int far fn_06_71b2(int deg);
extern int g_0594;
extern int g_9000;
extern int g_9334;
extern int g_9006;
extern POINT g_7be0[][4][16];
void far pascal fn_08_0764(int a, int b);
void far fn_18_49d8(int i, int v);
extern int g_0aa2[4];              /* last drawn state per light [inferred] */
extern int g_93fe;
extern HBITMAP g_5034;
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
    int f04;
    int f06;                    /* +06 */
    char p08[0x34 - 8];
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
    int f20;                    /* +20 */
    char p22[0x34 - 0x22];
    int f34;                    /* +34 */
    char p36[0x38 - 0x36];
    POINT f38[5];               /* +38: cell offsets [inferred] */
    char p4c[0x6c - 0x4c];
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

/* 0x50-byte records seen from DS:2f4c (the REC_50 above, based lower). */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    int f14;                    /* +14 */
    int f16;                    /* +16 */
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    int f2a;                    /* +2a */
    int f2c;                    /* +2c */
    int f2e;                    /* +2e */
    char p30[0x36 - 0x30];
    int f36;                    /* +36 */
    char p38[0x4e - 0x38];
    int f4e;                    /* +4e */
} REC_50A;
extern REC_50A g_2f4c[];
extern HDC g_39e8[];
extern int g_9156;
/* 0x7c-byte records at DS:6e24, byte view [inferred]. */
typedef struct {
    char p00[0x7a];
    char f7a;                   /* +7a */
    char f7b;                   /* +7b */
} REC_7CB;
#define g_6e24b (*(REC_7CB far **)&g_6e24)
HBITMAP far fn_11_2ff6(int a);
void far fn_11_33cc(void);
void far fn_11_9078(int type, int n);
void far fn_11_238e(HWND hwnd, HDC dc);
void far fn_11_9fdc(int type, int n);
int far pascal fn_08_19b0(int dx, int dy);
void far fn_11_a234(int type, int n, int tt, int tn);
POINT far pascal fn_08_29ea(POINT pt);
void far fn_08_5df2(int a, int b, int c, int d, int e);
void far fn_07_2512(int n, int m);
extern POINT g_7b60[][64];
extern int g_943a;
extern int g_943c;
extern char g_9628[];               /* run-time buffer (BSS) */
extern char g_8718[];               /* run-time buffer (BSS) */
extern char g_960a[];               /* run-time buffer (BSS) */
extern char g_8740[];               /* run-time buffer (BSS) */
extern char g_8768[];               /* run-time buffer (BSS) */
extern char g_87b8[];               /* run-time buffer (BSS) */
extern int g_059a;
extern int g_059c;
extern int g_5026;
extern int g_6e70;
extern int g_6e72;
extern int g_9498;
int far fn_03_0000(int type, int n);
int far fn_13_371c(int type, int n);
int far fn_13_2688(int i, int j);
void far fn_13_58dc(HDC hdc, int b);
void far fn_12_7256(HDC dc, POINT a, POINT b);
extern int g_1016;
extern int g_1036;
extern int g_951e;
extern int g_9520;
extern int g_9526;
extern int g_9412;
extern HBITMAP g_3974[];
extern HPALETTE g_3a5c[];
extern HBITMAP g_3ad0[];
typedef struct {                /* 0x1c-byte records at DS:66e4 [inferred] */
    int f00;                    /* +00 */
    char p02[4 - 2];
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[0x1c - 0x0c];
} REC_1C;
extern REC_1C g_66e4[];
void far fn_12_6a60(int type, int idx);
int far fn_10_6308(int a, int b, int c, int d);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
extern int g_9528;
extern POINT g_6b5c[];
extern POINT g_6bbc[][5];
extern POINT g_6cfc[][3];
extern int g_2400;
extern int g_2402;
extern int g_9008;
extern int g_9150;
extern int g_9158;
extern int g_90ec;

/* 20-byte records at DS:1e90 (as seg07.c) [inferred]. */
typedef struct {
    int f0, f2, f4, f6, f8, fa, fc, fe;
    long f10;
} REC_14B;
extern REC_14B g_1e90[];
extern POINT g_5170[];
extern POINT g_5224[];
extern int g_9430;
extern int g_9434;
long far pascal fn_08_1290(long n, long g);
#define SC(n) ((n) << g_9156 >> 1)


/* 0x94-byte records at DS:6098 (as seg08c.c) [inferred]. */
typedef struct {
    int x0[2][6];               /* +00 */
    int y0[2][6];               /* +18 */
    int x1[2][6];               /* +30 */
    int y1[2][6];               /* +48 */
    char p60[0x68 - 0x60];
    int f68;                    /* +68 */
    int f6a;                    /* +6a */
    int f6c;                    /* +6c */
    int f6e;                    /* +6e */
    int f70;                    /* +70 */
    int f72;                    /* +72 */
    int f74;                    /* +74 */
    int f76;                    /* +76: -1 = free */
    int f78;                    /* +78 */
    int f7a;                    /* +7a: owner type */
    int f7c;                    /* +7c: owner index */
    int f7e;                    /* +7e */
    int f80;                    /* +80 */
    int f82;                    /* +82 */
    int f84[2];                 /* +84 */
    int f88;                    /* +88 */
    int f8a;                    /* +8a */
    char p8c[0x90 - 0x8c];
    long f90;                   /* +90 */
} REC_94;
extern REC_94 g_6098[];
extern char g_9eb5;
extern char g_9ec2[][40];
extern long g_05cc;
int far fn_08_35d0(long a, long b);
long far abs32(long x);

/* 0x16-byte records at DS:5b28 (as seg07.c) [inferred]. */
typedef struct {
    POINT p;                    /* +0 */
    POINT q;                    /* +4 */
    POINT r;                    /* +8 */
    int age;                    /* +c */
    int vx;                     /* +e */
    int vy;                     /* +10 */
    POINT s;                    /* +12 */
} REC_16;
extern REC_16 g_5b28[][4];
extern POINT g_1050[];
extern DWORD g_1c3e;
extern int g_9510;
extern int g_9512;
extern int g_9514;
extern int g_952a;
extern char g_8630[];
extern int g_058c;
extern DWORD g_05c0;
void far fn_13_6716(int n);
void far pascal fn_11_b09c(int n, int a);

extern char g_38c8[];
extern int g_9684;
extern int g_186a;
extern DWORD g_9e60[];
extern DWORD g_9e70[];
extern DWORD g_9e80[];
extern DWORD g_9e90[];
void far fn_09_9580(UINT id, LPSTR dst);
int far fn_09_955c(UINT id, LPSTR buf);
void far fn_17_7ba6(int a, LPSTR buf);
void far race_position(void);
void far fn_11_4928(int mode, DWORD t, LPSTR out);
void far race_radar_background(int a);

/* 0x20-byte tether records at DS:65cc (as seg08.c) [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[0x14 - 0x0c];
    POINT f14;                  /* +14 */
    char p18[4];
    POINT f1c;                  /* +1c */
} REC_20;
extern REC_20 g_65cc[];
extern int g_9300;
void far fn_08_348e(int type, int idx, int type2, int idx2, int speed);
void far fn_07_2080(int t, int unused);

extern HINSTANCE g_8e66;
extern int g_0a78;
extern int g_0010;
extern HDC g_929a;
typedef struct { char p00[0x1c]; int f1c; } REC_6DA4;   /* far pointer at DS:6da4 */
extern REC_6DA4 far *g_6da4;
void far fn_07_11cc(void);
void far fn_07_1f38(void);
void far fn_15_5962(int a);
void far fn_16_0cfe(int a);
void far fn_16_6928(int a);
void far fn_09_6dec(int a);
void far fn_06_5f7a(int a);
void far fn_09_6a12(void);
void far draw_briefing_panel_with_esc_prompt(int a);

/* 0x1c-byte shot records, second view based at DS:66e0 (REC_1C above is
 * based at 66e4) [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04: weapon kind, -1 = free */
    char p06[2];
    int f08;                    /* +08: owner type */
    int f0a;                    /* +0a: owner index */
    int f0c;                    /* +0c */
    char p0e[0x14 - 0x0e];
    int f14;                    /* +14 */
    int f16;                    /* +16 */
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
} REC_1CB;
extern REC_1CB g_66e0[];
extern HGLOBAL g_910c;
extern int g_92f8;
extern int g_9146;
extern char g_507c[];
extern char g_50e0[];
extern POINT g_7ba0[][64];
extern int g_95bc;                  /* flow_interactive */
int far fn_06_84fc(int a, int x, int y, int dx, int dy, int w, int h,
                   int c, int d, int e);
int far fn_07_2652(int type, int idx, int amount);
void far fn_07_2e02(int type, int idx);
void far fn_12_274a(int type, int idx);
void far fn_10_7944(int a, int b, int c, int d, LPCSTR e);
void far fn_03_00f4(int n, int type, int k);

/* Prototypes, and stubs ({ }) for functions not yet decompiled, so calls
 * to them compile as near calls. */
void far pascal fn_11_4e0a(int n);
void far pascal fn_11_5ab6(int n, int k);
void far fn_11_6874(int n);
void far pascal fn_11_63b4(int n, int a);
void far fn_11_5626(int i);
void far fn_11_41bc(HDC dc, int a, int b);
void far pascal fn_11_6b64(int msg, int wparam, long lparam) { }
void far pascal fn_11_7c12(int k, int type, int n);
void far pascal fn_11_b09c(int n, int a);
void far fn_11_0afe(void);
void far fn_11_8a42(int type, int n);
void far fn_11_947a(int type, int n, int k);
void far fn_11_a4a6(POINT a, POINT b, int type);

/* Redraw the four system status lights of the player's ship and play the
 * damage/repair messages [inferred]. */
/* @addr 11:05fe */
void far fn_11_05fe(int a)
{
    int i;
    int st;
    HDC dc;
    HBITMAP oldbmp;
    HBRUSH oldbrush;
    HPALETTE oldpal;
    int said;

    if (g_934e < 4)
        said = 1;
    else
        said = 0;
    for (i = 0; i < 4; i++) {
        if (g_96ea[g_7090[g_9646].f4e].f0a[i] == -1)
            st = 42;
        else if (g_7090[g_9646].f26[i] > 75)
            st = 0;
        else if (g_7090[g_9646].f26[i] > 50)
            st = 1;
        else if (g_7090[g_9646].f26[i] > 25)
            st = 2;
        else if (g_7090[g_9646].f26[i] > 0)
            st = 30;
        else
            st = 42;
        if (st != g_0aa2[i]) {
            if (st > g_0aa2[i]) {
                if (st == 30 && i == 0) {
                    if (!said) {
                        said = 1;
                        fn_03_06ec(g_9646, 7, 0, 10);
                    }
                } else if (st == 42) {
                    switch (i) {
                    case 1:
                        if (!said)
                            fn_03_06ec(g_9646, 7, 0, 11);
                        break;
                    case 2:
                        if (!said)
                            fn_03_06ec(g_9646, 7, 0, 12);
                        break;
                    }
                }
                switch (st) {       /* empty cases kept from the original */
                case 2:
                    break;
                case 30:
                    break;
                case 42:
                    break;
                }
            } else if (g_951a == 0 && g_952e != g_9646) {
                switch (st) {
                default:
                    break;
                case 0:
                    switch (i) {
                    case 1:
                        if (!said)
                            fn_03_06ec(g_9646, 7, 0, 0x52);
                        break;
                    case 2:
                        if (!said)
                            fn_03_06ec(g_9646, 7, 0, 0x53);
                        break;
                    }
                }
            }
        }
        if (a || st == 30 || g_0aa2[i] != st) {
            g_0aa2[i] = st;
            if (st == 30) {
                if (g_93fe)
                    st = 2;
                else
                    st = 42;
            }
            if (st == 42) {
                oldbrush = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
                PatBlt(g_13dc, g_93c0 + 6, g_8e5a + i * 14 + 30, 27, 6, PATCOPY);
                SelectObject(g_13dc, oldbrush);
            } else {
                dc = CreateCompatibleDC(g_13dc);
                oldbmp = SelectObject(dc, g_5034);
                if (g_920e)
                    oldpal = SelectPalette(dc, g_920e, 0);
                BitBlt(g_13dc, g_93c0 + 6, g_8e5a + i * 14 + 30, 27, 6, dc,
                       0, st * 6, SRCCOPY);
                SelectObject(dc, oldbmp);
                if (oldpal)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
            }
        }
    }
}

/* Fire the ship's weapon n: checks the reload time and aim, then fills a
 * free 0x94-byte shot record [inferred]. */
/* @addr 11:4e0a */
void far pascal fn_11_4e0a(int n)
{
    int i;
    int k;
    int j;
    int t;
    int facing;
    int ang;
    int cnt;
    long ldx;
    long ldy;
    long len;
    int ok;
    int flag;
    int found;
    POINT from;
    POINT to;

    g_0594 = 7;
    if (n == g_952e && g_9e49 >= 3 && g_9e49 <= 6 && g_9130 == 0)
        return;
    if (g_7090[n].f26[1] == 0)
        return;
    if (g_7090[n].f8c != 0 && g_7090[n].f8c + g_7090[n].fa0 > g_1e68
        || g_7090[n].fa0 + 5 > g_1e68)
        return;
    if (g_1df8[g_9324][n].f1a == 0 && g_7090[n].f32 != 0
        && g_7090[n].f32 != 9 && g_7090[n].f32 != g_9324)
        return;
    if (n != g_9646 || g_9134 != 0) {
        if (g_1df8[g_9324][n].f1a == 0)
            from = fn_08_29ea(g_1df8[g_9324][n].f04);
        else
            from = *(POINT far *)&g_1df8[g_9324][n].f00;
        if (g_1df8[g_7090[n].f32][g_7090[n].f34].f1a == 0)
            to = fn_08_29ea(g_1df8[g_7090[n].f32][g_7090[n].f34].f04);
        else
            to = *(POINT far *)&g_1df8[g_7090[n].f32][g_7090[n].f34].f00;
        ang = fn_08_19b0(to.x - from.x, to.y - from.y);
        facing = g_1df8[g_9324][n].f28;
        if (g_7090[n].f32 == g_9324 && g_7090[g_7090[n].f34].fe8 != 0)
            ang = facing;
        if (ang != facing)
            return;
        fn_11_5ab6(n, 5);
    }
    if (n == g_9646)
        g_8e28 = g_1e50;
    ok = 1;
    found = flag = 0;
    cnt = 0;
    for (i = 0; i < g_0594; i++) {
        if (g_6098[i].f76 == -1)
            cnt++;
        else if (g_6098[i].f7a == g_9324 && g_6098[i].f7c == n) {
            flag = 1;
            if (g_90ea / ((g_0594 - 2) * 10) >= g_6098[i].f76) {
                ok = 0;
                break;
            }
        }
        if (g_6098[i].f7a == g_9324 && g_6098[i].f7c == g_9646)
            found = 1;
    }
    if (cnt < 2 && found == 0 && n != g_9646)
        return;
    if (ok == 0)
        return;
    g_7090[n].fcc = max(7 - g_9000 * 2 - g_9334, 1);
    g_7090[n].fa0 = g_1e68;
    g_7090[n].f14a = g_1df8[g_9324][n].f04;
    g_7090[n].f14e = g_1e50;
    if (n == g_9646 && g_9134 != 0)
        fn_07_1208();
    for (i = 0; i < g_0594; i++) {
        if (g_6098[i].f76 == -1) {
            k = g_6098[i].f80 = g_6098[i].f7e = g_6098[i].f76 = 0;
            for (; k < g_0594; k++)
                for (j = 0; j < g_7090[n].f24; j++) {
                    g_6098[i].x1[j][k] = -100;
                    g_6098[i].y1[j][k] = -100;
                    fn_08_0764(i, k);
                }
            g_6098[i].x1[0][0] = g_6098[i].x1[1][0] = g_1df8[g_9324][n].f04.x;
            g_6098[i].y1[0][0] = g_6098[i].y1[1][0] = g_1df8[g_9324][n].f04.y;
            g_6098[i].f7a = g_9324;
            g_6098[i].f7c = n;
            g_6098[i].f78 = g_7090[n].f24;
            g_6098[i].f84[0] = g_7090[n].fe0;
            g_6098[i].f84[1] = g_7090[n].fe1;
            g_6098[i].f70 = g_1050[g_1df8[g_9324][n].f28].x * 3;
            g_6098[i].f72 = g_1050[g_1df8[g_9324][n].f28].y * 3;
            g_6098[i].f70 += g_1df8[g_9324][n].f0c / 10 * 10 / g_9006;
            g_6098[i].f72 += g_1df8[g_9324][n].f0e / 10 * 10 / g_9006;
            g_6098[i].f90 = 0;
            if (g_9130 == 0) {
                if (n == g_9646) {
                    g_6098[i].x1[0][0] -= g_1df8[g_9324][n].f0c;
                    g_6098[i].y1[0][0] -= g_1df8[g_9324][n].f0e;
                    g_6098[i].x1[1][0] -= g_1df8[g_9324][n].f0c;
                    g_6098[i].y1[1][0] -= g_1df8[g_9324][n].f0e;
                } else {
                    g_6098[i].x1[0][0] += g_1df8[g_9324][n].f0c;
                    g_6098[i].y1[0][0] += g_1df8[g_9324][n].f0e;
                    g_6098[i].x1[1][0] += g_1df8[g_9324][n].f0c;
                    g_6098[i].y1[1][0] += g_1df8[g_9324][n].f0e;
                }
            }
            g_6098[i].f74 = g_90ea / 10;
            if (n == g_9646 && g_7090[g_9646].f32 != 9)
                g_9432++;
            fn_13_4eec(n, 1);
            g_6098[i].f82 = 0;
            for (t = g_9326; t <= g_9324; t++)
                for (k = 0; k < g_9406[t]; k++)
                    g_1df8[t][k].f55[i] = 0;
            if (g_7090[n].f24 == 1) {
                g_6098[i].x1[0][0] += g_7b60[g_7090[n].f4e][g_1df8[g_9324][n].f28].x << 3;
                g_6098[i].y1[0][0] += g_7b60[g_7090[n].f4e][g_1df8[g_9324][n].f28].y << 3;
                g_6098[i].x1[0][0] = ((long)g_6098[i].x1[0][0] + ((long)g_05a0_lo << 3))
                                     % (g_05a0_lo << 3);
                g_6098[i].y1[0][0] = ((long)g_6098[i].y1[0][0] + ((long)g_05a2 << 3))
                                     % (g_05a2 << 3);
                if (n == g_9646)
                    fn_10_744c(0x69);
                fn_10_754a(3, 0x1e, i, 2);
                if (flag)
                    g_6098[i].f76 = 15;
                if (g_9130 != 0)
                    fn_18_49d8(i, g_6098[i].f74 - g_6098[i].f76);
                else if (g_9320 == 6 && g_9eb5 == 0)
                    fn_11_5626(i);
            } else {
                for (j = 0; j < 2; j++) {
                    g_6098[i].x1[j][0] += g_7be0[g_7090[n].f4e][j][g_1df8[g_9324][n].f28].x << 3;
                    g_6098[i].y1[j][0] += g_7be0[g_7090[n].f4e][j][g_1df8[g_9324][n].f28].y << 3;
                    g_6098[i].x1[j][0] = ((long)g_6098[i].x1[j][0] + ((long)g_05a0_lo << 3))
                                         % (g_05a0_lo << 3);
                    g_6098[i].y1[j][0] = ((long)g_6098[i].y1[j][0] + ((long)g_05a2 << 3))
                                         % (g_05a2 << 3);
                }
                ldx = g_6098[i].x1[1][0] - g_6098[i].x1[0][0];
                ldy = g_6098[i].y1[1][0] - g_6098[i].y1[0][0];
                g_6098[i].f68 = (int)ldx << 4;
                g_6098[i].f6a = (int)ldy << 4;
                len = (int)fn_08_1290(ldx * ldx + ldy * ldy, abs32(ldx) + abs32(ldy));
                if (len <= 1)
                    len = 1;
                g_6098[i].f68 = g_6098[i].f68 / len;
                g_6098[i].f6a = g_6098[i].f6a / len;
                g_6098[i].f6c = 0x1c;
                g_6098[i].f6e = 0x3e;
                if (n == g_9646)
                    fn_10_744c(0x69);
                if (g_7090[n].fe0 && g_7090[n].fe1)
                    fn_10_754a(4, 0x1e, i, 2);
                else
                    fn_10_754a(3, 0x1e, i, 2);
                if (flag)
                    g_6098[i].f76 = 15;
                if (g_9130 != 0)
                    fn_18_49d8(i, g_6098[i].f74 - g_6098[i].f76);
                else if (g_9320 == 6 && g_9eb5 == 0)
                    fn_11_5626(i);
            }
            return;
        }
    }
}

/* Steering/thrust of ship n for command k: autopilot speed limit, then fire
 * (6874), turn (63b4) or brake [inferred]. */
/* @addr 11:5ab6 */
void far pascal fn_11_5ab6(int n, int k)
{
    int j;
    int u6;
    int u8;
    int lim;
    int ang;
    int pa;
    int pb;
    int dist;
    POINT dv;
    int canfire;
    int strong;
    int pl;
    int autoon;
    int u20;
    long speed;
    int facing;
    int tf;
    int ang2;
    int a1;
    int a2;
    int accel;

    pl = 0;
    if (g_9320 == 6 && g_9eb4 == 0)
        return;
    if ((n != g_9646 || g_9134 != 0) && g_9e49 == 0 && n == g_952e)
        pl = 1;
    if (g_951a != 0 && n == g_9646)
        pl = 1;
    if (n == g_952e && g_9e49 >= 3 && g_9e49 <= 6 && g_9130 == 0)
        return;
    if (g_7090[n].f26[2] == 0)
        canfire = 0;
    else
        canfire = 1;
    if (g_7090[n].f26[2] < 50 && (g_9320 != 6 && g_9320 != 7 || g_7090[n].f1e > 50)
        && g_95f6 < 4)
        canfire = 0;
    if (g_7090[n].f1e < 50) {
        canfire = 0;
        /* Both arms equal (sic): the test is dropped, its imul stays. */
        if ((g_7090[n].f1e / 12 < 2 ? 2 : g_7090[n].f1e / 12) >= g_95f6 / 2 || k == 1) {
            if (g_7090[n].f1e)
                canfire = 1;
            else
                canfire = 1;
        }
        if ((n != g_9646 || g_9134 != 0) && g_7090[n].f32 == 4 && g_7090[n].f38 == 2)
            canfire = 1;
    }
    if (g_7090[n].f84 > g_1e50 || g_9320 == 6 && g_7090[n].f84 + 400 > g_1e50)
        canfire = 0;
    g_7090[n].f1c = g_7090[n].f1c - 1 < 1 ? 1 : g_7090[n].f1c - 1;
    if (k == 2)
        k = g_952a = 1;
    else
        g_952a = 0;
    strong = 0;
    autoon = 1;
    if (g_7090[n].f61 && g_7090[n].f26[2] > 75)
        autoon = 0;
    if (g_7090[n].f32 == 12)
        autoon = 1;
    if (g_9320 == 6) {
        if (g_1df8[14][n].f51)
            autoon = 1;
        else
            autoon = 0;
    }
    if (n == g_9646 && g_9134 == 0 || autoon == 0) {
        if (g_9320 != 6)
            g_7090[n].fda = g_7090[n].f0c * 19 / g_7090[n].f0e;
    } else {
        if (g_96ea[g_7090[n].f4e].f20 == 5)
            g_7090[n].fda = 120;
        else
            g_7090[n].fda = 90;
        if (g_9208 > 1) {
            for (j = 0; j < g_9344; j++) {
                dist = fn_08_285a(&pa, &pb, g_1df8[g_9324][n].f04, g_4f30[j].f06);
                if ((g_4f30[j].f00 >> 3) + 100 > dist) {
                    if ((g_4f30[j].f00 >> 3) - 40 < dist && (g_4f30[j].f00 >> 3) + 40 > dist)
                        g_7090[n].fda = g_7090[n].fda * 7 / 3;
                    else
                        g_7090[n].fda = g_7090[n].fda * 2 / 3;
                    break;
                }
            }
        }
        if (n != g_9646 || g_9134 != 0) {
            if (fn_09_88ba(g_1df8[g_9324][n].f0c) + fn_09_88ba(g_1df8[g_9324][n].f0e)
                > g_7090[n].fda) {
                if (g_94e2 < 30)
                    g_7090[n].fda = g_7090[n].fda * 5 / 4;
                else if (g_94e2 > 70 && g_94e2 < 100)
                    g_7090[n].fda = g_7090[n].fda * 4 / 5;
                else if (g_94e2 >= 100)
                    g_7090[n].fda = g_7090[n].fda * 3 / 4;
                g_7090[n].fda = g_7090[n].fda * 3 / 4;
                if (g_9156 == 2)
                    g_7090[n].fda = g_7090[n].fda * 4 / 5;
                else if (g_9156 == 0)
                    g_7090[n].fda = g_7090[n].fda * 5 / 4;
                if (g_7090[n].f14 > 30)
                    g_7090[n].fda = g_7090[n].fda * 35 / (g_7090[n].f14 + 10);
                lim = fn_08_35d0((long)g_1df8[g_9324][n].f0c, (long)g_1df8[g_9324][n].f0e);
                if (g_7090[n].fda < lim) {
                    ang = fn_08_19b0(g_1df8[g_9324][n].f0c, g_1df8[g_9324][n].f0e);
                    if (g_1df8[g_9324][n].f28 == ang && g_7090[n].fda > lim * 3 / 2)
                        strong = 1;
                    else
                        k = 5;
                }
            }
        }
    }
    if (pl) {
        g_7090[n].fda = g_7090[n].fda / 2 > 40 ? 40 : g_7090[n].fda / 2;
        strong = 1;
        if (fn_09_88ba(g_1df8[g_9324][n].f0c) > 30 || fn_09_88ba(g_1df8[g_9324][n].f0e) > 30)
            k = 1;
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8001) && g_9134 == 0 && n == g_9646 && canfire
        || k == 5 && canfire) {
        fn_11_6874(n);
    } else if ((GetAsyncKeyState(VK_UP) & 0x8001 || g_1040) && g_9134 == 0 && k == 4
               && canfire && !strong) {
        fn_11_63b4(n, k);
    } else if ((g_7090[n].f02 && k == 3 || k == 1) && canfire && !strong) {
        fn_11_63b4(n, k);
    } else {
        if (g_7090[n].fe2 && g_9130 == 0)
            goto done;
        if (g_7090[n].f02) {
            fn_11_b09c(n, g_7090[n].f02 = 0);
            fn_13_6716(n);
        }
        accel = g_7090[n].f0e;
        if (g_9130 != 0) {
            dv.x = -(accel * g_1df8[g_9324][n].f0c / (g_1df8[g_9324][n].f44 << 2));
            dv.y = -(g_1df8[g_9324][n].f0e * accel / (g_1df8[g_9324][n].f44 << 2));
        } else if (g_8ff6 && n == g_9646 && g_9134 == 0) {
            dv.x = (g_1df8[g_9324][n].f44 / -60 - g_7090[n].f02 / 8 - g_7090[n].f0e - 30)
                   * g_1df8[g_9324][n].f0c / g_1df8[g_9324][n].f44;
            dv.y = (g_1df8[g_9324][n].f44 / -60 - g_7090[n].f02 / 8 - g_7090[n].f0e - 30)
                   * g_1df8[g_9324][n].f0e / g_1df8[g_9324][n].f44;
        } else if (g_9208 > 2) {
            speed = fn_08_35d0((long)g_1df8[g_9324][n].f0c, (long)g_1df8[g_9324][n].f0e);
            ang2 = fn_08_19b0(g_1df8[g_9324][n].f0c, g_1df8[g_9324][n].f0e);
            facing = g_1df8[g_9324][n].f28;
            tf = (ang2 - facing) * 23 + 360;
            a1 = (long)fn_06_720c(tf) * accel * speed / ((long)g_1df8[g_9324][n].f44 << 9);
            a2 = (long)fn_06_71b2(tf) * accel * speed / (178L * g_1df8[g_9324][n].f44);
            if (strong) {
                a1 = a1 * 4 / 3;
                a2 = a2 * 4 / 3;
            }
            dv.x = (g_1050[facing].x * a1 + g_1050[(facing + 4) % 16].x * a2) / -20;
            dv.y = (g_1050[facing].y * a1 + g_1050[(facing + 4) % 16].y * a2) / -20;
        } else {
            dv.x = -(g_1df8[g_9324][n].f0c * accel / (g_1df8[g_9324][n].f44 << 3));
            dv.y = -(g_1df8[g_9324][n].f0e * accel / (g_1df8[g_9324][n].f44 << 3));
        }
        g_1df8[g_9324][n].f0c += dv.x;
        g_1df8[g_9324][n].f0e += dv.y;
    }
done:
    if ((n != g_9646 || g_9134 != 0) && g_7090[n].f3a == 2 && g_7090[n].f38 == 3) {
        if (g_7090[n].f52 == 0 || g_7090[n].f52 == 2) {
            if (fn_08_285a(&pa, &pb, g_1df8[g_7090[n].f32][g_7090[n].f34].f04,
                           g_1df8[g_9324][n].f04) < 400) {
                g_1df8[g_9324][n].f0c = g_1df8[g_9324][n].f0c * 3 / 4;
                g_1df8[g_9324][n].f0e = g_1df8[g_9324][n].f0e * 3 / 4;
            }
        }
    }
}

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
/* @addr 11:6874 */
void far fn_11_6874(int n)
{
    POINT d;

    if (g_1df8[g_9324][n].f0c == 0 && g_1df8[g_9324][n].f0e == 0)
        return;
    g_1df8[g_9324][n].f26 = 0;
    if (g_7090[n].f90 < g_1e50) {
        g_7090[n].f90 = g_1e50 + 250;
        if (g_7090[n].f02)
            fn_11_b09c(n, g_7090[n].f02 = 0);
    }
    d.x = -((long)(g_1df8[g_9324][n].f44 / 30 + g_7090[n].f0c / 8
                  + g_7090[n].f0e + 30) * g_1df8[g_9324][n].f0c
           / g_1df8[g_9324][n].f44);
    d.y = -((long)(g_1df8[g_9324][n].f44 / 30 + g_7090[n].f0c / 8
                  + g_7090[n].f0e + 30) * g_1df8[g_9324][n].f0e
           / g_1df8[g_9324][n].f44);
    if (fn_09_88ba(g_1df8[g_9324][n].f0c) < fn_09_88ba(d.x))
        d.x = -g_1df8[g_9324][n].f0c;
    if (fn_09_88ba(g_1df8[g_9324][n].f0e) < fn_09_88ba(d.y))
        d.y = -g_1df8[g_9324][n].f0e;
    if (d.x == 0 && d.y == 0) {
        if (g_1df8[g_9324][n].f0c > 0)
            d.x = -1;
        else if (g_1df8[g_9324][n].f0c < 0)
            d.x = 1;
        if (g_1df8[g_9324][n].f0e > 0)
            d.y = -1;
        else if (g_1df8[g_9324][n].f0e < 0)
            d.y = 1;
    }
    g_1df8[g_9324][n].f0c += d.x;
    g_1df8[g_9324][n].f0e += d.y;
}

/* Builds a bitmap for 0x50-record a [inferred]. */
/* @addr 11:2ff6 */
HBITMAP far fn_11_2ff6(int a)
{
    int u4;
    HDC dc;
    HDC sdc;
    HBITMAP bmp;
    int uc;
    HBITMAP src;
    HBITMAP oldsrc;
    HBITMAP old;
    int u14;
    HPALETTE oldpal;
    HPALETTE oldspal;
    int kind;
    int h;
    int w;
    int s;
    int bw;
    int width;
    int height;
    int s2;
    int bh;
    int dy;
    int by;
    int sy;
    int sx;
    BITMAP bm;

    if (a == 0)
        return 0;
    if ((g_2f4c[a].f12 == 0 || g_2f4c[a].f06 == -1) && a != 0x18) {
        bmp = fn_10_6c02(g_2f4c[a].f0a, 0, -1);
    } else {
        if (g_2f4c[a].f12) {
            w = g_2f4c[a].f00;
            h = g_2f4c[a].f02;
        } else if (a == 0x18) {
            w = g_6e24b[g_931c].f7a;
            h = g_6e24b[g_931c].f7b;
        }
        if (g_2f4c[a].f1c) {
            switch (g_2f4c[a].f1c) {
            case 1:
            case 4:
                src = fn_10_6c02(0xbf, 0, -1);
                break;
            case 2:
                src = fn_10_6c02(0xc4, 0, -1);
                break;
            case 3:
                src = fn_10_6c02(0xc5, 0, -1);
                break;
            }
        } else if (a == 0x18)
            src = fn_10_6c02(0xbd, 0, -1);
        else
            src = 0;
        if (src) {
            GetObject(src, sizeof bm, &bm);
            bw = bm.bmWidth;
            bh = bm.bmHeight;
            if (a == 0x18)
                s = w;
            else
                s = w + w;
            height = max(bh, s);
            s2 = s;
            if (height > s2) {
                dy = (height - s2) / 2;
                by = 0;
            } else {
                by = (height - bh) / 2;
                dy = 0;
            }
            width = bw + s;
            sdc = CreateCompatibleDC(g_13dc);
            if (g_920e)
                oldspal = SelectPalette(sdc, g_920e, 0);
            oldsrc = SelectObject(sdc, src);
        } else {
            kind = g_2f4c[a].f08;
            s2 = height = s = width =
                kind == 0xc4 || kind == 0xc6 || kind == 0xc3
                ? g_2f4c[a].f00 * 4 / 3 : g_2f4c[a].f00 * 2;
            dy = by = bw = bh = 0;
        }
        bmp = CreateCompatibleBitmap(g_13dc, width, height);
        dc = CreateCompatibleDC(g_13dc);
        if (g_920e)
            oldpal = SelectPalette(dc, g_920e, 0);
        old = SelectObject(dc, bmp);
        PatBlt(dc, 0, 0, width, height, BLACKNESS);
        kind = g_2f4c[a].f08;
        if (w & 1) {
            w++;
            h = 4;
        } else
            h = 6;
        h = (h << g_9156) >> 1;
        w = (w << g_9156) >> 1;
        if (g_2f4c[a].f0e == 5 || kind == 0xc6 || kind == 0xc3) {
            sx = sy = h;
        } else {
            if (g_2f4c[a].f0e == 4)
                sx = (g_2f4c[a].f2e - 1) * (w + h) + h;
            else
                sx = w * 4 + h * 5;
            sy = h;
        }
        SetStretchBltMode(dc, 3);
        if (a == 0x18)
            StretchBlt(dc, 0, dy, s, s2, g_3a38[g_9646], sx, sy, w, w,
                       SRCCOPY);
        else
            StretchBlt(dc, 0, dy, s, s2, g_39e8[g_2f4c[a].f04], sx, sy, w, w,
                       SRCCOPY);
        if (src) {
            BitBlt(dc, s, by, bw, bh, sdc, 0, 0, SRCCOPY);
            if (g_920e)
                SelectPalette(sdc, oldspal, 0);
            SelectObject(sdc, oldsrc);
            DeleteDC(sdc);
            DeleteObject(src);
            src = 0;
        }
        if (g_920e)
            SelectPalette(dc, oldpal, 0);
        SelectObject(dc, old);
        DeleteDC(dc);
        dc = 0;
    }
    return bmp;
}

/* Redraws the radar view [inferred]. */
/* @addr 11:33cc */
void far fn_11_33cc(void)
{
    int i;
    int j;
    HBRUSH old;
    RECT r;
    int got;

    if (g_93ce == 0 || !fn_11_2120())
        return;
    g_93d6 = g_9008 * 1000 / (g_0a6c + 500);
    g_93d6 = g_93d6 > 26 ? 26 : g_93d6;
    got = 0;
    if (g_13dc == 0) {
        got = 1;
        g_13dc = GetDC(g_0016);
    }
    if (g_094e)
        fn_11_367c();
    else {
        PatBlt(g_93ce, 0, 0, g_0a72, g_0a74, BLACKNESS);
        for (i = 0; i < g_9158; i++) {
            r.left = fn_11_1ab6(g_2400) * g_0a6c * g_0a64 / g_501c + g_5050;
            r.top = fn_11_1b44(g_2402) * g_0a6c * g_0a68 / g_5020 + g_5052;
            r.right = fn_11_1ab6((long)g_2400 + (g_90ea << g_9150))
                      * g_0a6c * g_0a64 / g_501c + g_5050;
            r.bottom = fn_11_1b44((long)g_2402 + (g_90ec << g_9150))
                       * g_0a6c * g_0a68 / g_5020 + g_5052;
            FrameRect(g_93ce, &r, g_5004[0]);
        }
        SetRect(&g_5048, g_5050 - g_0a72 / 2 + 1, g_5052 - g_0a74 / 2 + 1,
                g_0a72 / 2 + g_5050 - 1, g_0a74 / 2 + g_5052 - 1);
        old = SelectObject(g_93ce, g_5004[0]);
        for (i = g_9326; i <= g_9324; i++)
            for (j = 0; j < g_9406[i]; j++)
                if (g_1df8[i][j].f18 == 0 && g_1df8[i][j].f44 > 0)
                    g_1df8[i][j].f62(i, j, g_93ce);
        SelectObject(g_93ce, old);
    }
    BitBlt(g_13dc, g_90ea / 2 - 0x2b, g_8e5a + 7, g_0a72, g_0a74, g_93ce,
           0, 0, SRCCOPY);
    if (got) {
        ReleaseDC(g_0016, g_13dc);
        g_13dc = 0;
    }
}

/* Draws a bevelled frame of depth c around (l, t, rt, b); c == -1 gives a
 * depth-2 frame with a light grey fill [inferred]. */
/* @addr 11:1774 */
void far fn_11_1774(int c, int l, int t, int rt, int b)
{
    RECT r;
    HPEN old;
    HBRUSH oldbr;
    int i;
    int fill;

    if (c == -1) {
        c = 2;
        fill = 1;
    } else
        fill = 0;
    SetRect(&r, l, t, rt, b);
    old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, PALETTERGB(128, 128, 128)));
    MoveTo(g_13dc, r.left, r.bottom);
    LineTo(g_13dc, r.right, r.bottom);
    MoveTo(g_13dc, r.left + 1, r.bottom - 1);
    LineTo(g_13dc, r.right - 1, r.bottom - 1);
    LineTo(g_13dc, r.right - 1, r.top);
    MoveTo(g_13dc, r.left + c + 2, r.bottom - c - 3);
    LineTo(g_13dc, r.left + c + 2, r.top + c + 2);
    LineTo(g_13dc, r.right - c - 2, r.top + c + 2);
    if (c == 4) {
        MoveTo(g_13dc, r.right, r.bottom);
        LineTo(g_13dc, r.right, r.top);
    }
    DeleteObject(SelectObject(g_13dc, old));
    if (c != 4) {
        old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
        MoveTo(g_13dc, r.right, r.bottom);
        LineTo(g_13dc, r.right, r.top);
        SelectObject(g_13dc, old);
    }
    old = SelectObject(g_13dc, GetStockObject(WHITE_PEN));
    MoveTo(g_13dc, r.left + c + 2, r.bottom - c - 2);
    LineTo(g_13dc, r.right - c - 2, r.bottom - c - 2);
    LineTo(g_13dc, r.right - c - 2, r.top + c + 1);
    MoveTo(g_13dc, r.left, r.bottom);
    LineTo(g_13dc, r.left, r.top);
    LineTo(g_13dc, r.right, r.top);
    MoveTo(g_13dc, r.left + 1, r.bottom - 1);
    LineTo(g_13dc, r.left + 1, r.top + 1);
    LineTo(g_13dc, r.right - 1, r.top + 1);
    SelectObject(g_13dc, old);
    old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, PALETTERGB(192, 192, 192)));
    if (fill)
        oldbr = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
    else
        oldbr = SelectObject(g_13dc, GetStockObject(NULL_BRUSH));
    for (i = 0; i < c; i++)
        Rectangle(g_13dc, i + r.left + 2, i + r.top + 2, r.right - i - 1,
                  r.bottom - i - 1);
    DeleteObject(SelectObject(g_13dc, old));
    SelectObject(g_13dc, oldbr);
    SetPixel(g_13dc, r.right, r.top, PALETTERGB(128, 128, 128));
    SetPixel(g_13dc, r.right - 1, r.top + 1, PALETTERGB(192, 192, 192));
    SetPixel(g_13dc, r.left, r.bottom, PALETTERGB(192, 192, 192));
    SetPixel(g_13dc, r.left + 1, r.bottom - 1, PALETTERGB(192, 192, 192));
}

/* Draws the line sets at DS:6b5c, 6bbc and 6cfc [inferred]. */
/* @addr 11:a9ea */
void far fn_11_a9ea(int a)
{
    HPEN old;
    int u6;
    int i;
    int j;

    SetBkMode(g_13dc, OPAQUE);
    if (g_1016 > 0)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
    else {
        if (a) {
            if (g_1318 > 1)
                fn_10_754a(0x22, g_6b5c[0].x, g_6b5c[0].y, 4);
            else
                fn_10_754a(0x22, g_951e, g_9520, 1);
        }
        if (a && g_951e == 9)
            old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
        else
            old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(127, 255, 255)));
    }
    for (i = 1; i < fn_09_88ba(g_1016); i++)
        fn_12_7256(g_13dc, g_6b5c[i - 1], g_6b5c[i]);
    DeleteObject(SelectObject(g_13dc, old));
    if (g_1016 > 0)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
    else if (a && g_951e == 9)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));
    else
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(127, 255, 255)));
    for (i = 0; i < g_9526; i++)
        for (j = 1; j < 5; j++)
            fn_12_7256(g_13dc, g_6bbc[i][j - 1], g_6bbc[i][j]);
    for (i = 0; i < g_9528; i++)
        for (j = 1; j < 3; j++)
            fn_12_7256(g_13dc, g_6cfc[i][j - 1], g_6cfc[i][j]);
    DeleteObject(SelectObject(g_13dc, old));
    if (g_1016 > 0 && g_1036 == 0) {
        old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
        for (i = 0; i < g_9526; i++)
            for (j = 1; j < 5; j++)
                fn_12_7256(g_13dc, g_6bbc[i][j - 1], g_6bbc[i][j]);
        for (i = 0; i < g_9528; i++)
            for (j = 1; j < 3; j++)
                fn_12_7256(g_13dc, g_6cfc[i][j - 1], g_6cfc[i][j]);
        SelectObject(g_13dc, old);
        g_1016 = -g_1016;
    } else if (g_1036 == 0) {
        g_1036 = 1;
        g_1016 = -g_1016;
    } else
        g_1036 = g_1016 = 0;
}

/* Spawns rings of 20-byte effect records around object n [inferred]. */
/* @addr 11:8a42 */
void far fn_11_8a42(int type, int n)
{
    int w;
    int m;
    int j;
    int i;
    int k;
    int sk;
    int r;
    int sr;
    int k8;
    int r8;
    int step;
    int delay;
    struct { POINT a, b; } rc;
    int ok;

    w = 0x50;
    delay = 0x1e;
    ok = j = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].fcb; j++)
            if (g_7090[n].fb8[j] == 1) {
                if (g_7090[n].f1e > 70)
                    ok = 1;
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    if (type == g_9324)
        g_7090[n].f1e += -70L * g_1df8[14][n].f44 / 250;
    rc.b = g_1df8[type][n].f04;
    rc.a = *(POINT far *)&g_1df8[type][n].f00;
    for (k = 11, step = 0; k < w * 10 / 14; k += 21, step++) {
        r = fn_08_1290((long)(w * w - k * k), (long)(w - k / 4));
        k8 = k * 8;
        sk = SC(k);
        r8 = r * 8;
        sr = SC(r);
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x + k8;
                g_5170[i].x = rc.a.x + sk;
                g_5224[i].y = rc.b.y - r8;
                g_5170[i].y = rc.a.y - sr;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = delay * step + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x + r8;
                g_5170[i].x = rc.a.x + sr;
                g_5224[i].y = rc.b.y - k8;
                g_5170[i].y = rc.a.y - sk;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (5 - step) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x + r8;
                g_5170[i].x = rc.a.x + sr;
                g_5224[i].y = rc.b.y + k8;
                g_5170[i].y = rc.a.y + sk;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (step + 5) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x + k8;
                g_5170[i].x = rc.a.x + sk;
                g_5224[i].y = rc.b.y + r8;
                g_5170[i].y = rc.a.y + sr;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (10 - step) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x - k8;
                g_5170[i].x = rc.a.x - sk;
                g_5224[i].y = rc.b.y - r8;
                g_5170[i].y = rc.a.y - sr;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (20 - step) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x - r8;
                g_5170[i].x = rc.a.x - sr;
                g_5224[i].y = rc.b.y - k8;
                g_5170[i].y = rc.a.y - sk;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (step + 15) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x - r8;
                g_5170[i].x = rc.a.x - sr;
                g_5224[i].y = rc.b.y + k8;
                g_5170[i].y = rc.a.y + sk;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (15 - step) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x - k8;
                g_5170[i].x = rc.a.x - sk;
                g_5224[i].y = rc.b.y + r8;
                g_5170[i].y = rc.a.y + sr;
                g_1e90[i].f0 = g_1e90[i].fa = 1;
                g_1e90[i].f2 = 10;
                g_1e90[i].f10 = (step + 10) * delay + g_1e50;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_9430++;
                break;
            }
        j = i + 1;
    }
    for (m = 0; m < 2; m++) {
        for (i = j; i < 45; i++)
            if (g_1e90[i].f0 == -1) {
                g_5224[i].x = rc.b.x;
                g_5170[i].x = rc.a.x;
                g_5224[i].y = rc.b.y;
                g_5170[i].y = rc.a.y;
                g_1e90[i].fa = -250;
                if (i > g_9434)
                    g_9434 = i;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = n;
                g_1e90[i].f0 = 1;
                g_1e90[i].f2 = 13;
                g_1e90[i].f10 = (15 - step) * delay * m + g_1e50;
                g_9430++;
                break;
            }
        j = i + 1;
    }
}

/* Turns nearby 0x1c-records into kind 0x1b and builds its bitmap
 * [inferred]. */
/* @addr 11:9078 */
void far fn_11_9078(int type, int n)
{
    int i;
    int pa;
    int pb;
    int dist;
    int kind;
    int j;
    BITMAP bm;
    HDC dc;
    HBITMAP bmp;
    HBITMAP oldbmp;
    HPALETTE oldpal;
    int found;
    int ok;

    ok = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].fcb; j++)
            if (g_7090[n].fb8[j] == 0xd || g_7090[n].fb8[j] == 0x17) {
                ok = 1;
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    for (i = 0; i < g_9412; i++) {
        if (g_66e4[i].f08 > 0 && g_2f4c[g_66e4[i].f00].f26 > g_66e4[i].f08
            && g_66e4[i].f00 != 0x1b
            && (dist = fn_08_285a(&pa, &pb, g_1df8[type][n].f04,
                                  g_1df8[6][i].f04)) < 0x28a) {
            PatBlt(g_13dc, g_1df8[6][i].f00, g_1df8[6][i].f02, g_1df8[6][i].f22,
                   g_1df8[6][i].f22, BLACKNESS);
            kind = g_66e4[i].f00;
            found = -1;
            for (j = 0; j < g_9412; j++)
                if (g_66e4[j].f08 > 0 && g_2f4c[g_66e4[j].f00].f26 > g_66e4[j].f08
                    && g_66e4[j].f00 == 0x1b)
                    found = j;
            g_66e4[i].f00 = 0x1b;
            g_66e4[i].f08 = 1;
            g_66e4[i].f0a = g_2f4c[0x1b].f26;
            g_2f4c[0x1b].f04 = 0x39;
            g_2f4c[0x1b].f2c = 5;
            g_1df8[6][i].f66 = fn_12_6a60;
            if (found == -1) {
                if (g_39e8[g_2f4c[0x1b].f04]) {
                    SelectObject(g_39e8[g_2f4c[0x1b].f04], g_3974[g_2f4c[0x1b].f04]);
                    if (g_920e)
                        SelectPalette(g_39e8[g_2f4c[0x1b].f04],
                                      g_3a5c[g_2f4c[0x1b].f04], 0);
                    DeleteDC(g_39e8[g_2f4c[0x1b].f04]);
                    g_39e8[g_2f4c[0x1b].f04] = 0;
                    DeleteObject(g_3ad0[g_2f4c[0x1b].f04]);
                    g_3ad0[g_2f4c[0x1b].f04] = 0;
                }
                bmp = fn_10_6c02(rand() % 3 + 0x294, 0, -1);
                dc = CreateCompatibleDC(g_13dc);
                g_39e8[g_2f4c[0x1b].f04] = CreateCompatibleDC(g_13dc);
                if (g_920e) {
                    g_3a5c[g_2f4c[0x1b].f04] =
                        SelectPalette(g_39e8[g_2f4c[0x1b].f04], g_920e, 0);
                    oldpal = SelectPalette(dc, g_920e, 0);
                }
                GetObject(bmp, sizeof bm, &bm);
                g_1df8[6][i].f22 = bm.bmHeight;
                if (bm.bmHeight & 1)
                    g_1df8[6][i].f24 = 5;
                else
                    g_1df8[6][i].f24 = 6;
                g_3ad0[g_2f4c[0x1b].f04] = CreateCompatibleBitmap(g_13dc,
                    g_1df8[6][i].f24 * 2 + g_1df8[6][i].f22,
                    g_1df8[6][i].f24 * 2 + g_1df8[6][i].f22);
                oldbmp = SelectObject(dc, bmp);
                g_3974[g_2f4c[0x1b].f04] = SelectObject(g_39e8[g_2f4c[0x1b].f04],
                                                        g_3ad0[g_2f4c[0x1b].f04]);
                PatBlt(g_39e8[g_2f4c[0x1b].f04], 0, 0,
                       g_1df8[6][i].f24 * 2 + g_1df8[6][i].f22,
                       g_1df8[6][i].f24 * 2 + g_1df8[6][i].f22, BLACKNESS);
                BitBlt(g_39e8[g_2f4c[0x1b].f04], g_1df8[6][i].f24,
                       g_1df8[6][i].f24, g_1df8[6][i].f22, g_1df8[6][i].f22, dc,
                       0, 0, SRCCOPY);
                SelectObject(dc, oldbmp);
                if (g_920e)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
                DeleteObject(bmp);
                fn_10_6308(g_2f4c[0x1b].f04, -1, -1, -1);
                g_1df8[6][i].f20 = g_1df8[6][i].f22 * 8;
                if (g_1df8[6][i].f22 & 1) {
                    g_1df8[6][i].f22 = (g_1df8[6][i].f22 + 1 << g_9156) >> 1;
                    g_1df8[6][i].f24 = (4 << g_9156) >> 1;
                } else
                    g_1df8[6][i].f24 = (6 << g_9156) >> 1;
            } else {
                g_1df8[6][i].f22 = g_1df8[6][found].f22;
                g_1df8[6][i].f24 = g_1df8[6][found].f24;
            }
        }
    }
}

/* Paints the target panel (control 0xd2) and the weapon panel (control
 * 0xdc) [inferred]. */
/* @addr 11:238e */
void far fn_11_238e(HWND hwnd, HDC dc)
{
    BITMAP bm;
    HFONT oldfont;
    HPEN oldpen;
    COLORREF oldcolor;
    char buf[140];
    char tmp[48];
    HDC memdc;
    HBITMAP oldbmp;
    HPALETTE oldpal2;
    HPALETTE oldpal;
    RECT rc;
    int id;
    int rel;
    int xoff;
    int yoff;
    int type;
    int n;
    int got;
    int kind;

    got = 0;
    if (dc == 0) {
        got = 1;
        dc = GetDC(hwnd);
    }
    if (g_920e)
        oldpal = SelectPalette(dc, g_920e, 0);
    id = GetDlgCtrlID(hwnd);
    GetClientRect(hwnd, &rc);
    PatBlt(dc, 0, 0, rc.right, rc.bottom, BLACKNESS);
    switch (id) {
    case 0xd2:
        oldfont = SelectObject(dc, g_90fe);
        SetTextAlign(dc, TA_LEFT);
        SetBkMode(dc, TRANSPARENT);
        if (g_90ee == 1)
            oldcolor = SetTextColor(dc, RGB(255, 255, 255));
        else
            oldcolor = SetTextColor(dc, RGB(0, 255, 0));
        switch (g_0a76) {
        case 2:
            if (g_094e) {
                fn_11_41bc(dc, 1, 1);
                break;
            }
            if (!fn_03_0000(type = g_6e54, n = g_6e52) && !fn_13_371c(type, n))
                g_9498++;
            fn_11_2ce6(dc, 0);
            fn_13_58dc(dc, 1);
            if (g_90ea < 700) {
                xoff = 12;
                lstrcpy(buf, "");
            } else {
                xoff = 15;
                LoadString(g_9212, 0x3a2, tmp, 40);
                lstrcpy(buf, tmp);
            }
            LoadString(g_9212, 0x3a3, tmp, 40);
            lstrcat(buf, tmp);
            if (g_0a62 == 0)
                LoadString(g_9212, 0x3a4, tmp, 40);
            else
                LoadString(g_9212, 0x3a5, tmp, 40);
            lstrcat(buf, tmp);
            lstrcat(buf, ")");
            TextOut(dc, 1, 0, buf, lstrlen(buf));
            SetTextAlign(dc, TA_RIGHT);
            TextOut(dc, g_5024 - xoff, 0x12, g_9628, lstrlen(g_9628));
            if (g_9324 == g_6e54) {
                rel = fn_13_2688(g_6e52, g_9646);
                if (rel > 80)
                    SetTextColor(dc, PALETTERGB(0, 0xb9, 0xff));
                else if (rel < -80)
                    SetTextColor(dc, PALETTERGB(0xff, 0x6e, 0));
                else
                    SetTextColor(dc, PALETTERGB(0xaa, 0xaa, 0xaa));
            } else
                SetTextColor(dc, RGB(0, 128, 0));
            TextOut(dc, g_5024 - xoff, 0x20, g_8718, lstrlen(g_8718));
            TextOut(dc, g_5024 - xoff, 0x2e, g_960a, lstrlen(g_960a));
            if (g_6e54 == g_9324) {
                fn_11_3f2e(rel);
                TextOut(dc, g_5024 - xoff, 0x3c, g_93e0, lstrlen(g_93e0));
            }
            break;
        case 3:
            fn_11_2ce6(dc, 1);
            fn_13_58dc(dc, 1);
            if (g_90ea < 700)
                xoff = 12;
            else
                xoff = 15;
            LoadString(g_9212, 0x3a1, tmp, 40);
            lstrcpy(buf, tmp);
            TextOut(dc, 1, 0, buf, lstrlen(buf));
            SetTextAlign(dc, TA_LEFT);
            if (g_6e72 == g_9324) {
                rel = fn_13_2688(g_6e70, g_9646);
                if (rel > 80)
                    SetTextColor(dc, PALETTERGB(0, 0xb9, 0xff));
                else if (rel < -80)
                    SetTextColor(dc, PALETTERGB(0xff, 0x6e, 0));
                else
                    SetTextColor(dc, PALETTERGB(0xaa, 0xaa, 0xaa));
                TextOut(dc, 1, 0x12, g_8740, lstrlen(g_8740));
                fn_11_3f2e(rel);
                if (g_6e70 != g_9646)
                    TextOut(dc, 1, 0x20, g_93e0, lstrlen(g_93e0));
            } else {
                SetTextColor(dc, RGB(0, 128, 0));
                TextOut(dc, 1, 0x12, g_8740, lstrlen(g_8740));
            }
            SetTextColor(dc, RGB(255, 255, 0));
            TextOut(dc, 1, 0x2e, g_8768, lstrlen(g_8768));
            TextOut(dc, 1, 0x3c, g_87b8, lstrlen(g_87b8));
            oldpen = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 128, 0)));
            MoveTo(dc, 0, 14);
            LineTo(dc, 80, 14);
            DeleteObject(SelectObject(dc, oldpen));
            break;
        case 4:
            LoadString(g_9212, 0x3a0, tmp, 40);
            lstrcpy(buf, tmp);
            TextOut(dc, 1, 0, buf, lstrlen(buf));
            if (g_059c == 1200) {
                LoadString(g_9212, 0x88f, buf, 140);
                lstrcpy(buf, buf);
            } else {
                fn_06_0f1a(g_059c, buf);
                LoadString(g_9212, 0x39f, tmp, 40);
                lstrcat(buf, tmp);
                LoadString(g_9212, 0x890, tmp, 40);
                lstrcat(buf, tmp);
            }
            TextOut(dc, 1, 0x16, buf, lstrlen(buf));
            fn_06_0f1a(g_059a, buf);
            LoadString(g_9212, 0x39f, tmp, 40);
            lstrcat(buf, tmp);
            LoadString(g_9212, 0x891, tmp, 40);
            lstrcat(buf, tmp);
            TextOut(dc, 1, 0x26, buf, lstrlen(buf));
            break;
        }
        SetTextColor(dc, oldcolor);
        SelectObject(dc, oldfont);
        if (g_0a76 != 3) {
            oldpen = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 128, 0)));
            MoveTo(dc, 0, 14);
            LineTo(dc, rc.right, 14);
            DeleteObject(SelectObject(dc, oldpen));
        }
        break;
    case 0xdc:
        oldfont = SelectObject(dc, g_90fe);
        SetTextAlign(dc, TA_LEFT);
        SetBkMode(dc, TRANSPARENT);
        oldcolor = SetTextColor(dc, RGB(255, 0, 0));
        LoadString(g_9212, 0x3a6, tmp, 40);
        lstrcpy(buf, tmp);
        TextOut(dc, 1, 0, buf, lstrlen(buf));
        if (g_2f4c[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f12
            && g_2f4c[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f36 == 0) {
            fn_06_0f1a(g_7090[g_9646].fae[g_7090[g_9646].f18], buf);
            lstrcat(buf, " - ");
            LoadString(g_9212,
                       g_2f4c[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f08,
                       tmp, 40);
            lstrcat(buf, tmp);
        } else {
            kind = g_2f4c[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f08;
            if (kind != 0xc9 && kind != 0xba && kind != 0xbc)
                LoadString(g_9212, 0x3a7, buf, 40);
            else
                lstrcpy(buf, "");
            LoadString(g_9212, kind, tmp, 40);
            lstrcat(buf, tmp);
        }
        TextOut(dc, 1, 0x11, buf, lstrlen(buf));
        SetTextColor(dc, oldcolor);
        SelectObject(dc, oldfont);
        oldpen = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(255, 0, 255)));
        MoveTo(dc, 0, 15);
        LineTo(dc, rc.right, 15);
        DeleteObject(SelectObject(dc, oldpen));
        if (g_5040) {
            GetObject(g_5040, sizeof bm, &bm);
            memdc = CreateCompatibleDC(g_13dc);
            oldbmp = SelectObject(memdc, g_5040);
            if (g_920e)
                oldpal2 = SelectPalette(memdc, g_920e, 0);
            kind = g_2f4c[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f08;
            if (g_2f4c[g_7090[g_9646].fb8[g_7090[g_9646].f18]].f12
                && kind != 0xc4 && kind != 0xc6 && kind != 0xcb)
                yoff = 0x1c;
            else if (kind == 0xcb)
                yoff = 0x28;
            else
                yoff = 0x23;
            BitBlt(dc, g_5026 / 2 - bm.bmWidth / 2, yoff, bm.bmWidth,
                   bm.bmHeight, memdc, 0, 0, SRCPAINT);
            SelectObject(memdc, oldbmp);
            if (oldpal2)
                SelectPalette(memdc, oldpal2, 0);
            DeleteDC(memdc);
        }
        break;
    }
    if (oldpal)
        SelectPalette(dc, oldpal, 0);
    if (got) {
        ReleaseDC(hwnd, dc);
        dc = 0;
    }
}

/* Picks the best target in range and in the facing direction of object
 * (type, n), for weapon kind 3 [inferred]. */
/* @addr 11:9fdc */
void far fn_11_9fdc(int type, int n)
{
    int bt;
    int bn;
    int best;
    int i;
    int j;
    int dir;
    int range;
    int pa;
    int pb;
    int dist;
    int val;
    int u1a;
    int u1c;
    int u1e;
    int u20;
    int ok;

    ok = 0;
    if (type == g_9324) {
        for (i = 1; i < g_7090[n].fcb; i++)
            if (g_7090[n].fb8[i] == 3 && g_7090[n].f1e > g_2f4c[3].f36) {
                ok = 1;
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    range = min(g_1df8[type][n].f50 * 4, g_90ea / 2);
    if (type == g_9324 && n == g_9646)
        range = max(range, 150);
    bt = -1;
    best = 0;
    for (i = g_9326; i <= g_9324; i++) {
        if (i != 5 && i != 12) {
            for (j = 0; j < g_9406[i]; j++) {
                if (g_1df8[i][j].f18 == 0 && (i != type || j != n)
                    && (dist = fn_08_285a(&pa, &pb, g_1df8[type][n].f04,
                                          g_1df8[i][j].f04)) < range
                    && g_1df8[type][n].f28 >= (dir = fn_08_19b0(pa, pb)) - 1
                    && g_1df8[type][n].f28 <= dir + 1) {
                    val = g_1df8[i][j].f44;
                    if (type == 14 && g_7090[n].f38 == 1 && g_7090[n].f32 == i
                        && g_7090[n].f34 == j)
                        val *= 4;
                    val = (long)(range - dist) * val / range;
                    if (g_1df8[i][j].f44 > best) {
                        bt = i;
                        bn = j;
                        best = g_1df8[i][j].f44;
                    }
                }
            }
        }
    }
    if (bt >= 0) {
        if (type == 14)
            g_7090[n].f1e = max(g_7090[n].f1e - g_2f4c[3].f36, 0);
        fn_11_a234(type, n, bt, bn);
    }
    if (type == 6 && g_66e4[n].f04 == bt && bt == g_9324
        && g_66e4[n].f06 == bn)
        g_66e4[n].f08 = g_2f4c[g_66e4[n].f00].f26 - 1;
}

/* Object (type, n) hits object (tt, tn) with its beam [inferred]. */
/* @addr 11:a234 */
void far fn_11_a234(int type, int n, int tt, int tn)
{
    POINT a;
    POINT b;
    POINT pa;
    POINT pb;
    POINT u14;
    int dmg;
    POINT u1a;
    POINT c;

    if (g_1016)
        return;
    c.x = g_2400 >> 3;
    c.y = g_2402 >> 3;
    g_9520 = n;
    g_951e = type;
    if (g_9406[type] <= n) {
        g_9498++;
        return;
    }
    fn_10_754a(0x22, g_951e, g_9520, 1);
    if (type == g_9324) {
        a.x = g_7b60[g_7090[n].f4e][g_1df8[type][n].f28].x * 8
              + g_1df8[type][n].f04.x;
        a.y = g_7b60[g_7090[n].f4e][g_1df8[type][n].f28].y * 8
              + g_1df8[type][n].f04.y;
    } else {
        a.x = g_1df8[type][n].f20 / 2 + g_1df8[type][n].f04.x;
        a.y = g_1df8[type][n].f20 / 2 + g_1df8[type][n].f04.y;
    }
    b.x = g_1df8[tt][tn].f20 / 2 + g_1df8[tt][tn].f04.x;
    b.y = g_1df8[tt][tn].f20 / 2 + g_1df8[tt][tn].f04.y;
    pa = fn_08_29ea(a);
    fn_11_a4a6(pa, pb = fn_08_29ea(b), type);
    if (type == 9)
        dmg = rand() % (g_1df8[type][n].f50 / 2) + g_1df8[type][n].f50 / 3;
    else
        dmg = g_1df8[type][n].f50;
    if (type == 9 && tt == 0)
        fn_07_2512(tn, 0);
    fn_08_5df2(tt, tn, g_943a = type, g_943c = n, dmg / 2 + 2000);
    if (tt != g_9324)
        g_1df8[tt][tn].f50 = dmg * 3 / 5;
    if (type == g_9324 && n == g_9646)
        dmg /= 3;
    g_1df8[type][n].f50 -= dmg;
    if (type == g_9324 && g_96ea[g_7090[n].f4e].f20 == 7) {
        g_1df8[tt][tn].f50 = 0;
        g_1df8[type][n].f50 = 0;
    }
}

/* Blits the 16 cells of object n's ring sprite (a: second row) [inferred]. */
/* @addr 11:b09c */
void far pascal fn_11_b09c(int n, int a)
{
    int i;
    int h;
    int g;
    int x;
    int y;
    int cls;
    int idx;
    int unused;
    int off;
    int sz;
    int flag;
    int unused2;

    flag = 1;
    cls = g_7090[n].f4e;
    g = g_1df8[g_9324][n].f24;
    h = g_1df8[g_9324][n].f22;
    if (a)
        g_1df8[g_9324][n].f2f = g_7090[n].f0c / 20;
    else
        g_1df8[g_9324][n].f2f = 0;
    if (g_7090[n].f10 > 0 && g_7090[n].f10 < 7)
        flag = 0;
    if (g_7090[n].fe4) {
        if (g_9130)
            sz = g_9156 * 6 + 3;
        else
            sz = SC(9);
        for (i = 0; i < 16; i++) {
            if (flag || g_1df8[g_9324][n].f28 == i) {
                if (i < 5) {
                    x = g_96ea[cls].f38[i].x;
                    y = g_96ea[cls].f38[i].y;
                } else if (i < 9) {
                    x = g_96ea[cls].f38[8 - i].x;
                    y = h - g_96ea[cls].f38[8 - i].y - sz;
                } else if (i < 12) {
                    x = h - g_96ea[cls].f38[i - 8].x - sz;
                    y = h - g_96ea[cls].f38[i - 8].y - sz;
                } else {
                    x = h - g_96ea[cls].f38[16 - i].x - sz;
                    y = g_96ea[cls].f38[16 - i].y;
                }
                idx = n + 40;
                if (g_7090[n].f10 > 3)
                    off = g + h;
                else
                    off = 0;
                if (flag == 0) {
                    BitBlt(g_39e8[idx], h * 16 + g * 17 + x, y + g, sz, sz,
                           g_39e8[34], sz * i, (n * 2 + a) * sz, SRCCOPY);
                    BitBlt(g_39e8[idx], h * 16 + g * 17 + x, g * 2 + y + h, sz, sz,
                           g_39e8[34], sz * i, (n * 2 + a) * sz, SRCCOPY);
                } else
                    BitBlt(g_39e8[idx], (g + h) * i + x + g, off + y + g, sz, sz,
                           g_39e8[34], sz * i, (n * 2 + a) * sz, SRCCOPY);
            }
        }
    }
}

/* Builds and draws a random lightning bolt from a to b with side branches (type 9: green) [inferred]. */
/* @addr 11:a4a6 */
void far fn_11_a4a6(POINT a, POINT b, int type)
{
    POINT d;
    POINT p;
    int i;
    int len;
    int seg;
    int j;
    int k;
    HGDIOBJ old;
    int unused;

    srand((unsigned)GetCurrentTime());
    g_9526 = g_9528 = 0;
    seg = 30;
    p.x = -(d.y = b.y - a.y);
    p.y = d.x = b.x - a.x;
    len = fn_08_1290((long)d.y * d.y + (long)d.x * d.x,
                     (long)(fn_09_88ba(d.x) + fn_09_88ba(d.y)));
    if (len / seg > 22) {
        seg = 50;
        if (len / seg > 22)
            return;
    }
    for (i = 0; i < len / seg; i++) {
        if (i > 0) {
            g_6b5c[i].x = (long)(rand() % 10 + (i + 1) * seg - 5) * d.x / len
                        + (long)(rand() % 26 - 13) * p.x / len + a.x;
            g_6b5c[i].y = (long)(rand() % 10 + (i + 1) * seg - 5) * d.y / len
                        + (long)(rand() % 26 - 13) * p.y / len + a.y;
        } else
            g_6b5c[0] = a;
        if (rand() % 3 == 0) {
            g_6bbc[g_9526][0] = g_6b5c[i];
            for (j = 1; j < 5; j++) {
                g_6bbc[g_9526][j].x = (long)((i % 2 * 32 - 16) * j + rand() % 24 - 12) * p.x / len
                    + (long)(rand() % 15 + j * 15) * d.x / len + g_6b5c[i].x;
                g_6bbc[g_9526][j].y = (long)(rand() % 24 + (i % 2 * 32 - 16) * j - 12) * p.y / len
                    + (long)(rand() % 15 + j * 15) * d.y / len + g_6b5c[i].y;
            }
            g_9526++;
            if (g_9526 > 16)
                return;
            if (rand() % 5 <= 3) {
                g_6cfc[g_9528][0] = g_6bbc[g_9526 - 1][2];
                for (k = 1; k < 3; k++) {
                    g_6cfc[g_9528][k].x = (long)(((k + 2) * (i % 2) * 2 - k) * 12 + rand() % 16 - 32) * p.x / len
                        + (long)(rand() % 15 + (k + 2) * 15) * d.x / len + g_6cfc[g_9528][0].x;
                    g_6cfc[g_9528][k].y = (long)(rand() % 16 + ((k + 2) * (i % 2) * 2 - k) * 12 - 32) * p.y / len
                        + (long)(rand() % 15 + (k + 2) * 15) * d.y / len + g_6cfc[g_9528][0].y;
                }
                g_9528++;
            }
        }
    }
    g_6b5c[i] = b;
    if (type == 9)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
    else
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(195, 255, 255)));
    for (j = 1; j < i + 1; j++)
        fn_12_7256(g_13dc, g_6b5c[j - 1], g_6b5c[j]);
    DeleteObject(SelectObject(g_13dc, old));
    if (type == 9)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));
    else
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(195, 255, 255)));
    for (j = 0; j < g_9526; j++)
        for (k = 1; k < 5; k++)
            fn_12_7256(g_13dc, g_6bbc[j][k - 1], g_6bbc[j][k]);
    for (j = 0; j < g_9528; j++)
        for (k = 1; k < 3; k++)
            fn_12_7256(g_13dc, g_6cfc[j][k - 1], g_6cfc[j][k]);
    DeleteObject(SelectObject(g_13dc, old));
    g_1016 = i + 1;
}

/* Finds the earliest crossing of ship i's path with a link segment (best time into f90) and reflects its velocity into f88/f8a [inferred]. */
/* @addr 11:5626 */
void far fn_11_5626(int i)
{
    long A;
    long B;
    long C;
    long D;
    long E;
    long F;
    long G;
    long dummy;
    long t;
    long H;
    long best;
    long den;
    long u;
    int j;
    int unused;

    best = 50000L;
    if (g_9320 != 6 || g_9eb5 != 0)
        return;
    C = (long)g_6098[i].f70;
    D = (long)g_6098[i].f72;
    if (C == 0)
        C = 1;
    if (D == 0)
        D = 1;
    dummy = fn_08_35d0(C, D);
    for (j = 0; j < g_9eb9[g_9322]; j++) {
        if (g_9ec2[g_9322][j] != j) {
            A = (long)(g_1df8[8][j + 2].f04.x - g_6098[i].x1[0][0] + 56);
            B = (long)(g_1df8[8][j + 2].f04.y - g_6098[i].y1[0][0] + 56);
            E = (long)(g_1df8[8][g_9ec2[g_9322][j] + 2].f04.x - g_1df8[8][j + 2].f04.x + 56);
            F = (long)(g_1df8[8][g_9ec2[g_9322][j] + 2].f04.y - g_1df8[8][j + 2].f04.y + 56);
            G = (long)fn_08_35d0(E, F);
            den = E * D - F * C;
            if (den == 0)
                den = 1;
            H = (C * B - D * A) / 20 * G / den * 20;
            if (H >= 0 && H <= G) {
                if (abs32(D) < abs32(C))
                    t = (H * E / G + A) / C;
                else
                    t = (H * F / G + B) / D;
                if (t >= 0 && t < best) {
                    best = t;
                    u = (F * C - E * D) / G;
                    g_6098[i].f88 = C - u * F * 2 / G;
                    g_6098[i].f8a = u * E * 2 / G + D;
                }
            }
        }
    }
    if (best != 50000L)
        g_6098[i].f90 = best + g_05cc;
}

/* Ship n's thrust step: afterburner on Ctrl (a != 1 also applies thrust to the velocity and checks for a hard turn) [inferred]. */
/* @addr 11:63b4 */
void far pascal fn_11_63b4(int n, int a)
{
    int u1;
    int u2;
    int j;
    int k;
    int key;
    int e;
    int p;
    int m;
    int s;
    int t;
    POINT v;
    POINT dv;
    char buf[40];
    long len;
    long cr;
    long tq;

    if (g_9e49 >= 1 && g_9e49 <= 6 && n == g_952e && g_9130 == 0)
        return;
    if (g_7090[n].f90 < g_1e50) {
        g_7090[n].f90 = g_1e50 + 250;
        if (g_7090[n].f02 == 0) {
            fn_11_b09c(n, g_7090[n].f02 = 1);
            g_1df8[g_9324][n].f26 = 0;
            g_7090[n].f12 = 0;
            fn_13_6716(n);
        }
    }
    if (g_9134)
        key = 0;
    else
        key = GetAsyncKeyState(VK_CONTROL);
    if (n == g_9646 && g_103e)
        g_952a = 1;
    if (g_7090[n].f60 < 4) {
        if (((key & 0x8000) && n == g_9646 || g_952a) && g_7090[n].f1e >= 30) {
            if (g_1df8[g_9324][n].f1a != 0) {
                fn_10_754a(0x29, g_9324, n, 1);
                for (j = 0; j < 10; j++)
                    for (k = 0; k < 4; k++) {
                        g_5b28[j][k].age = 0;
                        g_5b28[j][k].q.x = g_5b28[j][k].q.y = -100;
                    }
                g_9512 = g_9324;
                g_9514 = n;
                g_9510 = 0;
                if (g_9134 != 0 && g_9134 != 2 && n == g_9646 && g_7090[n].f3a == 5
                    && g_7090[n].f06 == 8 && g_3d54[g_7090[n].f08].f06 == -3) {
                    LoadString(g_9212, 0x203, buf, 40);
                    lstrcpy(g_8630, buf);
                    LoadString(g_9212, 0x204, buf, 40);
                    lstrcat(g_8630, buf);
                    g_058c = 1;
                    g_05c0 = g_1e50 + 1200;
                }
                if (g_7090[n].f60 && (n != g_9646 || g_9134))
                    g_7090[n].f60 = 0x1c;
                else
                    g_7090[n].f60 = 8;
            }
            g_7090[n].f1c = 5;
            g_7090[n].f1e -= 25;
        }
    }
    if (a != 1) {
        e = g_1df8[g_9324][n].f28;
        m = g_1df8[g_9324][n].f44;
        p = g_7090[n].f1c;
        if (p > 1 && g_7090[n].f3a == 5)
            p += 2;
        s = g_7090[n].f0c;
        if (g_7090[n].fd6 != -1)
            s = (long)((g_6e24[g_7090[n].fd6].f33 + 10) * 10) * s / 100;
        if (g_7090[n].f26[2] == 0)
            s /= 3;
        else if (g_7090[n].f1e == 0)
            s /= 3;
        else if (g_7090[n].f26[2] < 35)
            s -= (40 - g_7090[n].f26[2]) * s >> 6;
        if (s < 1)
            s = 1;
        t = g_7090[n].f0e;
        v = *(POINT far *)&g_1df8[g_9324][n].f0c;
        dv.x = (g_1050[e].x * s * p - t * v.x) / m;
        dv.y = (g_1050[e].y * s * p - t * v.y) / m;
        g_1df8[g_9324][n].f0c += dv.x;
        g_1df8[g_9324][n].f0e += dv.y;
        if (g_9320 == 6 && g_1c3e < g_1e50 && g_9eb5 == 0) {
            len = fn_08_35d0((long)v.x, (long)v.y);
            cr = ((long)dv.y * v.x - (long)dv.x * v.y) / len;
            tq = cr * g_1df8[14][n].f44;
            if (p > 2)
                tq /= 3;
            if (abs32(tq) > 2950 && abs32(cr * 5) < len) {
                if (rand() % 1000 + 3100 < abs32(tq))
                    fn_10_754a(0x28, 0xe, n, 1);
                g_1c3e = g_1e50 + 1500;
            }
        }
    }
    g_1df8[g_9324][n].f2f = s * p / 20;
}

/* Race HUD: lap count, position line, lap times and the start countdown [inferred]. */
/* @addr 11:41bc */
void far fn_11_41bc(HDC dc, int a, int b)
{
    char buf1[240];
    char buf2[200];
    int i;
    int rank;
    int left;
    int laps;
    DWORD tm;
    long col;
    POINT pt;
    char buf3[6];

    if (b) {
        if (a)
            SetBkMode(dc, TRANSPARENT);
        else
            SetBkMode(dc, OPAQUE);
        if (a) {
            fn_06_0f1a(g_9ea0, buf1);
            fn_09_9580(0x892, buf1);
            lstrcat(buf1, g_38c8);
            for (i = lstrlen(g_38c8) - 1; i > 2; i--)
                if (g_38c8[i] == '-') {
                    g_38c8[i - 1] = 0;
                    break;
                }
            TextOut(dc, 1, 0, buf1, lstrlen(buf1));
        }
        SetTextColor(dc, RGB(255, 255, 0));
        race_position();
        fn_17_7ba6(g_9684, buf1);
        fn_09_9580(0x893, buf1);
        if (g_9eb4 == 0)
            rank = 1;
        else if (g_7090[g_9646].fda < 0)
            rank = -g_7090[g_9646].fda;
        else
            rank = g_7090[g_9646].fda + 1;
        left = g_9ea0 - rank + 1;
        if (left != 0 && g_1df8[14][g_9646].f51 == 0) {
            lstrcat(buf1, " ");
            if (left == 1)
                fn_09_9580(0x894, buf1);
            else {
                fn_06_0f1a(left, buf2);
                lstrcat(buf1, buf2);
                fn_09_9580(0x895, buf1);
            }
        }
        if (lstrcmp(g_9628, buf1) != 0) {
            buf1[30] = 0;
            lstrcpy(g_9628, buf1);
            PatBlt(dc, 1, 18, 270, 14, BLACKNESS);
        }
        TextOut(dc, 1, 18, g_9628, lstrlen(g_9628));
        SetTextColor(dc, RGB(0, 255, 0));
    }
    if (g_9eb4 != 0 && b != 0) {
        if (g_9e90[g_9646] != 0) {
            LoadString(g_9212, 0x896, buf1, 240);
            fn_11_4928(0, g_9e90[g_9646], buf2);
            lstrcat(buf1, buf2);
            TextOut(dc, 1, 32, buf1, lstrlen(buf1));
        }
        if (g_1df8[14][g_9646].f51)
            laps = g_9ea0;
        else if (g_7090[g_9646].fda < 0)
            laps = -g_7090[g_9646].fda;
        else
            laps = g_7090[g_9646].fda + 1;
        if (g_9e70[g_9646] + 140 > g_1e68 && g_9e90[g_9646] != 0
            || g_1df8[14][g_9646].f51 != 0) {
            if (g_1df8[14][g_9646].f51 == 0)
                laps--;
            tm = g_9e70[g_9646] - g_9e80[g_9646];
        } else
            tm = g_1e68 - g_9e70[g_9646];
        fn_09_955c(0x897, buf1);
        fn_06_0f1a(laps, buf2);
        lstrcat(buf1, buf2);
        fn_09_9580(0x898, buf1);
        fn_11_4928(0, tm, buf2);
    l_reset:    /* bare label: resets register tracking */
        lstrcat(buf1, buf2);
        TextOut(dc, 1, 60, buf1, lstrlen(buf1));
        if (g_1df8[14][g_9646].f51 == 0) {
            fn_09_955c(0x899, buf1);
            fn_11_4928(0, g_1e68 - g_9e60[g_9646], buf2);
            lstrcat(buf1, buf2);
            TextOut(dc, 1, 46, buf1, lstrlen(buf1));
        } else {
            fn_09_955c(0x89a, buf1);
            fn_11_4928(0, g_9e60[g_9646], buf2);
            lstrcat(buf1, buf2);
            TextOut(dc, 1, 46, buf1, lstrlen(buf1));
        }
    } else if (g_9eb4 == 0) {
        if (b) {
            fn_09_955c(0x89b, buf1);
            TextOut(dc, 1, 46, buf1, lstrlen(buf1));
        }
        if (g_1df8[14][g_9316].f28 == 4) {
            if (g_13dc)
                g_186a++;
            if (g_9eb5) {
                fn_10_744c(20);
                race_radar_background(1);
            }
            g_9eb5 = 0;
            if (g_186a == 5 || g_186a == 9 || g_186a == 13 || g_186a == 16
                || g_186a == 17) {
                fn_10_744c(110);
                col = RGB(255, 0, 0);
                pt.x = ((g_1df8[12][1].f04.x - g_1df8[14][g_9646].f04.x) >> 4 << g_9156)
                     + g_1df8[14][g_9646].f00 + (25 << g_9156);
                pt.y = g_1df8[14][g_9646].f22 / 4 + g_1df8[14][g_9646].f02;
                switch (g_186a) {
                case 5:
                    fn_10_754a(0x75, -80, g_90ec / 2, 4);
                    lstrcpy(buf3, "3");
                    fn_10_94c4(1, 0, col, pt.x, pt.y, buf3);
                    break;
                case 9:
                    fn_10_754a(0x75, g_90ea + 40, g_90ec / 2, 4);
                    lstrcpy(buf3, "2");
                    fn_10_94c4(1, 0, col, pt.x, pt.y, buf3);
                    break;
                case 13:
                    fn_10_754a(0x75, g_90ea / 2, g_90ec / 2, 4);
                    lstrcpy(buf3, "1");
                    fn_10_94c4(1, 0, col = RGB(255, 128, 0), pt.x, pt.y, buf3);
                    break;
                case 16:
                    LoadString(g_9212, 0x89c, buf3, 5);
                    fn_10_94c4(1, 0, col = RGB(128, 255, 0), pt.x, pt.y, buf3);
                    break;
                case 17:
                    PatBlt(g_13dc, pt.x, pt.y, 50, 30, BLACKNESS);
                    break;
                }
            }
            if (g_186a == 17) {
                fn_10_7480(4, 1);
                fn_10_744c(31);
                g_9eb4 = 1;
                for (i = 0; i <= g_9316; i++) {
                    g_9e80[i] = g_9e70[i] = g_9e60[i] = g_1e68;
                    g_9e90[i] = 0;
                }
            }
        } else
            g_186a = 0;
    }
}

/* Fire or release the tow tether of object (type, n), weapon k: picks the
 * best target in range and launches a type-10 tether object [inferred]. */
/* @addr 11:947a */
void far fn_11_947a(int type, int n, int k)
{
    int unused1[4];             /* frame slots never used */
    int t;
    int speed;
    int tt;
    int tn;
    int best;
    int v16;                    /* set, never read */
    int j;
    int dx;
    int dy;
    int dist;
    int dir;
    int unused3;
    int slot;
    int maxd;
    int score;
    int unused2[4];             /* frame slots never used */
    HGDIOBJ old;
    int ok;

    if (g_1df8[type][n].f1a == 0)
        return;
    ok = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].fcb; j++)
            if (g_7090[n].fb8[j] == 2 || g_7090[n].fb8[j] == 15) {
                ok = 1;
                break;
            }
    } else
        ok = 1;
    if (type == g_9324) {
        if (g_2f4c[k].f36 > g_7090[n].f1e)
            ok = 0;
        else
            g_7090[n].f1e -= g_2f4c[k].f36;
    }
    if (ok == 0)
        return;
    if (g_1df8[type][n].f36 == -1) {
        slot = -1;
        for (t = 0; t < g_9300; t++)
            if (g_1df8[10][t].f18 != 0 && g_65cc[t].f00 == -1) {
                slot = t;
                break;
            }
        if (slot == -1)
            return;
        g_65cc[slot].f0a = k;
        g_1df8[10][slot].f02 = -1000;
        g_1df8[10][slot].f00 = g_1df8[10][slot].f02;
        fn_10_754a(29, type, n, 1);
        if (type == g_9324 && g_96ea[g_7090[n].f4e].f20 == 7 && k == 15) {
            tt = g_7090[n].f54;
            tn = g_7090[n].f56;
            v16 = 200;
        } else {
            tt = -1;
            best = 0;
            maxd = 300;
            for (t = g_9326; t <= g_9324; t++) {
                if (t != 5 && t != 12 && t != 2)
                    for (j = 0; j < g_9406[t]; j++) {
                        if (g_1df8[t][j].f18 == 0 && (t != type || j != n)
                            && (g_1df8[t][j].f54 == 0 || t == 4)
                            && (dist = fn_08_285a(&dx, &dy, g_1df8[type][n].f04, g_1df8[t][j].f04)) < maxd) {
                            score = g_1df8[t][j].f44 + 400 > 1200 ? 1200 : g_1df8[t][j].f44 + 400;
                            dir = fn_08_19b0(dx, dy);
                            if (g_1df8[type][n].f28 >= dir - 1 && g_1df8[type][n].f28 <= dir + 1)
                                score *= 2;
                            if (type == 14 && t == g_7090[n].f32 && j == g_7090[n].f34) {
                                score *= 2;
                                if (g_1df8[g_7090[n].f32][g_7090[n].f34].f53 != 0)
                                    score *= 3;
                            } else if (type == 14 && t == 14 && g_7090[n].f32 == 14)
                                score /= 8;
                            else if (type == 14 && g_1df8[t][j].f53 == 1 && g_7090[n].f38 != 1)
                                score *= 2;
                            if (t == 6)
                                score *= 6;
                            score = (long)score * (maxd * 2 - dist) / ((long)maxd * 2);
                            if (score > best) {
                                tt = t;
                                tn = j;
                                best = score;
                            }
                        }
                    }
            }
        }
        g_1df8[type][n].f31 = slot;
        if (tt != -1 && g_92e8 == 0) {
            g_1df8[10][slot].f04 = g_1df8[type][n].f04;
            *(long far *)&g_1df8[10][slot].f0c = *(long far *)&g_1df8[type][n].f0c;
            if (type == g_9324) {
                g_1df8[10][slot].f04.x += g_7b60[g_7090[n].f4e][g_1df8[10][slot].f28].x * 4 / 3 << 3;
                g_1df8[10][slot].f04.y += g_7b60[g_7090[n].f4e][g_1df8[10][slot].f28].y * 4 / 3 << 3;
            } else {
                g_1df8[10][slot].f04.x += g_1df8[type][n].f20 / 2 * g_1050[g_1df8[10][slot].f28].x / 16
                    + (g_1050[g_1df8[10][slot].f28 + 32].x << 3);
                g_1df8[10][slot].f04.y += g_1df8[type][n].f20 / 2 * g_1050[g_1df8[10][slot].f28].y / 16
                    + (g_1050[g_1df8[10][slot].f28 + 32].y << 3);
            }
            if (tt == g_9324)
                speed = 160;
            else
                speed = 110;
            fn_08_348e(10, slot, tt, tn, speed);
            if (g_1df8[type][n].f0c == g_1df8[10][slot].f0c
                && g_1df8[type][n].f0e == g_1df8[10][slot].f0e) {
                g_1df8[10][slot].f0c = g_1050[g_1df8[type][n].f28].x * 7 + g_1df8[type][n].f0c;
                g_1df8[10][slot].f0e = g_1050[g_1df8[type][n].f28].y * 7 + g_1df8[type][n].f0e;
            }
            g_1df8[10][slot].f28 = fn_08_19b0(g_1df8[10][slot].f0c, g_1df8[10][slot].f0e);
            g_1df8[10][slot].f18 = 0;
            g_1df8[10][slot].f2e = 0;
            g_1df8[10][slot].f32 = type;
            g_1df8[10][slot].f34 = n;
            g_65cc[slot].f08 = 0;
            g_65cc[slot].f00 = 10;
            g_65cc[slot].f02 = slot;
            g_65cc[slot].f04 = type;
            g_65cc[slot].f06 = n;
            g_1df8[type][n].f36 = 10;
            g_1df8[type][n].f38 = slot;
        } else {
            g_1df8[10][slot].f18 = 0;
            g_1df8[10][slot].f2e = 0;
            g_1df8[10][slot].f0c = g_1050[g_1df8[type][n].f28].x * 7 + g_1df8[type][n].f0c;
            g_1df8[10][slot].f0e = g_1050[g_1df8[type][n].f28].y * 7 + g_1df8[type][n].f0e;
            g_1df8[10][slot].f28 = g_1df8[type][n].f28;
            g_1df8[10][slot].f04 = g_1df8[type][n].f04;
            if (type == g_9324) {
                g_1df8[10][slot].f04.x += g_7b60[g_7090[n].f4e][g_1df8[10][slot].f28].x * 4 / 3 << 3;
                g_1df8[10][slot].f04.y += g_7b60[g_7090[n].f4e][g_1df8[10][slot].f28].y * 4 / 3 << 3;
            } else {
                g_1df8[10][slot].f04.x += g_1df8[type][n].f20 / 2 * g_1050[g_1df8[10][slot].f28].x / 16
                    + (g_1050[g_1df8[10][slot].f28 + 32].x << 3);
                g_1df8[10][slot].f04.y += g_1df8[type][n].f20 / 2 * g_1050[g_1df8[10][slot].f28].y / 16
                    + (g_1050[g_1df8[10][slot].f28 + 32].y << 3);
            }
            g_1df8[10][slot].f32 = type;
            g_1df8[10][slot].f34 = n;
            g_1df8[type][n].f36 = 10;
            g_1df8[type][n].f38 = slot;
            g_65cc[slot].f08 = 0;
            g_65cc[slot].f00 = 10;
            g_65cc[slot].f02 = slot;
            g_65cc[slot].f04 = type;
            g_65cc[slot].f06 = n;
        }
    } else {
        if (g_1df8[type][n].f36 == g_9324) {
            g_7090[g_1df8[type][n].f38].f84 = g_1e50 + 800;
            g_1df8[g_9324][g_1df8[type][n].f38].f26 = 1;
            g_7090[g_1df8[type][n].f38].fe2 = 1;
        }
        g_1df8[g_1df8[type][n].f36][g_1df8[type][n].f38].f32 = -1;
        g_1df8[type][n].f36 = -1;
        g_65cc[g_1df8[type][n].f31].f00 = -1;
        g_65cc[g_1df8[type][n].f31].f04 = -1;
        g_1df8[10][g_1df8[type][n].f31].f18 = 1;
        old = SelectObject(g_13dc, GetStockObject(7));
        fn_12_7256(g_13dc, g_65cc[g_1df8[type][n].f31].f1c, g_65cc[g_1df8[type][n].f31].f14);
        SelectObject(g_13dc, old);
        PatBlt(g_13dc, g_1df8[10][g_1df8[type][n].f31].f00, g_1df8[10][g_1df8[type][n].f31].f02,
               g_1df8[10][g_1df8[type][n].f31].f22, g_1df8[10][g_1df8[type][n].f31].f22, BLACKNESS);
        if (type == g_9324 && n == g_9646 && g_951a == 0)
            fn_07_1208();
    }
    fn_07_2080(10, -1);
}

/* Lay out and draw the control panel below the play view: info windows,
 * zoom scroll bar, stone frame, panel bitmaps; then redraw the current
 * screen [inferred]. */
/* @addr 11:0afe */
void far fn_11_0afe(void)
{
    HDC memdc;
    HPEN oldpen;
    HBITMAP oldbmp;
    HBRUSH oldbrush;
    HPALETTE oldpal;
    int i;
    int unused1[7];             /* frame slots never used */
    int h;
    int unused2[2];             /* frame slots never used */
    int gotdc;
    char buf[8];
    char s[4];
    RECT r2;
    RECT r1;                    /* computed, never used */
    int off;
    int n;
    int rem;
    int tile;
    int h2;
    COLORREF col;               /* set, never read */

    g_5050 = g_0a72 / 2;
    g_5052 = g_0a74 / 2;
    srand((unsigned)GetCurrentTime());
    gotdc = 0;
    if (g_13dc == 0) {
        gotdc = 1;
        g_13dc = GetDC(g_0016);
    }
    if (g_920e) {
        oldpal = SelectPalette(g_13dc, g_920e, 0);
        RealizePalette(g_13dc);
    }
    if (fn_11_2120()) {
        if (g_90ea < 660) {
            g_93b8 = 1;
            g_93dc = 73;
        } else if (g_90ea < 760) {
            g_93b8 = 1;
            g_93dc = 90;
        } else {
            g_93b8 = 4;
            g_93dc = 134;
        }
        g_5024 = g_90ea / 2 - g_93dc - 96;
        if (g_90ea < 700)
            g_5024 += 9;
        g_93ba = g_93dc + g_93b8 + 4;
        if (g_90ea < 700)
            g_93ba -= 2;
        g_93be = g_90ea / 2 - 50;
        g_93bc = g_93be - 30;
        if (g_90ea >= 700)
            g_93bc -= 4;
        g_93c0 = g_90ea / 2 + 68;
        if (g_094e)
            g_93c0 -= 14;
        g_93c2 = g_93c0 + 28;
        g_93c4 = g_93c0 + 88;
        g_5026 = g_90ea / 2 - 160;
        if (g_90ea < 700)
            g_5026 += 4;
        if (g_094e)
            g_5026 += 14;
        if (g_0a7a) {
            GetWindowRect(g_0a7a, &r1);
            GetWindowRect(g_0016, &r2);
            r1.left -= r2.left;
            r1.top -= r2.top;
        }
        if (g_0a7a) {
            DestroyWindow(g_0a7a);
            g_0a7a = 0;
        }
        if (g_094e == 0) {
            g_0a7a = CreateWindow("scrollbar", "", WS_CHILD | WS_VISIBLE | SBS_VERT,
                                  g_90ea / 2 + 50, g_8e5a, 14, 85, g_0016, (HMENU)200, g_8e66, NULL);
            SetScrollRange(g_0a7a, SB_CTL, 100, 500, FALSE);
            SetScrollPos(g_0a7a, SB_CTL, 600 - (int)g_0a6c, TRUE);
        }
        if (g_0a7c) {
            DestroyWindow(g_0a7c);
            g_0a7c = 0;
        }
        g_0a7c = CreateWindow("IS_INFO", "", WS_CHILD | WS_VISIBLE,
                              g_93ba + 5, g_8e5a + 5, g_5024 - 9, 76, g_0016, (HMENU)210, g_8e66, NULL);
        if (g_0a7e) {
            DestroyWindow(g_0a7e);
            g_0a7e = 0;
        }
        g_0a7e = CreateWindow("IS_INFO", "", WS_CHILD | WS_VISIBLE,
                              g_93c4 + 5, g_8e5a + 5, g_5026 - 9, 76, g_0016, (HMENU)220, g_8e66, NULL);
        oldbrush = SelectObject(g_13dc, g_500a);
        PatBlt(g_13dc, 0, g_8e5a, g_90ea, 85, PATCOPY);
        SelectObject(g_13dc, oldbrush);
        if (g_0a78) {
            h2 = g_8e5a;
            off = (58 - g_90ea % 58) / 2;
            n = g_90ea / 58;
            if (off)
                n++;
            fn_11_170a(1);
            memdc = CreateCompatibleDC(g_13dc);
            oldbmp = SelectObject(memdc, g_5044);
            for (i = 0; i < n + 1; i++) {
                tile = fn_11_170a(0);
                BitBlt(g_13dc, i * 58 - off, 0, 58, 58, memdc, tile * 58, 0, SRCCOPY);
            }
            n = h2 / 58;
            rem = h2 % 58;
            for (i = 1; i < n; i++) {
                tile = fn_11_170a(0);
                BitBlt(g_13dc, -off, i * 58, 58, 58, memdc, tile * 58, 0, SRCCOPY);
            }
            tile = fn_11_170a(0);
            BitBlt(g_13dc, -off, i * 58, 58, rem, memdc, tile * 58, 0, SRCCOPY);
            for (i = 1; i < n; i++) {
                tile = fn_11_170a(0);
                BitBlt(g_13dc, off + g_90ea - 58, i * 58, 58, 58, memdc, tile * 58, 0, SRCCOPY);
            }
            tile = fn_11_170a(0);
            BitBlt(g_13dc, off + g_90ea - 58, i * 58, 58, rem, memdc, tile * 58, 0, SRCCOPY);
            SelectObject(memdc, oldbmp);
            DeleteDC(memdc);
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((14 - i) * 10, (14 - i) * 10, (14 - i) * 10)));
                PatBlt(g_13dc, (i + 29) * 2 - off, (i + 29) * 2,
                       g_90ea - ((i + 29) * 2 - off) * 2, 2, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((12 - i) * 20, (12 - i) * 20, (12 - i) * 20)));
                PatBlt(g_13dc, (i + 29) * 2 - off, h2 - (i + 1) * 2,
                       g_90ea - ((i + 29) * 2 - off) * 2, 2, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((14 - i) * 10, (14 - i) * 10, (14 - i) * 10)));
                PatBlt(g_13dc, (i + 29) * 2 - off, (i + 29) * 2,
                       2, h2 - i * 4 - 58, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((12 - i) * 20, (12 - i) * 20, (12 - i) * 20)));
                PatBlt(g_13dc, g_90ea + off - (i + 30) * 2, (i + 29) * 2,
                       2, h2 - i * 4 - 58, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
        }
        oldpen = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
        MoveTo(g_13dc, 0, g_8e5a);
        LineTo(g_13dc, g_90ea, g_8e5a);
        DeleteObject(SelectObject(g_13dc, oldpen));
        LoadString(g_9212, 0x80f, buf, 6);
        s[0] = buf[0];
        s[1] = 0;
        if (g_90ea < 660) {
            PatBlt(g_13dc, g_93b8, g_8e5a + 12, g_93dc, h = 45, BLACKNESS);
            if (g_90f0)
                col = 0x200a0ffL;
            else
                col = 0x80ffL;
            for (i = 0; i < 5; i++) {
                s[0] = buf[i];
                fn_11_2154(0, 0xffL, i * 14 + g_93b8 + 6, g_8e5a + 16, s);
            }
        } else if (g_90ea < 760) {
            PatBlt(g_13dc, g_93b8, g_8e5a + 12, g_93dc, h = 60, BLACKNESS);
            for (i = 0; i < 5; i++) {
                s[0] = buf[i];
                fn_10_94c4(0, 0, 0xffL, i * 18 + g_93b8, g_8e5a + 16, s);
            }
        } else {
            PatBlt(g_13dc, g_93b8, g_8e5a + 12, g_93dc, h = 60, BLACKNESS);
            for (i = 0; i < 5; i++) {
                s[0] = buf[i];
                fn_10_94c4(0, 0, 0xffL, i * 22 + g_93b8 + 25, g_8e5a + 16, s);
            }
        }
        g_5018 = -1;
        fn_11_04ea();
        oldpen = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
        MoveTo(g_13dc, g_93dc + g_93b8, g_8e5a + 12);
        LineTo(g_13dc, g_93dc + g_93b8, h + g_8e5a + 12);
        LineTo(g_13dc, g_93b8, h + g_8e5a + 12);
        DeleteObject(SelectObject(g_13dc, oldpen));
        fn_11_1774(2, g_93ba, g_8e5a, g_93ba + g_5024, g_8e5a + 84);
        memdc = CreateCompatibleDC(g_13dc);
        oldbmp = SelectObject(memdc, g_503e);
        BitBlt(g_13dc, g_93bc, g_8e5a, 30, 85, memdc, 0, 0, SRCCOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        g_93d4 = -1;
        fn_11_0978();
        fn_11_1774(4, g_93be, g_8e5a, g_93be + 99, g_8e5a + 84);
        memdc = CreateCompatibleDC(g_13dc);
        oldbmp = SelectObject(memdc, g_503c);
        BitBlt(g_13dc, g_93c0, g_8e5a + 24, 84, 61, memdc, 0, 0, SRCCOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        fn_11_05fe(1);
        g_5028 = g_1e50;
        g_93da = g_93d8 == 0;
        fn_11_0894();
        fn_10_949c(g_13dc, g_93c2, g_8e5a + 1, 55, 17, 0);
        memdc = CreateCompatibleDC(g_13dc);
        oldbrush = SelectObject(g_13dc, CreateSolidBrush(RGB(0, 255, 0)));
        oldbmp = SelectObject(memdc, g_5038);
        BitBlt(g_13dc, g_93c2 + 23, g_8e5a + 4, 10, 10, memdc, 100, 0, MERGECOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        DeleteObject(SelectObject(g_13dc, oldbrush));
        fn_11_1ef6(1);
        fn_11_1774(2, g_93c4, g_8e5a, g_93c4 + g_5026, g_8e5a + 84);
    }
    switch (g_90f4) {
    case 1:
    case 7:
        if (g_951a == 0) {
            if (g_9130) {
                if (g_6da4 != 0)
                    g_6da4->f1c = 1;
            } else {
                fn_07_11cc();
                fn_07_1208();
                g_058c = 1;
                fn_07_1f38();
                fn_11_33cc();
            }
        }
        break;
    case 0:
        if (g_95b8 >= 6) {
            if (g_92d4 >= 2)
                g_92d4 = 9;
            else
                BitBlt(g_13dc, 0, 0, g_90ea, g_0010, g_929a, 0, 0, SRCCOPY);
        } else if (g_95b8 != 0) {
            if (g_95b8 < 3)
                g_6e28 = GetCurrentTime();
            else if (g_6e28 != g_1e50)
                g_6e28 = GetCurrentTime() + 15000;
        }
        fn_15_5962(1);
        break;
    case 6:
        fn_16_0cfe(1);
        if (g_9130 && g_6da4 != 0)
            g_6da4->f1c = 1;
        break;
    case 8:
        fn_16_6928(1);
        break;
    case 2:
        fn_09_6dec(1);
        break;
    case 3:
        if (g_93aa != 18)
            draw_briefing_panel_with_esc_prompt(0);
        break;
    case 5:
        fn_06_5f7a(1);
        break;
    case 4:
        fn_09_6a12();
        break;
    }
    if (oldpal)
        SelectPalette(g_13dc, oldpal, 0);
    if (gotdc) {
        ReleaseDC(g_0016, g_13dc);
        g_13dc = 0;
    }
}

/* Fire weapon k from object (type, n): find or grow a free shot slot
 * (type 6 objects), pay the ammo or energy cost, aim the shot (homing
 * target search for kind 5) and launch it [inferred]. */
/* @addr 11:7c12 */
void far pascal fn_11_7c12(int k, int type, int n)
{
    int s;
    int i;
    int unused08;               /* frame slot never used */
    int w;
    int tt;
    int tn;
    int bestd;
    int dx;
    int dy;
    int dist;
    int dir;
    int ang;
    int unused1c;               /* frame slot never used */
    int ok;
    int done;

    s = -1;
    done = 0;
    if (g_9412 >= 10)
        return;
    do {
        if (++s >= g_92f8) {
            g_92f8 = s + 1;
            GlobalUnlock(g_910c);
            g_910c = GlobalReAlloc(g_910c, (long)(g_92f8 < 1 ? 1 : g_92f8) * 0x70, 0x42);
            g_1df8[6] = (REC_70 far *)GlobalLock(g_910c);
            g_1df8[6][s].f18 = 1;
            g_1df8[6][s].f44 = 20;
            g_1df8[6][s].f42 = 100;
            g_1df8[6][s].f4c = 0x7f00;
            g_1df8[6][s].f2c = -1;
            g_1df8[6][s].f48 = 5;
            g_1df8[6][s].f62 = fn_11_3914;
            g_1df8[6][s].f5e = fn_07_2652;
            if (k == 16)
                g_1df8[6][s].f53 = 1;
            else
                g_1df8[6][s].f53 = 0;
            g_1df8[6][s].f54 = 0;
            g_1df8[6][s].f32 = -1;
            g_1df8[6][s].f12 = g_1df8[6][s].f24;
            g_1df8[6][s].f2e = 0;
            g_66e0[s].f04 = -1;
            g_9412 = s + 1;
        }
        if ((g_1df8[6][s].f18 != 0
             || g_2f4c[g_66e0[s].f04].f26 <= g_66e0[s].f0c && g_2f4c[g_66e0[s].f04].f2c != 6
             || g_66e0[s].f0c == 0)
            && g_1df8[6][s].f51 == 0)
            g_66e0[s].f04 = -1;
        ok = 0;
        if (type == g_9324) {
            for (i = 1; i < g_7090[n].fcb; i++)
                if (g_7090[n].fb8[i] == k) {
                    if (g_7090[n].fae[i] > 0 && g_2f4c[k].f36 == 0
                        || g_2f4c[k].f36 > 0
                           && (type != 14 || g_2f4c[k].f36 < g_7090[n].f1e))
                        ok = 1;
                    w = i;
                    break;
                }
        } else
            ok = 1;
        if (g_66e0[s].f04 == -1 && ok != 0) {
            done = 1;
            for (i = 0; i < g_9412; i++)
                if (g_66e0[i].f0c > 0 && g_66e0[i].f0c < 15 && g_66e0[i].f08 == type
                    && g_66e0[i].f0a == n && g_66e0[i].f04 != -1)
                    return;
            if (type == g_9324) {
                if (g_2f4c[k].f36 == 0)
                    g_7090[n].fae[w]--;
                else
                    g_7090[n].f1e = max(g_7090[n].f1e - g_2f4c[k].f36, 0);
            }
            PostMessage(g_0a7e, WM_PAINT, 0, 0L);
            g_66e0[s].f0c = 0;
            g_66e0[s].f18 = 0;
            g_66e0[s].f04 = k;
            g_66e0[s].f16 = 0;
            g_66e0[s].f14 = 2;
            g_1df8[6][s].f00 = -1000;
            g_1df8[6][s].f02 = -1000;
            g_1df8[6][s].f08 = -1000;
            g_1df8[6][s].f0a = -1000;
            if (g_2f4c[k].f12 == 2 && type == g_9324) {
                if (n != g_9646 || g_95bc == 0)
                    fn_03_00f4(n, g_7090[n].f32, g_7090[n].f34);
                g_66e0[s].f00 = g_7090[n].f3e;
                g_66e0[s].f02 = g_7090[n].f40;
                g_66e0[s].f1a = 0;
            } else {
                g_66e0[s].f00 = -1;
                g_66e0[s].f1a = 0;
            }
            g_1df8[6][s].f18 = 0;
            g_1df8[6][s].f2e = 0;
            g_1df8[6][s].f22 = SC(g_2f4c[k].f00);
            if (g_2f4c[k].f00 & 1) {
                g_1df8[6][s].f22 = SC(g_2f4c[k].f00 + 1);
                g_1df8[6][s].f24 = SC(4);
            } else
                g_1df8[6][s].f24 = SC(6);
            g_1df8[6][s].f12 = g_1df8[6][s].f24;
            g_1df8[6][s].f20 = g_2f4c[k].f00 * 8;
            g_1df8[6][s].f48 = g_2f4c[k].f2a;
            g_1df8[6][s].f50 = 0;
            g_1df8[6][s].f44 = g_2f4c[k].f18;
            g_1df8[6][s].f2c = g_2f4c[k].f10;
            g_1df8[6][s].f1e = 0;
            g_1df8[6][s].f28 = g_1df8[type][n].f28;
            g_1df8[6][s].f04.x = g_1df8[type][n].f04.x;
            g_1df8[6][s].f04.y = g_1df8[type][n].f04.y;
            if (g_2f4c[k].f06 == -1) {
                if (g_92e8)
                    g_66e0[s].f0c = g_2f4c[k].f26 / 4;
                fn_06_84fc((rand() % 2 + 1) * 10, 0, 0, 0, 0, 0, 0, 0, g_2f4c[k].f26 - 1, s);
            }
            if (g_2f4c[k].f2c == 4 || g_2f4c[k].f2c == 6)
                g_1df8[6][s].f66 = fn_07_2e02;
            else
                g_1df8[6][s].f66 = fn_12_274a;
            if (k == 16) {
                g_1df8[6][s].f53 = 1;
                for (i = 0; i < g_9316; i++)
                    if (g_96ea[g_7090[i].f4e].f20 == 7) {
                        g_7090[i].f06 = 6;
                        g_7090[i].f08 = s;
                        g_7090[i].f36 = g_7090[i].f3a = 2;
                        g_7090[i].f94 = g_1e50 + 100;
                    }
            } else
                g_1df8[6][s].f53 = 0;
            if (g_2f4c[k].f12 == 5) {
                g_1df8[6][s].f0c = g_1df8[type][n].f0c;
                g_1df8[6][s].f0e = g_1df8[type][n].f0e;
                g_1df8[6][s].f04.x += g_1df8[type][n].f20 / 2 - g_1df8[6][s].f20 / 2;
                g_1df8[6][s].f04.y += g_1df8[type][n].f20 / 2 - g_1df8[6][s].f20 / 2;
                tt = -1;
                if (g_2f4c[k].f4e != 0)
                    for (i = 0; i < g_9412; i++)
                        if (g_66e0[i].f08 != type || g_66e0[i].f0a != n) {
                            dist = fn_08_285a(&dx, &dy, g_1df8[6][s].f04, g_1df8[6][i].f04);
                            if (dist < 350) {
                                tt = 6;
                                tn = i;
                            }
                        }
                if (tt == -1) {
                    tt = -1;    /* sic */
                    bestd = 20000;
                    for (i = 0; i < g_9146; i++) {
                        if ((g_507c[i] != type || g_50e0[i] != n)
                            && g_1df8[g_507c[i]][g_50e0[i]].f44 > 1) {
                            dist = fn_08_285a(&dx, &dy, g_1df8[g_507c[i]][g_50e0[i]].f04,
                                              g_1df8[type][n].f04);
                            if (g_507c[i] == g_9324) {
                                dist = dist * 3 / 4;
                                if (type == g_9324 && g_7090[n].f32 == g_9324
                                    && g_7090[n].f34 == g_50e0[i])
                                    dist /= 6;
                                else if (type == g_9324
                                         && (fn_13_2688(n, g_50e0[i]) > 150
                                             || g_96ea[g_7090[g_50e0[i]].f4e].f20
                                                == g_96ea[g_7090[n].f4e].f20))
                                    dist = (dist + 50) * 5;
                            }
                            dir = fn_08_19b0(-dx, -dy);
                            ang = g_1df8[type][n].f28;
                            if (ang - 1 <= dir && ang + 1 >= dir)
                                dist = dist * 2 / 3;
                            if (dist < bestd) {
                                tt = g_507c[i];
                                tn = g_50e0[i];
                                bestd = dist;
                            }
                        }
                    }
                }
                if (tt != -1) {
                    fn_08_348e(6, s, tt, tn, g_2f4c[k].f16);
                    ang = fn_08_19b0(g_1df8[6][s].f0c - g_1df8[type][n].f0c,
                                     g_1df8[6][s].f0e - g_1df8[type][n].f0e);
                    g_1df8[6][s].f04.x += (g_1df8[6][s].f20 / 2 + g_1df8[type][n].f20 / 8)
                                          * g_1050[ang].x * 5 / 20;
                    g_1df8[6][s].f04.y += (g_1df8[6][s].f20 / 2 + g_1df8[type][n].f20 / 8)
                                          * g_1050[ang].y * 5 / 20;
                }
                if (g_1df8[type][n].f0c == g_1df8[6][s].f0c
                    && g_1df8[type][n].f0e == g_1df8[6][s].f0e) {
                    g_1df8[6][s].f0c = g_1050[g_1df8[type][n].f28].x * 8 + g_1df8[type][n].f0c;
                    g_1df8[6][s].f0e = g_1050[g_1df8[type][n].f28].y * 8 + g_1df8[type][n].f0e;
                    ang = fn_08_19b0(g_1df8[6][s].f0c - g_1df8[type][n].f0c,
                                     g_1df8[6][s].f0e - g_1df8[type][n].f0e);
                    g_1df8[6][s].f04.x += (g_1df8[6][s].f20 / 2 + g_1df8[type][n].f20 / 2)
                                          * g_1050[ang].x / 20;
                    g_1df8[6][s].f04.y += (g_1df8[6][s].f20 / 2 + g_1df8[type][n].f20 / 2)
                                          * g_1050[ang].y / 20;
                }
            } else if (g_2f4c[k].f0c == 1 || type != g_9324) {
                g_1df8[6][s].f04.x += (g_1df8[type][n].f20 - g_1df8[6][s].f20) / 2
                    + (g_1df8[type][n].f20 + g_1df8[6][s].f20) / 2
                      * g_1050[g_1df8[type][n].f28].x / 15;
                g_1df8[6][s].f04.y += (g_1df8[type][n].f20 - g_1df8[6][s].f20) / 2
                    + (g_1df8[type][n].f20 + g_1df8[6][s].f20) / 2
                      * g_1050[g_1df8[type][n].f28].y / 15;
                g_1df8[6][s].f0c = g_1050[g_1df8[type][n].f28].x * 4;
                g_1df8[6][s].f0e = g_1050[g_1df8[type][n].f28].y * 4;
                if (type == g_9324)
                    g_7090[n].fa0 = g_1e68 + 36;
            } else if (g_2f4c[k].f0c == 2 && type == g_9324) {
                g_1df8[6][s].f04.x += (g_7ba0[g_7090[n].f4e][g_1df8[type][n].f28].x << 3)
                    + g_1050[(g_1df8[type][n].f28 + 8) % 16].x * 11 / 4
                    - g_1df8[6][s].f20 / 2;
                g_1df8[6][s].f04.y += (g_7ba0[g_7090[n].f4e][g_1df8[type][n].f28].y << 3)
                    + g_1050[(g_1df8[type][n].f28 + 8) % 16].y * 11 / 4
                    - g_1df8[6][s].f20 / 2;
                g_1df8[6][s].f0c = -(g_1050[g_1df8[type][n].f28].x * 4);
                g_1df8[6][s].f0e = -(g_1050[g_1df8[type][n].f28].y * 4);
                g_1df8[6][s].f04.x -= g_1df8[g_9324][n].f0c;
                g_1df8[6][s].f04.y -= g_1df8[g_9324][n].f0e;
            }
            g_66e0[s].f0c = 0;
            if (g_2f4c[k].f12 != 5) {
                g_1df8[6][s].f0c += g_1df8[type][n].f0c;
                g_1df8[6][s].f0e += g_1df8[type][n].f0e;
            }
            g_66e0[s].f08 = type;
            g_66e0[s].f0a = n;
            if (type == g_9324 && n == g_9646)
                fn_10_744c(0x69);
            fn_10_7944(g_2f4c[k].f20, 6, s, 1, "");
        }
    } while (!done && ok);
    fn_07_2080(6, -1);
    if (g_1df8[6][0].f18 == 0 && g_66e0[0].f04 == -1)
        g_9498++;
}
