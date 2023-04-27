//
// Created by michal bialozyt on 20.04.2023.
//
#include "game_state.hpp"
#include <algorithm>

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
    pieces_.push_back(std::make_unique<Queen>(Position(3,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<King>(Position(4,7), Piece::WHITE));
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
    pieces_.push_back(std::make_unique<Queen>(Position(3,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<King>(Position(4,0), Piece::WHITE));


    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j) {
            board_[i][j] = nullptr;
        }
    }
    for(const auto& elem : pieces_){
        board_[elem->get_position().X_Coordinate][elem->get_position().Y_Coordinate] = elem.get();
    }
}

void make_move(Piece* piece, Position new_position, Piece::Move_type Move_type, Piece* board[8][8]){
    switch(Move_type){
        case Piece::NORMAL:
            board[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            piece->set_position(new_position);
            piece->has_moved_ = true;
            break;
        case Piece::CASTLE:
            //castling Queenside, rook move
            if(piece->get_position().X_Coordinate > new_position.X_Coordinate){
                board[0][piece->get_position().Y_Coordinate]->set_position(Position(piece->get_position().X_Coordinate - 1,piece->get_position().Y_Coordinate));
                board[3][piece->get_position().Y_Coordinate] = board[0][piece->get_position().Y_Coordinate];
                board[0][piece->get_position().Y_Coordinate] = nullptr;
                board[3][piece->get_position().Y_Coordinate]->has_moved_ = true;
            }
            //castling kingside, rook move
            else{
                board[7][piece->get_position().Y_Coordinate]->set_position(Position(piece->get_position().X_Coordinate + 1,piece->get_position().Y_Coordinate));
                board[5][piece->get_position().Y_Coordinate] = board[7][piece->get_position().Y_Coordinate];
                board[7][piece->get_position().Y_Coordinate] = nullptr;
                board[5][piece->get_position().Y_Coordinate]->has_moved_ = true;
            }
            //moving king
            board[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            piece->set_position(new_position);
            piece->has_moved_ = true;
            break;
        case Piece::EN_PASSANT:
            board[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            piece->set_position(new_position);
            piece->has_moved_ = true;
            break;
        // auto promoting to queen
        case Piece::PROMOTION:
            board[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            auto new_piece = std::make_unique<Queen>(Position(new_position.X_Coordinate,new_position.Y_Coordinate), piece->get_team());
            board[new_position.X_Coordinate][new_position.Y_Coordinate] = new_piece.get();
            break;
    }
}

bool Game_State::is_legal_move(Position position, Piece* piece){
    auto legal_moves = piece->calculate_possible_moves(board_);
    auto it = std::find_if(legal_moves.begin(), legal_moves.end(),
                           [position](const std::pair<Position, Piece::Move_type>& p) { return p.first == position; });

    return it != legal_moves.end();
}

std::vector<std::pair<Position,Piece::Move_type>> Game_State::get_postitions_attacked_by_team (Piece::Team team, Piece* board[8][8]) {
    std::vector<std::pair<Position,Piece::Move_type>> pos;
    for(const auto& piece : pieces_){
        if(piece->get_team() == team){
            auto moves = piece->calculate_possible_moves(board);
            pos.insert(pos.end(), moves.begin(), moves.end());
        }
    }
    return pos;
}

bool Game_State::check_check_after_move(Piece* piece, Position new_position, Piece::Move_type Move_type) {
    Piece* board_after_move[8][8];
    Piece* attacked_king;
    Position kings_position;
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j) {
            *board_after_move[i][j] = *board_[i][j];
        }
    }
    Piece* piece_to_move;
    piece_to_move = board_after_move[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate];
    Piece::Team attacking_team;
    if(piece->get_team() == Piece::WHITE){
        attacking_team = Piece::BLACK;

        // TODO: get kings postion:
        //attacked_king = board_after_move[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate];
    }
    else{
        attacking_team = Piece::WHITE;

        // TODO: get kings postion
        //attacked_king = board_after_move[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate];
    }
    make_move(piece_to_move, new_position, Move_type, board_after_move);
    if(piece->get_piecetype() == Piece::KING && piece->get_team() != attacking_team){
        attacked_king = board_after_move[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate];
    }
    auto posisions_attacked = get_postitions_attacked_by_team(attacking_team, board_after_move);
    kings_position = attacked_king->get_position();
    auto it = std::find_if(posisions_attacked.begin(), posisions_attacked.end(),
                           [kings_position](const std::pair<Position, Piece::Move_type>& p) { return p.first == kings_position; });

    return it != posisions_attacked.end();
}

std::vector<std::pair<Position,Piece::Move_type>> Game_State::calculate_possible_moves_with_check(Piece* piece){
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;
    auto possible_moves_no_check = piece->calculate_possible_moves(board_);
    for(auto elem : possible_moves_no_check){
        if (!check_check_after_move(piece, elem.first, elem.second)){
            legal_moves.emplace_back(elem.first, elem.second);
        }
    }
    return legal_moves;
}