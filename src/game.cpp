//
// Created by michalbialozyt on 25.04.2023.
//
#include <algorithm>
#include "game.hpp"
void Game::run() {
    auto graphics = std::make_unique<Graphics>();
    auto gamestate = std::make_unique<Game_State>();

    Position null_position;
    Position Mouse_position;
    auto Highlighted_piece = std::make_unique<Position>();
    Piece* Highlighted_piece_pointer;

    Piece::Team turn = Piece::WHITE;
    bool no_checkmate = true;
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
                            Highlighted_piece_pointer = gamestate->board_[Highlighted_piece->X_Coordinate][Highlighted_piece->Y_Coordinate];
                            if(gamestate->is_legal_move(Mouse_position,Highlighted_piece_pointer)) {
                                auto move = std::find_if(gamestate->possible_moves_[Highlighted_piece_pointer].begin(),
                                                         gamestate->possible_moves_[Highlighted_piece_pointer].end(),
                                                         [Mouse_position](const std::pair<Position, Piece::Move_type> &p) {return p.first == Mouse_position;});
                                gamestate->make_move(
                                        gamestate->board_[Highlighted_piece->X_Coordinate][Highlighted_piece->Y_Coordinate],
                                        move->first, move->second, false);
                                if(turn == Piece::WHITE){
                                    turn = Piece::BLACK;
                                }
                                else{
                                    turn = Piece::WHITE;
                                }
                                no_checkmate = gamestate->calculate_all_possible_moves_with_check(turn);
                                if(!no_checkmate){
                                    if(turn == Piece::BLACK) {
                                        std::cout << "CHECKMATE, WHITE WON!" << std::endl;
                                    }
                                    else{
                                        std::cout << "CHECKMATE, BLACK WON!" << std::endl;
                                    }
                                    quit = true;
                                }
                                *Highlighted_piece = null_position;
                            }
                            else if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate] != nullptr){
                                if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate]->get_team() == turn){
                                    *Highlighted_piece = Mouse_position;
                                }
                                else{
                                    *Highlighted_piece = null_position;
                                }
                            }
                            else{
                                *Highlighted_piece = null_position;
                            }
                        }
                        else if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate] != nullptr) {
                            if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate]->get_team() == turn){
                                *Highlighted_piece = Mouse_position;
                            }
                            else{
                                *Highlighted_piece = null_position;
                            }
                        }
                    }
                    break;
            }
        }

        SDL_RenderClear(graphics->renderer_);
        graphics->Render_chessboard();
        graphics->Render_all_pieces(gamestate->board_);
        graphics->Render_possible_moves(
                    gamestate->board_[Highlighted_piece->X_Coordinate][Highlighted_piece->Y_Coordinate], gamestate);
        SDL_RenderPresent(graphics->renderer_);
    }
}