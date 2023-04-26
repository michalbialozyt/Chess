//
// Created by michalbialozyt on 25.04.2023.
//
#include "game.hpp"
void Game::run() {
    auto graphics = std::make_unique<Graphics>();
    auto gamestate = std::make_unique<Game_State>();

    Position null_position;
    Position Mouse_position;
    auto Highlighted_piece = std::make_unique<Position>();

    bool quit = false;
    while (!quit) {

        SDL_GetMouseState(&(Mouse_position.X_Coordinate), &(Mouse_position.Y_Coordinate));
        Mouse_position.X_Coordinate = Mouse_position.X_Coordinate/80;
        Mouse_position.Y_Coordinate = Mouse_position.Y_Coordinate/80;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(SDL_BUTTON_LEFT == event.button.button){
                        if(Highlighted_piece -> X_Coordinate != -1){
                            if(gamestate->is_legal_move(Mouse_position,
                                                        gamestate->board_[Highlighted_piece->X_Coordinate][Highlighted_piece->Y_Coordinate],
                                                        gamestate->board_)){
                                gamestate->make_move(gamestate->board_[Highlighted_piece->X_Coordinate][Highlighted_piece->Y_Coordinate],
                                                     Mouse_position);
                                *Highlighted_piece = null_position;
                            }
                            else if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate] != nullptr){
                                *Highlighted_piece = Mouse_position;
                            }
                            else{
                                *Highlighted_piece = null_position;
                            }
                        }
                        else if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate] != nullptr) {
                            *Highlighted_piece = Mouse_position;
                            std::cout << Mouse_position.X_Coordinate << Mouse_position.Y_Coordinate << std::endl;
                        }
                    }
                    break;
            }
        }

        SDL_RenderClear(graphics->renderer_);
        graphics->Render_chessboard();
        graphics->Render_all_pieces(gamestate->board_);
        graphics->Render_possible_moves(
                    gamestate->board_[Highlighted_piece->X_Coordinate][Highlighted_piece->Y_Coordinate],
                    gamestate->board_);
        SDL_RenderPresent(graphics->renderer_);
    }
}