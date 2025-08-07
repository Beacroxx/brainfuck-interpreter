cmake_minimum_required(VERSION 3.20)
project(brainfuck_interpreter)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SRC_FILES "src/*.c")
add_executable(bfi ${SRC_FILES})

target_include_directories(bfi PRIVATE include)

target_link_libraries(bfi PRIVATE SDL2 SDL2_ttf)