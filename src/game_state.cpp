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
        if(elem->get_team() == Piece::WHITE){
            ++num_of_white_pieces[elem->get_piecetype()];
        }
        else{
            ++num_of_black_pieces[elem->get_piecetype()];
        }
    }

    white_king_ = board_[4][7];
    black_king_ = board_[4][0];
    num_of_pieces_on_the_board_ = 32;
    number_of_turns_without_progress_ = 0;
    calculate_all_possible_moves_with_check(Piece::WHITE);
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
            auto it = std::find_if(pieces_.begin(), pieces_.end(),[piece](const std::unique_ptr<Piece>& p) {return *piece == *p;});
            board_[piece->get_position().X_Coordinate][piece->get_position().Y_Coordinate] = nullptr;
            pieces_.erase(it);
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

        //allowing pawn to get captured by en_passant
        if(piece->get_piecetype() == Piece::PAWN && ((piece-> get_team() == Piece::BLACK && piece->get_position().Y_Coordinate == 3) || (piece-> get_team() == Piece::WHITE && piece->get_position().Y_Coordinate == 4)) && !piece->has_moved_){
            piece->set_en_passant(true);
        }
        piece->has_moved_ = true;

//        auto taken_piece = std::find_if(pieces_.begin(), pieces_.end(), [this](const auto& ptr) {
//            return *board_[ptr->get_position().X_Coordinate][ptr->get_position().Y_Coordinate] != *ptr;});

//        if(taken_piece->get() != nullptr){
//            if(taken_piece->get()->get_team() == Piece::WHITE){
//                --num_of_white_pieces[taken_piece->get()->get_piecetype()];
//            }
//            else {
//                --num_of_black_pieces[taken_piece->get()->get_piecetype()];
//            }
//        }
//        pieces_.erase(taken_piece);
//        remove all pieces that are no longer on the board from the pieces_ vector
        pieces_.erase(std::remove_if(pieces_.begin(), pieces_.end(), [this](const auto& ptr) {
            return *board_[ptr->get_position().X_Coordinate][ptr->get_position().Y_Coordinate] != *ptr;
        }), pieces_.end());

        if(num_of_pieces_on_the_board_ != pieces_.size() || piece->get_piecetype() == Piece::PAWN){
            number_of_turns_without_progress_ = 0;
        }
        num_of_pieces_on_the_board_ = pieces_.size();
        ++number_of_turns_without_progress_;
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
            auto it = std::find_if(pieces_.begin(), pieces_.end(),[piece](const std::unique_ptr<Piece>& p) {return *piece == *p;});
            board_[new_position.X_Coordinate][new_position.Y_Coordinate] = taken_piece;
            pieces_.erase(it);
            auto new_piece = std::make_unique<Pawn>(Position(original_position.X_Coordinate,original_position.Y_Coordinate), piece->get_team());
            board_[original_position.X_Coordinate][original_position.Y_Coordinate] = new_piece.get();
            //piece = new_piece.get();
            pieces_.push_back(std::move(new_piece));
            break;
    }
}

bool Game_State::is_legal_move(Position position, Piece* piece) {
    auto it = std::find_if( possible_moves_[piece].cbegin(),  possible_moves_[piece].cend(),
                            [position](const std::pair<Position, Piece::Move_type>& p) { return p.first == position; });
    return it !=  possible_moves_[piece].end();
}

std::vector<Position> Game_State::get_postitions_attacked_by_team (Piece::Team team) const{
    std::vector<Position> pos;
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(board_[i][j] != nullptr && board_[i][j] -> get_team() == team){
                auto moves = board_[i][j] ->calculate_possible_moves(board_);
                if(!moves.empty()) {
                    for(const auto& move : moves){
                        pos.push_back(move.first);
                    }
                }
            }
        }
    }
    return pos;
}

