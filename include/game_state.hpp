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
    Piece* board_[8][8];
public:
    std::vector<Piece*> get_pieces() const;
    Piece::Team get_top_board_team () const {return top_board_team_;}
    bool is_in_check() const {return false;}
    Piece*** get_board() const;
};

