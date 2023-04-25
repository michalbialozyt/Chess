//
// Created by michal bialozyt on 25.04.2023.
//
#include "graphics.hpp"

void Graphics::Init(){
    SDL_Init(SDL_INIT_VIDEO);

    window_ = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        std::cerr << "Failed to create SDL window: %s\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    else{
        std::cout << "window created" << std::endl;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) {
        std::cerr << "Failed to create SDL renderer: %s\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    else{
        std::cout << "renderer created" << std::endl;
    }
}

void Graphics::Clear(){
    std::cerr << "window destroyed" << std::endl;
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}
