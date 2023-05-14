//
// Created by michalbialozyt on 25.04.2023.
//

#include "game.hpp"

void Game::run() {
    auto graphics = std::make_unique<Graphics>();
    auto gamestate = std::make_unique<Game_State>();
    auto turn = Piece::WHITE;

    Position null_position;
    Position Mouse_position;
    Position* Highlighted_position = &null_position;
    Piece* Highlighted_piece;
    Game_State::Game_Result result;
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
                        if(Highlighted_position -> X_Coordinate != -1){
                            Highlighted_piece = gamestate->board_[Highlighted_position->X_Coordinate][Highlighted_position->Y_Coordinate];

                            if(gamestate->is_legal_move(Mouse_position,Highlighted_piece)) {
                                auto move = std::find_if(gamestate->possible_moves_[Highlighted_piece].begin(),
                                                         gamestate->possible_moves_[Highlighted_piece].end(),
                                                         [Mouse_position](const std::pair<Position, Piece::Move_type> &p) {return p.first == Mouse_position;});
                                gamestate->make_move(
                                        gamestate->board_[Highlighted_position->X_Coordinate][Highlighted_position->Y_Coordinate],
                                        move->first, move->second, false);

                                if(turn == Piece::WHITE){
                                    turn = Piece::BLACK;
                                }
                                else{
                                    turn = Piece::WHITE;
                                }

                                gamestate->calculate_all_possible_moves_with_check(turn);
                                result = gamestate->check_game_result();

                                switch(result){
                                    case Game_State::NO_RESULT:
                                        break;
                                    case Game_State::Game_Result::BLACK_WIN:
                                        quit = true;
                                        std::cout << " BLACK WINS BY CHECKMATE " << std::endl;
                                        break;
                                    case Game_State::Game_Result::WHITE_WIN:
                                        quit = true;
                                        std::cout << " WHITE WINS BY CHECKMATE " << std::endl;
                                        break;
                                    case Game_State::Game_Result::DRAW_BY_STALEMATE:
                                        quit = true;
                                        std::cout << " DRAW BY STALEMATE" << std::endl;
                                        break;
                                    case Game_State::Game_Result::DRAW_BY_50_MOVES:
                                        quit = true;
                                        std::cout << " DRAW BY 50 MOVES" << std::endl;
                                        break;
                                    case Game_State::Game_Result::DRAW_BY_INSUFFICIENT_MATERIAL:
                                        quit = true;
                                        std::cout << "DRAW BY INSUFFICIENT MATERIAL" << std::endl;
                                        break;
                                }
                                *Highlighted_position = null_position;
                            }
                            else if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate] != nullptr){
                                if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate]->get_team() == turn){
                                    *Highlighted_position = Mouse_position;
                                }
                                else{
                                    *Highlighted_position = null_position;
                                }
                            }
                            else{
                                *Highlighted_position = null_position;
                            }
                        }
                        else if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate] != nullptr) {
                            if(gamestate->board_[Mouse_position.X_Coordinate][Mouse_position.Y_Coordinate]->get_team() == turn){
                                *Highlighted_position = Mouse_position;
                            }
                            else{
                                *Highlighted_position = null_position;
                            }
                        }
                    }
                    break;
            }
        }
        SDL_RenderClear(graphics->renderer_);
        graphics->Render_chessboard();
        graphics->Render_possible_moves(
                gamestate->board_[Highlighted_position->X_Coordinate][Highlighted_position->Y_Coordinate], gamestate);
        graphics->Render_all_pieces(gamestate->board_);
        SDL_RenderPresent(graphics->renderer_);
    }
}