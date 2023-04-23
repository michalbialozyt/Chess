//
// Created by michal bialozyt on 19.04.2023.
//
#include<pieces.hpp>

//checking possible moves for the king/ not including taking or check
std::vector<Position> King::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    for(int i = -1; i < 2; ++i){
        for(int j = -1; j < 2; ++j){
            Position pos = Position(i,j);
            if(position_.X_Coordinate + i > 0 && position_.X_Coordinate + i < 8 && position_.Y_Coordinate + j > 0 && position_.Y_Coordinate + j < 8 && !current_game_state.is_occupied(pos)){
                legal_moves.emplace_back(pos);
            }
        }
    }
}

//checking possible moves for the pawn not including taking or check or en passant
std::vector<Position> Pawn::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    Position pos;
    if (current_game_state.get_top_board_team() == team_) {
        pos = Position(position_.X_Coordinate, position_.Y_Coordinate + 1);
        if (!current_game_state.is_occupied(pos)) {
            legal_moves.emplace_back(pos);
            if (position_.Y_Coordinate == 1) {
                pos = Position(position_.X_Coordinate, position_.Y_Coordinate + 2);
                if (!current_game_state.is_occupied(pos)) {
                    legal_moves.emplace_back(pos);
                }
            }
        }
    } else {
        pos = Position(position_.X_Coordinate, position_.Y_Coordinate - 1);
        if (!current_game_state.is_occupied(pos)) {
            legal_moves.emplace_back(pos);
            if (position_.Y_Coordinate == 6) {
                pos = Position(position_.X_Coordinate, position_.Y_Coordinate - 2);
                if (!current_game_state.is_occupied(pos)) {
                    legal_moves.emplace_back(pos);
                }
            }
        }
    }
}

//checking possible moves for the knight not including taking or check
std::vector<Position> Knight::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    for(auto move : Knight_moves::horsey_moves_){
        Position new_pos = Position(position_.X_Coordinate + move.first, position_.Y_Coordinate + move.second);
        if(new_pos.X_Coordinate < 8 && new_pos.X_Coordinate >= 0 && new_pos.Y_Coordinate < 8 && new_pos.Y_Coordinate >= 0 && !current_game_state.is_occupied(new_pos)){
            legal_moves.emplace_back(new_pos);
        }
    }
    return legal_moves;
}

void add_vertical_and_horizontal_moves(std::vector<Position>& vec, Position position, Game_State& current_game_state){
    int i = position.X_Coordinate + 1;
    int j = position.Y_Coordinate;
    while(i <= 8){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            i++;
        }
        else{
            break;
        }
    }
    i = position.X_Coordinate - 1;
    while(i >= 0){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            i--;
        }
        else{
            break;
        }
    }
    i = position.X_Coordinate;
    j = position.Y_Coordinate + 1;
    while(j <= 8){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            j++;
        }
        else{
            break;
        }
    }
    j = position.Y_Coordinate - 1;
    while(j >= 0){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            j--;
        }
        else{
            break;
        }
    }
}

void add_diagonal_moves(std::vector<Position>& vec, Position position, Game_State& current_game_state){
    int i = position.X_Coordinate + 1;
    int j = position.Y_Coordinate + 1;
    while(i <= 8 && j <= 8){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            i++;
            j++;
        }
        else{
            break;
        }
    }
    i = position.X_Coordinate - 1;
    j = position.Y_Coordinate + 1;
    while(i >= 0 && j <= 8){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            j--;
            i++;
        }
        else{
            break;
        }
    }
    i = position.X_Coordinate + 1;
    j = position.Y_Coordinate - 1;
    while(j >= 0 && i <= 8){
        Position pos = Position(i,j);
        if(!current_game_state.is_occupied(pos)){
            vec.emplace_back(pos);
            i++;
            j--;
        }
        else{
            break;
        }
    }
    i = position.X_Coordinate - 1;
    j = position.Y_Coordinate - 1;
    while(j >= 0 && i >= 0) {
        Position pos = Position(i, j);
        if (!current_game_state.is_occupied(pos)) {
            vec.emplace_back(pos);
            --i;
            --j;
        } else {
            break;
        }
    }
}


//legal moves for the rook not considering taking nad checks
std::vector<Position> Rook::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    add_diagonal_moves(legal_moves, position_,current_game_state);
}

//legal moves for the rook not considering taking nad checks
std::vector<Position> Bishop::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    add_vertical_and_horizontal_moves(legal_moves, position_,current_game_state);
}

//legal moves for the queen not considering taking nad checks
std::vector<Position> Queen::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    add_vertical_and_horizontal_moves(legal_moves, position_,current_game_state);
    add_diagonal_moves(legal_moves, position_,current_game_state);
}