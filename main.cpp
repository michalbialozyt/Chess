#define SDL_MAIN_HANDLED
#include <cstdlib>
#include <iostream>
#include "game.hpp"
#include "pieces.hpp"

int main() {
    Game::run();
    return EXIT_SUCCESS;
}
