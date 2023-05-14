//
// Created by michalbialozyt on 25.04.2023.
//

#pragma once
#include "game_state.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>

class Graphics {
public:
    const int HEIGHT = 640;
    const int WIDTH = 640;
    const char* TITLE = "CHESS GAME";

    Graphics();
    ~Graphics();

    void Render_piece(const std::string& image_dir, int X, int Y) const;

    void Render_all_pieces(Piece* board[8][8]) const;

    void Render_chessboard() const;

    void Render_possible_moves(Piece* piece, const std::unique_ptr<Game_State>& game_state) const;

    SDL_Window* window_;

    SDL_Renderer* renderer_;
};