# port_calls: the port's ISPACE.DLL routines driven by a call script
# (tools/README.md, "DLL oracle").  Builds the port's sources without its
# main.c.
cmake_minimum_required(VERSION 3.16)
project(port_calls C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_package(SDL3 REQUIRED CONFIG)

set(PORT ${CMAKE_CURRENT_SOURCE_DIR}/../../port)
file(GLOB GAME_SOURCES ${PORT}/src/game/*.c)
file(GLOB WIN_SOURCES ${PORT}/src/win/*.c)
add_executable(port_calls port_calls.c ${PORT}/src/video.c ${PORT}/src/platform/platform_sdl.c
    ${WIN_SOURCES} ${GAME_SOURCES} ${PORT}/third_party/stb/stb_truetype.c)
target_include_directories(port_calls PRIVATE ${PORT}/src ${PORT}/src/game ${PORT}/src/win
    ${PORT}/third_party)
target_link_libraries(port_calls PRIVATE SDL3::SDL3 m)
target_compile_options(port_calls PRIVATE -Wall -Wextra -pedantic -fsigned-char -fwrapv
    -fno-strict-aliasing)
set_source_files_properties(${GAME_SOURCES} ${PORT}/third_party/stb/stb_truetype.c
    PROPERTIES COMPILE_OPTIONS "-w")
