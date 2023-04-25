//
// Created by michalbialozyt on 25.04.2023.
//
#include "game.hpp"
void Game::run() {
    Window window("SDL2 Window", WIDTH, HEIGHT);

    bool quit = false;
    while (!quit) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(window.getRenderer());

        SDL_RenderPresent(window.getRenderer());
    }
}