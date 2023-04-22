//
// Created by michalbialozyt on 19.04.2023.
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

void calculate_vertical_and_horizontal_moves(std::vector<Position>& vec, Position position, Game_State& current_game_state){
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
    calculate_vertical_and_horizontal_moves(legal_moves, position_,current_game_state);
}

//legal moves for the queen not considering taking nad checks
std::vector<Position> Queen::calculate_possible_moves(Game_State& current_game_state) const {
    std::vector<Position> legal_moves;
    calculate_vertical_and_horizontal_moves(legal_moves, position_,current_game_state);
    add_diagonal_moves(legal_moves, position_,current_game_state);
}