//
// Created by michal bialozyt on 20.04.2023.
//

#pragma once
#include <vector>
#include "pieces.hpp"
#include <memory>


class Game_State{
private:
    Piece::Team top_board_team_;
    std::vector<std::unique_ptr<Piece>> pieces_;
public:
    Piece* board_[8][8];
    Game_State();
    bool is_legal_move(Position position, Piece* piece);
    void make_move(Piece* piece, Position new_position, Piece::Move_type Move_type);

    //for checkmate
    std::vector<std::pair<Piece*,std::vector<Position>>> calculate_all_possible_moves (Piece::Team) const;
    std::vector<Position> get_postitions_attacked_by_team (Piece::Team team);
    Piece::Team get_top_board_team () const {return top_board_team_;}

    //for move being legal
    bool check_check_after_move(Piece::Team, Piece*) const {return false;}
    ~Game_State(){}
};

