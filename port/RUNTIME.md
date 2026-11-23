# Native Windows calls (port/src/win/)

What the game gets from the native layer. Unimplemented calls are stubs
that log their name once (`STUB()`) and return a neutral value.

| Area | Module | Implemented | Stubbed |
|---|---|---|---|
| Start-up | startup.c, main.c | GDI objects, DGROUP image, INSPACE.EXE module, call of WinMain (renamed `inspace_WinMain`) | |
| DGROUP | dgroup.c, game/globals.c | data segment 19 of INSPACE.EXE unpacked at run time (OPTLOADER LZ) into `dgroup[]`; plain globals are views of it (game.h); near pointers point into it; far pointers start zero | |
| NE files | ne.c | header, segments, OPTLOADER LZ, resource table lookup | relocation tails (not needed for DGROUP) |
| C runtime | crt.c | MSC `rand`/`srand` (LCG), `wsprintf` (16-bit `%d/%u/%x` unless `l`), `lstrcpy/cat/len/cmp`, `_dos_findfirst/next` (no volume labels), `stat` | `utime` |
| Memory | kernel.c | `GlobalAlloc/Lock/Unlock/ReAlloc/Free/Size/Compact` (native blocks, 25% slack for REC_70) | |
| Files | kernel.c | `OpenFile` (exist/read/write/create/delete), `_lread/_lwrite/_lclose/_filelength`; DOS paths: `C:\SPACE\` = data folder, `C:\WINDOWS\` = settings folder, case-insensitive lookup | other drives |
| Profile | profile.c | `Get/WritePrivateProfileString/Int`, `GetProfile*` (WIN.INI in the settings folder) | |
| System | kernel.c | `GetCurrentTime/timeGetTime/timeGetDevCaps`, `GetVersion` (3.10), `GetWindowsDirectory`, `GetFreeSystemResources`, `SetMessageQueue`, `OutputDebugString` (`INSPACE_DEBUG`) | `WinExec`, `GetInstanceData` (no-op) |
| Modules, resources | module.c | `LoadLibrary/FreeLibrary/GetModuleFileName`, `GetProcAddress` (ISPACE.DLL ordinals), `FindResource/LoadResource/LockResource/FreeResource/SizeofResource`, `LoadString`, `LoadAccelerators`, `TranslateAccelerator` | `LoadIcon/LoadCursor/DestroyIcon` (dummy handles), `ExtractIcon` |
| Windows, messages | user.c | classes, `CreateWindow/DestroyWindow/ShowWindow/UpdateWindow/InvalidateRect/MoveWindow/SetWindowPos`, window words/longs/text, queue (`Get/Peek/Post/Send/DispatchMessage`, `TranslateMessage`, `PostQuitMessage`), timers, keyboard and mouse from SDL, key state, cursor position, `GetSystemMetrics` (640x480), rectangles, `MessageBox` (logged, answers OK/No) | `IsIconic`, `EnableWindow`, `SetClassWord` |
| GDI | gdi.c, draw.c | DCs (window DCs draw into the framebuffer), 8-bit and monochrome bitmaps, `BitBlt/StretchBlt/PatBlt` with any ROP3 on palette indices, `FillRect/FrameRect/Rectangle/Polygon/Ellipse/LineTo/SetPixel/GetPixel/ScrollDC/DrawFocusRect`, brushes (solid, pattern), pens, regions as clip rectangles, palettes (`SelectPalette/RealizePalette` set the framebuffer palette, identity mapping), static system colours, LoadBitmap-style DIB conversion | dithering of RGB brushes, stretch modes, wide pens |
| Text | stubs.c | | `TextOut`, `ExtTextOut`, `GetTextExtent`, `GetTextMetrics` (fixed metrics), fonts are records only |
| Menus, dialogs | stubs.c | | all menu calls, `CreateDialog/DialogBox/EndDialog/GetDlgItem/IsDialogMessage`, scroll bars, `WinHelp`, `DrawIcon` |
| ISPACE.DLL | ispace.c | ord 3 (load bitmap from IGRAPHIC.DLL / SD_LOGO from ISPACE.DLL), ord 6 (black mask of a bitmap) | the other 21 ordinals the game fetches, among them ord 1/2 (image loader), ord 4 (palette manager), ord 7 (sound set-up, returns 1) |
| Sound, music | | | not reached yet |
