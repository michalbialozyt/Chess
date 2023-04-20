//
// Created by bialo on 19.04.2023.
//

#ifndef CHESS_PIECES_HPP
#define CHESS_PIECES_HPP
#include <vector>
#include "game_state.hpp"

class Position {
public:
    Position(int x, int y) : X_Coordinate(x), Y_Coordinate(y){}
    int X_Coordinate;
    int Y_Coordinate;
};

enum class Team {
    None = 0, WHITE, BLACK
};

class Piece{
public:
    Position position_;
    Team team_;
    Piece(const Position& start_position, const Team& team) : position_(start_position), team_(team){}
    Piece(const Piece& other) = default;
    Position get_position () const {return position_;}
    Team get_team () const {return team_;}
    virtual std::vector<Position> calculate_possible_moves(Game_State& current_game_state) const = 0;
    void set_position(Position new_position) {position_ = new_position;};
    ~Piece() = default;
};

class King: public Piece {
public:
    King(const Position& start_position, const Team& team) : Piece(start_position, team){}
    std::vector<Position> calculate_possible_moves(Game_State& current_game_state) const override;
    ~King() = default;
};

class Queen: public Piece {
public:
    Queen(const Position& start_position, const Team& team) : Piece(start_position, team){}
    std::vector<Position> calculate_possible_moves(Game_State& current_game_state) const override;
    ~Queen() = default;
};

class Knight: public Piece {
public:
    Knight(const Position& start_position, const Team& team) : Piece(start_position, team){}
    std::vector<Position> calculate_possible_moves(Game_State& current_game_state) const override;
    ~Knight() = default;
};

class Bishop: public Piece {
public:
    Bishop(const Position& start_position, const Team& team) : Piece(start_position, team){}
    std::vector<Position> calculate_possible_moves(Game_State& current_game_state) const override;
    ~Bishop() = default;
};

class Rook: public Piece {
public:
    Rook(const Position& start_position, const Team& team) : Piece(start_position, team){}
    std::vector<Position> calculate_possible_moves(Game_State& current_game_state) const override;
    ~Rook() = default;
};

#endif //CHESS_PIECES_HPP