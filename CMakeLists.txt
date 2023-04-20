cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID chess_game)
project(chess_game)
set(SOURCE_FILES
        src/pieces.cpp
        src/game_state.cpp
        )

include(../SetCommonConfig.cmake)
