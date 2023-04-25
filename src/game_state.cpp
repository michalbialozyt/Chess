//
// Created by michal bialozyt on 20.04.2023.
//
#include "game_state.hpp"

Game_State::Game_State(){
    top_board_team_ = Piece::BLACK;
    pieces_.push_back(std::make_unique<Pawn>(Position(0,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(1,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(2,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(3,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(4,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(5,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(6,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(7,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Rook>(Position(7,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Rook>(Position(0,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Knight>(Position(6,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Knight>(Position(1,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Bishop>(Position(5,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Bishop>(Position(2,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<King>(Position(4,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Queen>(Position(3,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(0,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(1,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(2,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(3,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(4,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(5,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(6,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(7,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Rook>(Position(7,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Rook>(Position(0,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Knight>(Position(6,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Knight>(Position(1,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Bishop>(Position(5,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Bishop>(Position(2,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<King>(Position(4,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Queen>(Position(3,0), Piece::BLACK));
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j) {
            board_[i][j] = nullptr;
        }
    }
    for(const auto& elem : pieces_){
        board_[elem->get_position().X_Coordinate][elem->get_position().Y_Coordinate] = elem.get();
    }
}
