//
// Created by michal bialozyt on 20.04.2023.
//
#include "game_state.hpp"
#include <algorithm>
#include <iostream>

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

void Game_State::make_move(Piece* piece, Position new_position, Piece::Move_type Move_type){
    switch(Move_type){
        case Piece::NORMAL:
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            piece->set_position(new_position);
            piece->has_moved_ = true;
            break;
        case Piece::CASTLE:
            //castling Queenside, rook move
            if(piece->get_position().X_Coordinate > new_position.X_Coordinate){
                board_[0][piece->get_position().Y_Coordinate]->set_position(Position(piece->get_position().X_Coordinate - 1,piece->get_position().Y_Coordinate));
                board_[3][piece->get_position().Y_Coordinate] = board_[0][piece->get_position().Y_Coordinate];
                board_[0][piece->get_position().Y_Coordinate] = nullptr;
                std::cout << (board_[0][0] == nullptr) << std::endl;
                board_[3][piece->get_position().Y_Coordinate]->has_moved_ = true;
            }
            //castling kingside, rook move
            else{
                board_[7][piece->get_position().Y_Coordinate]->set_position(Position(piece->get_position().X_Coordinate + 1,piece->get_position().Y_Coordinate));
                board_[5][piece->get_position().Y_Coordinate] = board_[7][piece->get_position().Y_Coordinate];
                board_[7][piece->get_position().Y_Coordinate] = nullptr;
                std::cout << (board_[7][7] == nullptr) << std::endl;
                board_[5][piece->get_position().Y_Coordinate]->has_moved_ = true;
            }
            //moving king
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            piece->set_position(new_position);
            piece->has_moved_ = true;
            break;
        case Piece::EN_PASSANT:
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            piece->set_position(new_position);
            piece->has_moved_ = true;
            break;
        // auto promoting to queen
        case Piece::PROMOTION:
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            auto new_piece = std::make_unique<Queen>(Position(new_position.X_Coordinate,new_position.Y_Coordinate), piece->get_team());
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = new_piece.get();
            pieces_.push_back(std::move(new_piece));
            break;
    }
}

bool Game_State::is_legal_move(Position position, Piece* piece){
    auto legal_moves = piece->calculate_possible_moves(board_);
    auto it = std::find(legal_moves.begin(), legal_moves.end(),position);
    return it != legal_moves.end();
}

std::vector<Position> Game_State::get_postitions_attacked_by_team (Piece::Team team) {
    std::vector<Position> pos;
    for(const auto& piece : pieces_){
        if(piece->get_team() == team){
            auto moves = piece->calculate_possible_moves(board_);
            pos.insert(pos.end(), moves.begin(), moves.end());
        }
    }
    return pos;
}