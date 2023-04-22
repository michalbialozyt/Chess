//
// Created by bialo on 20.04.2023.
//
#include<game_state.hpp>
std::vector<Piece*> Game_State::get_pieces() const{
    std::vector<Piece*> pieces_to_return;
    for(const auto& piece : pieces_){
        pieces_to_return.push_back(piece.get());
    }
    return pieces_to_return;
}
bool Game_State::is_occupied(Position& position) const {
    bool is_occupied = false;
    for(const auto& elem : pieces_){
        if(elem->get_position() == position){
            is_occupied = false;
        }
    }
    return is_occupied;
}