//
// Created by michal bialozyt on 19.04.2023.
//

#include "pieces.hpp"

//checking possible moves for the king/ not including taking or check
std::vector<std::pair<Position,Piece::Move_type>> King::calculate_possible_moves(const Piece* const (&board)[8][8]) const {
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;

    for(int i = -1; i < 2; ++i){
        for(int j = -1; j < 2; ++j){
            Position pos = Position(position_.X_Coordinate + i,position_.Y_Coordinate + j);
            if(pos.X_Coordinate >= 0 && pos.X_Coordinate < 8 && pos.Y_Coordinate >= 0 && pos.Y_Coordinate < 8){
                if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr || board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != team_) {
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }
    }

    if(board[position_.X_Coordinate + 3][position_.Y_Coordinate] != nullptr) {
        if (!has_moved_ && !board[position_.X_Coordinate + 3][position_.Y_Coordinate]->has_moved_ && board[position_.X_Coordinate + 1][position_.Y_Coordinate] == nullptr && board[position_.X_Coordinate + 2][position_.Y_Coordinate] == nullptr){
            legal_moves.emplace_back(Position(position_.X_Coordinate + 2, position_.Y_Coordinate),Piece::CASTLE);
        }
    }

    if(board[position_.X_Coordinate - 4][position_.Y_Coordinate] != nullptr) {
        if (!has_moved_ && !board[position_.X_Coordinate - 4][position_.Y_Coordinate]->has_moved_ && board[position_.X_Coordinate - 3][position_.Y_Coordinate] == nullptr && board[position_.X_Coordinate - 2][position_.Y_Coordinate] == nullptr && board[position_.X_Coordinate - 1][position_.Y_Coordinate] == nullptr){
            legal_moves.emplace_back(Position(position_.X_Coordinate - 2, position_.Y_Coordinate),Piece::CASTLE);
        }
    }

    return legal_moves;
}

//checking possible moves for the pawn not including taking or check or en passant
std::vector<std::pair<Position,Piece::Move_type>> Pawn::calculate_possible_moves(const Piece* const (&board)[8][8]) const {
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;
    Position pos;

    if (team_ == BLACK) {
        pos = Position(position_.X_Coordinate, position_.Y_Coordinate + 1);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            if(position_.Y_Coordinate == 6){
                legal_moves.emplace_back(pos, Piece::PROMOTION);
            }
            else{
                legal_moves.emplace_back(pos, Piece::NORMAL);
            }
            if (position_.Y_Coordinate == 1) {
                pos.Y_Coordinate = position_.Y_Coordinate + 2;
                if (board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }

        pos.Y_Coordinate = position_.Y_Coordinate + 1;
        pos.X_Coordinate = position_.X_Coordinate + 1;
        if(pos.X_Coordinate >= 0 && pos.X_Coordinate < 8 && pos.Y_Coordinate >= 0 && pos.Y_Coordinate < 8 && board[pos.X_Coordinate][pos.Y_Coordinate] != nullptr) {
            if (board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != team_) {
                if(position_.Y_Coordinate == 6){
                    legal_moves.emplace_back(pos, Piece::PROMOTION);
                }
                else{
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }

        pos.X_Coordinate = position_.X_Coordinate - 1;
        if(pos.X_Coordinate >= 0 && pos.X_Coordinate < 8 && pos.Y_Coordinate >= 0 && pos.Y_Coordinate < 8 && board[pos.X_Coordinate][pos.Y_Coordinate] != nullptr) {
            if (board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != team_) {
                if(position_.Y_Coordinate == 6){
                    legal_moves.emplace_back(pos, Piece::PROMOTION);
                }
                else{
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }

        if(position_.Y_Coordinate == 4) {
            if (position_.X_Coordinate < 7 && board[position_.X_Coordinate + 1][position_.Y_Coordinate] != nullptr) {
                if (board[position_.X_Coordinate + 1][position_.Y_Coordinate]->get_piecetype() == Piece::PAWN && board[position_.X_Coordinate + 1][position_.Y_Coordinate]->check_en_passant()){
                    legal_moves.emplace_back(Position(position_.X_Coordinate + 1, position_.Y_Coordinate + 1),Piece::EN_PASSANT);
                }
            }
            else if(position_.X_Coordinate > 0  && board[position_.X_Coordinate - 1][position_.Y_Coordinate] != nullptr) {
                if (board[position_.X_Coordinate - 1][position_.Y_Coordinate]->get_piecetype() == Piece::PAWN && board[position_.X_Coordinate - 1][position_.Y_Coordinate]->check_en_passant()){
                    legal_moves.emplace_back(Position(position_.X_Coordinate - 1, position_.Y_Coordinate + 1),Piece::EN_PASSANT);
                }
            }
        }
    }

    else {
        pos = Position(position_.X_Coordinate, position_.Y_Coordinate - 1);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr) {
            if(position_.Y_Coordinate == 1){
                legal_moves.emplace_back(pos, Piece::PROMOTION);
            }
            else{
                legal_moves.emplace_back(pos, Piece::NORMAL);
            }
            if (position_.Y_Coordinate == 6) {
                pos = Position(position_.X_Coordinate, position_.Y_Coordinate - 2);
                if (board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr) {
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }

        pos.Y_Coordinate = position_.Y_Coordinate - 1;
        pos.X_Coordinate = position_.X_Coordinate + 1;
        if(pos.X_Coordinate >= 0 && pos.X_Coordinate < 8 && pos.Y_Coordinate >= 0 && pos.Y_Coordinate < 8 && board[pos.X_Coordinate][pos.Y_Coordinate] != nullptr) {
            if (board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != team_) {
                if(position_.Y_Coordinate == 1){
                    legal_moves.emplace_back(pos, Piece::PROMOTION);
                }
                else{
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }

        pos.X_Coordinate = position_.X_Coordinate - 1;
        if(pos.X_Coordinate >= 0 && pos.X_Coordinate < 8 && pos.Y_Coordinate >= 0 && pos.Y_Coordinate < 8 && board[pos.X_Coordinate][pos.Y_Coordinate] != nullptr) {
            if (board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != team_) {
                if(position_.Y_Coordinate == 1){
                    legal_moves.emplace_back(pos, Piece::PROMOTION);
                }
                else{
                    legal_moves.emplace_back(pos, Piece::NORMAL);
                }
            }
        }

        if(position_.Y_Coordinate == 3) {
            if (position_.X_Coordinate < 7 && board[position_.X_Coordinate + 1][position_.Y_Coordinate] != nullptr) {
                if (board[position_.X_Coordinate + 1][position_.Y_Coordinate]->get_piecetype() == Piece::PAWN && board[position_.X_Coordinate + 1][position_.Y_Coordinate]->check_en_passant()){
                    legal_moves.emplace_back(Position(position_.X_Coordinate + 1, position_.Y_Coordinate - 1),Piece::EN_PASSANT);
                }
            }
            else if(position_.X_Coordinate > 0 && board[position_.X_Coordinate - 1][position_.Y_Coordinate] != nullptr) {
                if (board[position_.X_Coordinate - 1][position_.Y_Coordinate]->get_piecetype() == Piece::PAWN && board[position_.X_Coordinate - 1][position_.Y_Coordinate]->check_en_passant()){
                    legal_moves.emplace_back(Position(position_.X_Coordinate - 1, position_.Y_Coordinate - 1),Piece::EN_PASSANT);
                }
            }
        }
    }

    return legal_moves;
}

//checking possible moves for the knight not including taking or check
std::vector<std::pair<Position,Piece::Move_type>> Knight::calculate_possible_moves(const Piece* const (&board)[8][8]) const {
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;

    for(const auto& move : Knight_moves::horse_moves_){
        Position pos = Position(position_.X_Coordinate + move.first, position_.Y_Coordinate + move.second);
        if(pos.X_Coordinate < 8 && pos.X_Coordinate >= 0 && pos.Y_Coordinate < 8 && pos.Y_Coordinate >= 0){
            if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr || board[pos.X_Coordinate][pos.Y_Coordinate] -> get_team() != team_){
                legal_moves.emplace_back(pos, Piece::NORMAL);
            }
        }
    }

    return legal_moves;
}

void add_vertical_and_horizontal_moves(std::vector<std::pair<Position,Piece::Move_type>>& vec, Position position, const Piece* const (&board)[8][8]){
    int i = position.X_Coordinate + 1;
    int j = position.Y_Coordinate;

    while(i < 8){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            i++;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }

    i = position.X_Coordinate - 1;

    while(i >= 0){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            i--;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }

    i = position.X_Coordinate;
    j = position.Y_Coordinate + 1;

    while(j < 8){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            j++;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }

    j = position.Y_Coordinate - 1;

    while(j >= 0){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            j--;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }
}

void add_diagonal_moves(std::vector<std::pair<Position,Piece::Move_type>>& vec, Position position, const Piece* const (&board)[8][8]){
    int i = position.X_Coordinate + 1;
    int j = position.Y_Coordinate + 1;

    while(i < 8 && j < 8){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            i++;
            j++;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }

    i = position.X_Coordinate - 1;
    j = position.Y_Coordinate + 1;

    while(i >= 0 && j < 8){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            j++;
            i--;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }

    i = position.X_Coordinate + 1;
    j = position.Y_Coordinate - 1;

    while(j >= 0 && i < 8){
        Position pos = Position(i,j);
        if(board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr){
            vec.emplace_back(pos, Piece::NORMAL);
            i++;
            j--;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }

    i = position.X_Coordinate - 1;
    j = position.Y_Coordinate - 1;

    while(j >= 0 && i >= 0) {
        Position pos = Position(i, j);
        if (board[pos.X_Coordinate][pos.Y_Coordinate] == nullptr) {
            vec.emplace_back(pos, Piece::NORMAL);
            --i;
            --j;
        }
        else if(board[pos.X_Coordinate][pos.Y_Coordinate]->get_team() != board[position.X_Coordinate][position.Y_Coordinate]->get_team()){
            vec.emplace_back(pos, Piece::NORMAL);
            break;
        }
        else{
            break;
        }
    }
}


//legal moves for the rook not considering checks
std::vector<std::pair<Position,Piece::Move_type>> Rook::calculate_possible_moves(const Piece* const (&board)[8][8]) const{
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;
    add_vertical_and_horizontal_moves(legal_moves, position_, board);
    return legal_moves;
}

//legal moves for the bishop not considering checks
std::vector<std::pair<Position,Piece::Move_type>> Bishop::calculate_possible_moves(const Piece* const (&board)[8][8]) const{
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;
    add_diagonal_moves(legal_moves, position_,board);
    return legal_moves;
}

//legal moves for the queen not considering checks
std::vector<std::pair<Position,Piece::Move_type>> Queen::calculate_possible_moves(const Piece* const (&board)[8][8]) const {
    std::vector<std::pair<Position,Piece::Move_type>> legal_moves;
    add_vertical_and_horizontal_moves(legal_moves, position_,board);
    add_diagonal_moves(legal_moves, position_,board);
    return legal_moves;
}

std::string Pawn::get_image_name() const{
    if(team_ == BLACK){
        return images_directory_ + R"(dark_pawn.png)";
    }
    else{
        return images_directory_ + R"(white_pawn.png)";
    }
}

std::string King::get_image_name() const{
    if(team_ == BLACK){
        return images_directory_ + R"(dark_king.png)";
    }
    else{
        return images_directory_ + R"(white_king.png)";
    }
}

std::string Queen::get_image_name() const{
    if(team_ == BLACK){
        return images_directory_ + R"(dark_Queen.png)";
    }
    else{
        return images_directory_ + R"(white_Queen.png)";
    }
}

std::string Knight::get_image_name() const{
    if(team_ == BLACK){
        return images_directory_ + R"(dark_horse.png)";
    }
    else{
        return images_directory_ + R"(white_horse.png)";
    }
}

std::string Rook::get_image_name() const{
    if(team_ == BLACK){
        return images_directory_ + R"(dark_rook.png)";
    }
    else{
        return images_directory_ + R"(white_rook.png)";
    }
}

std::string Bishop::get_image_name() const{
    if(team_ == BLACK){
        return images_directory_ + R"(dark_bishop.png)";
    }
    else{
        return images_directory_ + R"(white_bishop.png)";
    }
}