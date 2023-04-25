//
// Created by michalbialozyt on 25.04.2023.
//
#pragma once
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

    void Init();

    void Clear();

    SDL_Window* window_;

    SDL_Renderer* renderer_;
};
