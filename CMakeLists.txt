cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID chess_game)
project(chess_game)
set(SOURCE_FILES
        src/pieces.cpp
        src/game_state.cpp
        )

add_executable(CMake_Target main.cpp)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Werror=switch)

set(SDL2_INCLUDE_DIR C:/Users/bialo/SDL/SDL2-2.26.5/include)
set(SDL2_LIB_DIR C:/Users/bialo/SDL/SDL2-2.26.5/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_LIB_DIR})

include(../SetCommonConfig.cmake)

target_link_libraries(CMake_Target SDL2main SDL2)