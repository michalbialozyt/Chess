//
// Created by michal bialozyt on 19.04.2023.
//

#pragma once
#include <vector>
#include <set>
#include "position.hpp"

class Piece{
public:
    enum Piece_type{
        PAWN, QUEEN, KING, ROOK, KNIGHT, BISHOP
    };
    enum Team {
        WHITE, BLACK
    };
    enum Move_type{
        NORMAL, CASTLE, EN_PASSANT, PROMOTION
    };
    Piece(const Position& start_position, const Team& team, const Piece_type& piecetype) : team_(team), piecetype_(piecetype), position_(start_position) {}
    Piece(const Piece& other) = default;
    [[nodiscard]] Position get_position () const {return position_;}
    [[nodiscard]] Team get_team () const {return team_;}
    [[nodiscard]] Piece_type get_piecetype() const {return piecetype_;}
    virtual const char* get_image_name() = 0;
    [[nodiscard]] virtual std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const = 0;
    void set_position(Position new_position) {position_ = new_position;}
    virtual ~Piece() = default;
    virtual void set_en_passant(bool) {};
    [[nodiscard]] virtual bool check_en_passant() const {return false;}
    bool has_moved_ = false;

    bool operator==(const Piece& other) const  {
        return this->position_ == other.get_position() && this->team_ == other.get_team() && this->piecetype_ == other.get_piecetype() ;
    }
    bool operator!=(const Piece& other) const  {
        return this->position_ != other.get_position() || this->team_ != other.get_team() || this->piecetype_ != other.get_piecetype() ;
    }

protected:
    Team team_;
    Piece_type piecetype_;
    Position position_;
};

class Pawn: public Piece {
public:
    Pawn(const Pawn& other) = default;
    Pawn(const Position& start_position, Team team) : Piece(start_position, team, PAWN), en_passant_enabled(false){}
    const char* get_image_name() override;
    void set_en_passant(bool setting) override {en_passant_enabled = setting;}
    [[nodiscard]] bool check_en_passant() const override {return en_passant_enabled;}
    [[nodiscard]] std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const override;

private:
    bool en_passant_enabled;
};

class King: public Piece {
public:

    King(const Position& start_position, const Team& team) : Piece(start_position, team,KING){}
    [[nodiscard]] std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const override;
    const char* get_image_name() override;
    ~King() override = default;
};

class Queen: public Piece {
public:
    Queen(const Position& start_position, const Team& team) : Piece(start_position, team, QUEEN){}
    [[nodiscard]] std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const override;
    const char* get_image_name() override;
    ~Queen() override = default;
};

class Knight: public Piece {
public:
    Knight(const Position& start_position, const Team& team) : Piece(start_position, team, KNIGHT){}
    [[nodiscard]] std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const override;
    const char* get_image_name() override;
    ~Knight() override = default;
};

class Bishop: public Piece {
public:
    Bishop(const Position& start_position, const Team& team) : Piece(start_position, team, BISHOP){}
    [[nodiscard]] std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const override;
    const char* get_image_name() override;
    ~Bishop() override = default;
};

class Rook: public Piece {
public:
    Rook(const Rook& other) = default;
    Rook(const Position& start_position, const Team& team) : Piece(start_position, team, ROOK){}
    [[nodiscard]] std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves(const Piece* const (&board)[8][8]) const override;
    const char* get_image_name() override;
    ~Rook() override = default;
};

void add_vertical_and_horizontal_moves(std::vector<std::pair<Position,Piece::Move_type>>& vec, Position position, const Piece* const (&board)[8][8]);
void add_diagonal_moves(std::vector<std::pair<Position,Piece::Move_type>>& vec, Position position, const Piece* const (&board)[8][8]);

struct Knight_moves{
    inline static std::set<std::pair<int,int>> horsey_moves_{std::make_pair(1,2), std::make_pair(1,-2),std::make_pair(-1,2),std::make_pair(-1,-2),std::make_pair(2,1),std::make_pair(-2,-1),std::make_pair(-2,1),std::make_pair(2,-1)};
};