bool Game_State::check_check_after_move(Piece* piece, Position new_position, Piece::Move_type Move_type) {
    auto attacking_team = Piece::WHITE;
    auto kings_position = black_king_->get_position();
    auto taken_piece = board_[new_position.X_Coordinate][new_position.Y_Coordinate];
    auto original_position = piece->get_position();

    if(Move_type == Piece::EN_PASSANT){
        if(new_position.Y_Coordinate == 2){
            taken_piece = board_[new_position.X_Coordinate][new_position.Y_Coordinate + 1];
        }
        else{
            taken_piece = board_[new_position.X_Coordinate][new_position.Y_Coordinate - 1];
        }
    }

    make_move(piece, new_position, Move_type,true);

    if(piece->get_team() == Piece::WHITE){
        attacking_team = Piece::BLACK;
        kings_position = white_king_->get_position();
    }

    if(piece->get_piecetype() == Piece::KING && piece->get_team() != attacking_team){
        kings_position = new_position;
    }

    auto positions_attacked = get_postitions_attacked_by_team(attacking_team);
    auto it = std::find(positions_attacked.cbegin(), positions_attacked.cend(), kings_position);
    undo_move(piece, taken_piece, original_position, new_position, Move_type);
    return it != positions_attacked.end();
}

void Game_State::calculate_all_possible_moves_with_check(Piece::Team team_on_move){
    possible_moves_.clear();
    for(const auto& piece : pieces_){
        if (piece->get_team() == team_on_move){
            auto legal_moves = piece->calculate_possible_moves(board_);
            for(const auto& move : legal_moves){
                if(!check_check_after_move(piece.get(),move.first, move.second)){
                    possible_moves_[piece.get()].push_back(move);
                }
            }
        }
    }
}

Game_State::Game_Result Game_State::check_game_result(){
    if(possible_moves_.empty()){
        auto attacked_by_white = get_postitions_attacked_by_team(Piece::WHITE);
        auto attacked_by_black = get_postitions_attacked_by_team(Piece::BLACK);
        auto it = std::find(attacked_by_white.cbegin(), attacked_by_white.cend(), black_king_->get_position());
        if(it != attacked_by_white.cend()){
            return Game_State::WHITE_WIN;
        }
        auto it2 = std::find(attacked_by_black.cbegin(), attacked_by_black.cend(), white_king_->get_position());
        if(it2 != attacked_by_black.cend()){
            return Game_State::BLACK_WIN;
        }
        else{
            return Game_State::DRAW_BY_STALEMATE;
        }
    }
    if(number_of_turns_without_progress_ == 50){
        return Game_State::DRAW_BY_50_MOVES;
    }
    bool is_unsufficient_material_white = false;
    bool is_unsufficient_material_black = false;

    if(num_of_white_pieces[Piece::PAWN] == 0 && num_of_white_pieces[Piece::QUEEN] == 0 && num_of_white_pieces[Piece::ROOK] == 0){
        if(num_of_white_pieces[Piece::KNIGHT] <= 2 && num_of_white_pieces[Piece::BISHOP] <= 1 && !(num_of_white_pieces[Piece::KNIGHT] == 1  && num_of_white_pieces[Piece::BISHOP] == 1)){
            is_unsufficient_material_white = true;
        }
    }
    if(num_of_black_pieces[Piece::PAWN] == 0 && num_of_black_pieces[Piece::QUEEN] == 0 && num_of_black_pieces[Piece::ROOK] == 0){
        if(num_of_black_pieces[Piece::KNIGHT] <= 2 && num_of_black_pieces[Piece::BISHOP] <= 1 && !(num_of_black_pieces[Piece::KNIGHT] == 1  && num_of_black_pieces[Piece::BISHOP] == 1)){
            is_unsufficient_material_black = true;
        }
    }

    if(is_unsufficient_material_white && is_unsufficient_material_black){
        return Game_State::DRAW_BY_INSUFFICIENT_MATERIAL;
    }
    return Game_State::NO_RESULT;
}