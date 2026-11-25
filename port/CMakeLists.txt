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
    src/platform/platform_music.c
    src/platform/music_seq.c
    src/platform/music_tsf.c
    src/win/controls.c
    src/win/crt.c
    src/win/dgroup.c
    src/win/dialog.c
    src/win/dosfs.c
    src/win/draw.c
    src/win/edit.c
    src/win/gdi.c
    src/win/handles.c
    src/win/icon.c
    src/win/input.c
    src/win/ispace.c
    src/win/ispace_collide.c
    src/win/ispace_cut.c
    src/win/ispace_dlg.c
    src/win/ispace_img.c
    src/win/ispace_options.c
    src/win/ispace_panel.c
    src/win/ispace_pal.c
    src/win/ispace_reg.c
    src/win/ispace_room.c
    src/win/ispace_shape.c
    src/win/ispace_smooth.c
    src/win/ispace_sound.c
    src/win/ispace_music.c
    src/win/ispace_sprite.c
    src/win/ispace_surface.c
    src/win/kernel.c
    src/win/listbox.c
    src/win/mci.c
    src/win/menu.c
    src/win/module.c
    src/win/ne.c
    src/win/profile.c
    src/win/scrollbar.c
    src/win/startup.c
    src/win/stubs.c
    src/win/text.c
    src/win/user.c
    src/win/wavemix.c
    ${GAME_SOURCES}
    third_party/stb/stb_truetype.c
    third_party/tsf/tsf.c
)
target_include_directories(inspace PRIVATE src src/game src/win third_party)
# TinyMidiLoader's message type is a C11 anonymous union: a system header.
target_include_directories(inspace SYSTEM PRIVATE third_party/tsf)
target_link_libraries(inspace PRIVATE SDL3::SDL3)
if(WIN32)
    # The system's MIDI synthesizer (music_win.c).
    target_sources(inspace PRIVATE src/platform/music_win.c)
    target_link_libraries(inspace PRIVATE winmm)
elseif(NOT MSVC)
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
    set_source_files_properties(${GAME_SOURCES} third_party/stb/stb_truetype.c third_party/tsf/tsf.c
                                PROPERTIES COMPILE_OPTIONS "-w")
elseif(MSVC)
    target_compile_options(inspace PRIVATE /W4 /J-)
endif()

# The fonts that stand in for Windows' (port/README.md), next to the
# executable.
file(GLOB FONT_FILES third_party/liberation/*.ttf)
add_custom_command(TARGET inspace POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:inspace>/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FONT_FILES} $<TARGET_FILE_DIR:inspace>/fonts)
