//
// Created by michal bialozyt on 25.04.2023.
//
#include "graphics.hpp"
#include <algorithm>
#include <cmath>

Graphics::Graphics(){
    SDL_Init(SDL_INIT_VIDEO);

    window_ = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        std::cerr << "Failed to create SDL window: %s\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) {
        std::cerr << "Failed to create SDL renderer: %s\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Graphics::Render_chessboard() const {
    SDL_Rect cellRect;
    cellRect.w = WIDTH/8;
    cellRect.h = HEIGHT/8;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer_, 111, 78, 55, 255);
            } else {
                SDL_SetRenderDrawColor(renderer_, 228, 205, 167, 255);
            }
            cellRect.x = x * WIDTH/8;
            cellRect.y = y * HEIGHT/8;
            SDL_RenderFillRect(renderer_, &cellRect);
        }
    }
}

void Graphics::Render_piece(const char* image_dir, int X, int Y) const {
    SDL_Surface* surface = IMG_Load(image_dir);
    if (surface == nullptr) {
        std::cout << "Failed to load image: " << image_dir << ". SDL_image Error: " << IMG_GetError() << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        std::cout << "Failed to create texture from surface. SDL Error: " << SDL_GetError() << std::endl;
    }
    SDL_Rect destRect;
    destRect.x = X;  // x-coordinate of the destination rectangle
    destRect.y = Y;  // y-coordinate of the destination rectangle
    destRect.w = 60;    // set to 0 to use the width of the image
    destRect.h = 60;

    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
}

void Graphics::Render_all_pieces(Piece* board[8][8]) const {
    for(int i = 0; i < 8 ; ++i){
        for(int j = 0; j < 8 ; ++j){
            if(board[i][j] != nullptr){
                Render_piece(board[i][j]->get_image_name(),board[i][j]->get_position().X_Coordinate * WIDTH/8 + 10, board[i][j]->get_position().Y_Coordinate* HEIGHT/8 + 10);
            }
        }
    }
}

void Graphics::Render_possible_moves(Piece* piece, const std::unique_ptr<Game_State>& game_state) const {
    if(piece != nullptr) {
        for (const auto &pos: game_state->possible_moves_[piece]) {
            SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH / 8, HEIGHT / 8, 32, SDL_PIXELFORMAT_RGBA32);
            SDL_Rect cellRect;
            bool is_occupied = (game_state->board_[pos.first.X_Coordinate][pos.first.Y_Coordinate] != nullptr);
            cellRect.w = WIDTH / 8;
            cellRect.h = HEIGHT / 8;
            cellRect.x = pos.first.X_Coordinate * WIDTH / 8;
            cellRect.y = pos.first.Y_Coordinate * HEIGHT / 8;
            for(int y = 0; y < HEIGHT / 8; y++) {
                for(int x = 0; x < WIDTH / 8; x++) {

                    double dist = sqrt((x - WIDTH / 8 + 40) * (x - WIDTH / 8 + 40) + (y - HEIGHT / 8 + 40) * (y - HEIGHT / 8 + 40));
                    double alpha = 0.2;
                    if((dist > 15 && !is_occupied) || (is_occupied && (dist < 33 || dist > 36))){
                        alpha = 0.0;
                    }
                    Uint8* pixel = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
                    pixel[3] = (Uint8)(alpha * 255.0);
                }
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
            SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer_, texture, nullptr, &cellRect);
        }
        //highlight the position of the piece
        Position pos = piece->get_position();
        SDL_Rect cellRect;
        cellRect.w = WIDTH / 8;
        cellRect.h = HEIGHT / 8;
        cellRect.x = pos.X_Coordinate * WIDTH / 8;
        cellRect.y = pos.Y_Coordinate * HEIGHT / 8;
        if(std::div((cellRect.x + cellRect.y),80).quot % 2 == 0){
            SDL_SetRenderDrawColor(renderer_, 167, 136, 36, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer_, 167, 136, 36, 255);
        }
        SDL_RenderFillRect(renderer_, &cellRect);
    }
}
