cmake_minimum_required(VERSION 3.16)
project(inspace C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)

file(GLOB GAME_SOURCES src/game/*.c)
add_executable(inspace
    src/main.c
    src/video.c
    src/platform/platform_sdl.c
    src/win/controls.c
    src/win/crt.c
    src/win/dgroup.c
    src/win/dialog.c
    src/win/draw.c
    src/win/edit.c
    src/win/gdi.c
    src/win/handles.c
    src/win/input.c
    src/win/ispace.c
    src/win/ispace_dlg.c
    src/win/ispace_img.c
    src/win/ispace_pal.c
    src/win/ispace_reg.c
    src/win/ispace_smooth.c
    src/win/kernel.c
    src/win/module.c
    src/win/ne.c
    src/win/profile.c
    src/win/startup.c
    src/win/stubs.c
    src/win/text.c
    src/win/user.c
    ${GAME_SOURCES}
    third_party/stb/stb_truetype.c
)
target_include_directories(inspace PRIVATE src src/game src/win third_party)
target_link_libraries(inspace PRIVATE SDL3::SDL3)
if(NOT WIN32 AND NOT MSVC)
    target_link_libraries(inspace PRIVATE m)
endif()

# The game's arithmetic follows the 1994 compiler: 16-bit int arithmetic is
# made explicit with casts (tools/port_int16.py), and 32-bit (long)
# arithmetic may overflow and must wrap as it did then: -fwrapv.  MSVC has
# no such switch but wraps signed overflow in practice.  Globals are typed
# views of one DGROUP image (game.h): -fno-strict-aliasing.
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(inspace PRIVATE -Wall -Wextra -pedantic -fsigned-char -fwrapv -fno-strict-aliasing)
    # The generated game code still has the warnings listed in NOTES-port.md.
    set_source_files_properties(${GAME_SOURCES} third_party/stb/stb_truetype.c PROPERTIES COMPILE_OPTIONS "-w")
elseif(MSVC)
    target_compile_options(inspace PRIVATE /W4 /J-)
endif()

# The fonts that stand in for Windows' (port/README.md), next to the
# executable.
file(GLOB FONT_FILES third_party/liberation/*.ttf)
add_custom_command(TARGET inspace POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:inspace>/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FONT_FILES} $<TARGET_FILE_DIR:inspace>/fonts)
