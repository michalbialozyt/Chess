//
// Created by michalbialozyt on 19.04.2023.
//
#include<pieces.hpp>
//Piece::Piece(const Piece& other) :
//    position_(other.position_),
//    team_(other.team_){}

std::vector<Position> King::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    bool to_add = true;
    for(int i = -1; i < 2; ++i){
        for(int j = -1; j < 2; ++j){
            if(position_.X_Coordinate + i > 0 && position_.X_Coordinate + i < 8 && position_.Y_Coordinate + j > 0 && position_.Y_Coordinate + j < 8){
                for(auto piece_on_board : current_game_state.pieces_){
                    if(piece_on_board.position_.X_Coordinate == i  && piece_on_board.position_.X_Coordinate == j && piece_on_board.team_ == team_){
                        to_add = false;
                        break;
                    }
                }
                if(to_add){
                    legal_moves.push_back(Position(position_.X_Coordinate + i,position_.Y_Coordinate + j));
                }
            }
        }
    }
}