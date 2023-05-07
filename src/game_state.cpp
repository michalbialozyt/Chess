//
// Created by michal bialozyt on 20.04.2023.
//
#include "game_state.hpp"
#include <algorithm>

Game_State::Game_State(){
    //top_board_team_ = Piece::BLACK;
    pieces_.push_back(std::make_unique<Knight>(Position(6,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Knight>(Position(1,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Bishop>(Position(5,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Bishop>(Position(2,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Queen>(Position(3,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<King>(Position(4,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Rook>(Position(7,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Rook>(Position(0,7), Piece::WHITE));
    pieces_.push_back(std::make_unique<Knight>(Position(6,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Knight>(Position(1,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Bishop>(Position(5,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Bishop>(Position(2,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Queen>(Position(3,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<King>(Position(4,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Rook>(Position(7,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Rook>(Position(0,0), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(0,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(1,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(2,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(3,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(4,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(5,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(6,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(7,6), Piece::WHITE));
    pieces_.push_back(std::make_unique<Pawn>(Position(0,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(1,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(2,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(3,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(4,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(5,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(6,1), Piece::BLACK));
    pieces_.push_back(std::make_unique<Pawn>(Position(7,1), Piece::BLACK));



    for(int i = 2; i < 7; ++i){
        for(int j = 0; j < 8; ++j) {
            board_[i][j] = nullptr;
        }
    }

    for(const auto& elem : pieces_){
        board_[elem->get_position().X_Coordinate][elem->get_position().Y_Coordinate] = elem.get();
    }

    white_king_ = board_[4][7];
    black_king_ = board_[4][0];
    calculate_all_possible_moves_with_check();
}

void Game_State::make_move(Piece* piece, const Position& new_position, const Piece::Move_type& Move_type, bool is_test){
    switch(Move_type){
        case Piece::NORMAL:
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            break;
        case Piece::CASTLE:
            //castling Queenside, rook move
            if(piece->get_position().X_Coordinate > new_position.X_Coordinate){
                board_[3][piece->get_position().Y_Coordinate] = board_[0][piece->get_position().Y_Coordinate];
                board_[0][piece->get_position().Y_Coordinate] = nullptr;
                if(!is_test){
                    board_[3][piece->get_position().Y_Coordinate]->set_position(Position(3,piece->get_position().Y_Coordinate));
                    board_[3][piece->get_position().Y_Coordinate]->has_moved_ = true;
                }
            }
            //castling kingside, rook move
            else{
                board_[5][piece->get_position().Y_Coordinate] = board_[7][piece->get_position().Y_Coordinate];
                board_[7][piece->get_position().Y_Coordinate] = nullptr;
                if(!is_test){
                    board_[5][piece->get_position().Y_Coordinate]->set_position(Position(5,piece->get_position().Y_Coordinate));
                    board_[5][piece->get_position().Y_Coordinate]->has_moved_ = true;
                }
            }
            //moving king
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            break;
        case Piece::EN_PASSANT:
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = piece;
            if(piece->get_position().Y_Coordinate == 3){
                board_[new_position.X_Coordinate][new_position.Y_Coordinate + 1] = nullptr;
            }
            if(piece->get_position().Y_Coordinate == 4){
                board_[new_position.X_Coordinate][new_position.Y_Coordinate - 1] = nullptr;
            }
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            break;
        // auto promoting to queen
        case Piece::PROMOTION:
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            auto new_piece = std::make_unique<Queen>(Position(new_position.X_Coordinate,new_position.Y_Coordinate), piece->get_team());
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = new_piece.get();
            piece = new_piece.get();
            pieces_.push_back(std::move(new_piece));
            break;
    }
    if(!is_test){
        for(const auto& elem: pieces_){
            elem->set_en_passant(false);
        }
        piece->set_position(new_position);
        if(piece->get_piecetype() == Piece::PAWN && ((piece-> get_team() == Piece::BLACK && piece->get_position().Y_Coordinate == 3) || (piece-> get_team() == Piece::WHITE && piece->get_position().Y_Coordinate == 4)) && !piece->has_moved_){
            piece->set_en_passant(true);
        }
        piece->has_moved_ = true;
    }
}

void Game_State::undo_move(Piece *piece, Piece* taken_piece, Position original_position, Position new_position,
                           Piece::Move_type Move_type) {
    switch(Move_type){
        case Piece::NORMAL:
            board_[original_position.X_Coordinate][original_position.Y_Coordinate] = piece;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = taken_piece;
            break;
        case Piece::CASTLE:
            //castling Queenside, rook move
            if(piece->get_position().X_Coordinate > new_position.X_Coordinate){
                board_[0][piece->get_position().Y_Coordinate] = board_[3][piece->get_position().Y_Coordinate];
                board_[3][piece->get_position().Y_Coordinate] = nullptr;
            }
                //castling kingside, rook move
            else{
                board_[7][piece->get_position().Y_Coordinate] = board_[5][piece->get_position().Y_Coordinate];
                board_[5][piece->get_position().Y_Coordinate] = nullptr;
            }
            //moving king
            board_[original_position.X_Coordinate][original_position.Y_Coordinate] = piece;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = nullptr;
            break;
        case Piece::EN_PASSANT:
            if(piece->get_position().Y_Coordinate == 3){
                board_[new_position.X_Coordinate][new_position.Y_Coordinate + 1] = taken_piece;
            }
            else{
                board_[new_position.X_Coordinate][new_position.Y_Coordinate - 1] = taken_piece;
            }
            board_[original_position.X_Coordinate][original_position.Y_Coordinate] = piece;
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = nullptr;
            break;
            // auto promoting to queen
        case Piece::PROMOTION:
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = taken_piece;
            auto new_piece = std::make_unique<Pawn>(Position(original_position.X_Coordinate,original_position.Y_Coordinate), piece->get_team());
            board_[original_position.X_Coordinate][original_position.Y_Coordinate] = new_piece.get();
            piece = new_piece.get();
            pieces_.push_back(std::move(new_piece));
            break;
    }
}

bool Game_State::is_legal_move(Position position, Piece* piece) {
    auto it = std::find_if( possible_moves_[piece].begin(),  possible_moves_[piece].end(),
                           [position](const std::pair<Position, Piece::Move_type>& p) { return p.first == position; });
    return it !=  possible_moves_[piece].end();
}

std::vector<Position> Game_State::get_postitions_attacked_by_team (Piece::Team team) const{
    std::vector<Position> pos;
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(board_[i][j] != nullptr){
                if(board_[i][j] -> get_team() == team){
                    auto moves = board_[i][j] ->calculate_possible_moves(board_);
                    if(!moves.empty()) {
                        for(const auto& move : moves){
                            pos.push_back(move.first);
                        }
                    }
                }
            }
        }
    }
    return pos;
}

bool Game_State::check_check_after_move(Piece* piece, Position new_position, Piece::Move_type Move_type) {
    Piece::Team attacking_team;
    Position kings_position;
    Piece* taken_piece;
    Position original_position = piece->get_position();

    if(Move_type == Piece::EN_PASSANT){
        if(new_position.Y_Coordinate == 2){
            taken_piece = board_[new_position.X_Coordinate][new_position.Y_Coordinate + 1];
        }
        else{
            taken_piece = board_[new_position.X_Coordinate][new_position.Y_Coordinate - 1];
        }
    }
    else{
        taken_piece = board_[new_position.X_Coordinate][new_position.Y_Coordinate];
    }

    make_move(piece, new_position, Move_type,true);

    if(piece->get_team() == Piece::WHITE){
        attacking_team = Piece::BLACK;
        kings_position = white_king_->get_position();
    }
    else{
        attacking_team = Piece::WHITE;
        kings_position = black_king_->get_position();
    }

    if(piece->get_piecetype() == Piece::KING && piece->get_team() != attacking_team){
        kings_position = new_position;
    }

    auto positions_attacked = get_postitions_attacked_by_team(attacking_team);
    auto it = std::find(positions_attacked.begin(), positions_attacked.end(), kings_position);
    undo_move(piece, taken_piece, original_position, new_position, Move_type);
    return it != positions_attacked.end();
}

void Game_State::calculate_all_possible_moves_with_check(){
    std::map<Piece*,std::vector<std::pair<Position, Piece::Move_type>>> legal_moves_for_all_pieces;
    for(size_t i = 0; i < 8; ++i){
        for(size_t j = 0; j < 8; ++j) {
            if (board_[i][j] != nullptr) {
                auto legal_moves = board_[i][j]->calculate_possible_moves(board_);
                for(const auto& move : legal_moves){
                    if(!check_check_after_move(board_[i][j],move.first, move.second)){
                        legal_moves_for_all_pieces[board_[i][j]].push_back(move);
                    }
                }
            }
        }
    }
    possible_moves_ = legal_moves_for_all_pieces;
}