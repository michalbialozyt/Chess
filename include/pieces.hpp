//
// Created by michal bialozyt on 19.04.2023.
//

#pragma once
#include <vector>
#include "position.hpp"

class Piece{
public:
    enum Piece_type{
        NONE_PIECE = 0, PAWN, QUEEN, KING, ROOK, KNIGHT, BISHOP
    };
    enum Move_type{
        NONE_MOVE = 0, NORMAL, CASTLE, EN_PASSANT, PROMOTION
    };
    enum Team {
        NONE_TEAM = 0, WHITE, BLACK
    };
    Piece(const Position& start_position, const Team& team, const Piece_type& piecetype) : team_(team), piecetype_(piecetype), position_(start_position) {}
    Piece(const Piece& other) = default;
    Position get_position () const {return position_;}
    Team get_team () const {return team_;}
    Piece_type get_piecetype() const {return piecetype_;}
    virtual const char* get_image_name() = 0;
    virtual std::vector<Position> calculate_possible_moves(Piece*[8][8]) const = 0;
    void set_position(Position new_position) {position_ = new_position;}
    virtual ~Piece() = default;

protected:
    Team team_;
    Piece_type piecetype_;
    Position position_;
};

class Pawn: public Piece {
public:
    Pawn(const Position& start_position, Team team) : Piece(start_position, team, PAWN){}
    const char* get_image_name() override;
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
};

class King: public Piece {
public:
    King(const Position& start_position, const Team& team) : Piece(start_position, team,KING){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    const char* get_image_name() override;
    ~King() override = default;
};

class Queen: public Piece {
public:
    Queen(const Position& start_position, const Team& team) : Piece(start_position, team, QUEEN){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    const char* get_image_name() override;
    ~Queen() override = default;
};

class Knight: public Piece {
public:
    Knight(const Position& start_position, const Team& team) : Piece(start_position, team, KNIGHT){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    const char* get_image_name() override;
    ~Knight() override = default;
};

class Bishop: public Piece {
public:
    Bishop(const Position& start_position, const Team& team) : Piece(start_position, team, BISHOP){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    const char* get_image_name() override;
    ~Bishop() override = default;
};

class Rook: public Piece {
public:
    Rook(const Position& start_position, const Team& team) : Piece(start_position, team, ROOK){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    const char* get_image_name() override;
    ~Rook() override = default;
};

void add_vertical_and_horizontal_moves(std::vector<Position>& vec, Position position, Piece* board[8][8]);
void add_diagonal_moves(std::vector<Position>& vec, Position position, Piece* board[8][8]);

struct Knight_moves{
    inline static std::vector<std::pair<int,int>> horsey_moves_{std::make_pair(1,2), std::make_pair(1,-2),std::make_pair(-1,2),std::make_pair(-1,-2),std::make_pair(2,1),std::make_pair(-2,-1),std::make_pair(-2,1),std::make_pair(1,-2)};
};