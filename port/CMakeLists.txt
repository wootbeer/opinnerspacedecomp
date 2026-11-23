cmake_minimum_required(VERSION 3.16)
project(inspace C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)

add_executable(inspace
    src/main.c
    src/video.c
    src/platform/platform_sdl.c
)
target_include_directories(inspace PRIVATE src)
target_link_libraries(inspace PRIVATE SDL3::SDL3)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(inspace PRIVATE -Wall -Wextra -pedantic -fsigned-char)
elseif(MSVC)
    target_compile_options(inspace PRIVATE /W4 /J-)
endif()
