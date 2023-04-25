cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID chess_game)

project(chess_game)

set(SOURCE_FILES
        src/pieces.cpp
        src/game_state.cpp
        src/graphics.cpp
        src/game.cpp
        )

include(../SetCommonConfig.cmake)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Werror=switch)

set(SDL2_INCLUDE_DIR C:/Users/bialo/SDL/SDL2-2.26.5/include)
set(SDL2_LIB_DIR C:/Users/bialo/SDL/SDL2-2.26.5/lib/x64)
set(SDL2_IMAGE_INCLUDE_DIR C:/Users/bialo/SDL_image/SDL2_image-2.6.3/include)
set(SDL2_IMAGE_LIB_DIR C:/Users/bialo/SDL_image/SDL2_image-2.6.3/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(CMake_Target main.cpp)

target_sources(CMake_Target
        PRIVATE
        src/pieces.cpp
        src/game_state.cpp
        src/graphics.cpp
        src/game.cpp
        )

target_link_libraries(CMake_Target SDL2main SDL2 SDL2_image)