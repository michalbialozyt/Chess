//
// Created by michalbialozyt on 25.04.2023.
//
#include "game.hpp"
void Game::run() {
    Graphics graphics;
    Game_State gamestate;

    bool quit = false;
    while (!quit) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(graphics.renderer_);
        graphics.Render_chessboard();
        graphics.Render_all_pieces(gamestate.board_);
        SDL_RenderPresent(graphics.renderer_);
    }
}