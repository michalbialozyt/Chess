//
// Created by michalbialozyt on 25.04.2023.
//
#pragma once
#include "position.hpp"
#include "game_state.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Graphics {
public:
    const int HEIGHT = 640;
    const int WIDTH = 640;
    const char* TITLE = "CHESS GAME <3";

    Graphics();

    ~Graphics();

    void Render_piece(const char* image_dir, int X, int Y) const;

    void Render_all_pieces(Piece* board[8][8]) const;

    void Render_chessboard() const;

    SDL_Window* window_;

    SDL_Renderer* renderer_;
};
