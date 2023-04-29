//
// Created by michal bialozyt on 20.04.2023.
//

#pragma once
#include <vector>
#include "pieces.hpp"
#include <memory>


class Game_State{
private:
    Piece* white_king_;
    Piece* black_king_;
    Piece::Team top_board_team_;
    std::vector<std::unique_ptr<Piece>> pieces_;
public:
    Piece* board_[8][8];
    Game_State();
    bool is_legal_move(Position position, Piece* piece) const;
    //for checkmate
    std::vector<std::pair<Position,Piece::Move_type>> get_postitions_attacked_by_team (Piece::Team team, const Piece* const (&board)[8][8]) const;
    Piece::Team get_top_board_team () const {return top_board_team_;}

    std::vector<std::pair<Position,Piece::Move_type>> calculate_possible_moves_with_check(Piece* piece) const;

    //for move being legal
    bool check_check_after_move(Piece* piece, Position new_position, Piece::Move_type Move_type) const;
    ~Game_State(){}
};

void make_move(Piece* piece, Position new_position, Piece::Move_type Move_type, Piece* board[8][8]);
