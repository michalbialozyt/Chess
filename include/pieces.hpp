//
// Created by michal bialozyt on 19.04.2023.
//

#ifndef CHESS_PIECES_HPP
#define CHESS_PIECES_HPP
#include <vector>

struct Position {
    explicit Position(int x = -1, int y = -1) : X_Coordinate(x), Y_Coordinate(y){}
    int X_Coordinate;
    int Y_Coordinate;
    bool operator==(const Position& other) const {
        if (this->X_Coordinate == other.X_Coordinate && this->Y_Coordinate == other.Y_Coordinate) {
            return true;
        }
        else {
            return false;
        }
    }
};

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
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
};

class King: public Piece {
public:
    King(const Position& start_position, const Team& team) : Piece(start_position, team,KING){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    ~King() override = default;
};

class Queen: public Piece {
public:
    Queen(const Position& start_position, const Team& team) : Piece(start_position, team, QUEEN){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    ~Queen() override = default;
};

class Knight: public Piece {
public:
    Knight(const Position& start_position, const Team& team) : Piece(start_position, team, KNIGHT){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    ~Knight() override = default;
};

class Bishop: public Piece {
public:
    Bishop(const Position& start_position, const Team& team) : Piece(start_position, team, BISHOP){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    ~Bishop() override = default;
};

class Rook: public Piece {
public:
    Rook(const Position& start_position, const Team& team) : Piece(start_position, team, ROOK){}
    std::vector<Position> calculate_possible_moves(Piece* board[8][8]) const override;
    ~Rook() override = default;
};

void add_vertical_and_horizontal_moves(std::vector<Position>& vec, Position position, Piece* board[8][8]);
void add_diagonal_moves(std::vector<Position>& vec, Position position, Piece* board[8][8]);

struct Knight_moves{
    inline static std::vector<std::pair<int,int>> horsey_moves_{std::make_pair(1,2), std::make_pair(1,-2),std::make_pair(-1,2),std::make_pair(-1,-2),std::make_pair(2,1),std::make_pair(-2,-1),std::make_pair(-2,1),std::make_pair(1,-2),};
};


#endif //CHESS_PIECES_HPP