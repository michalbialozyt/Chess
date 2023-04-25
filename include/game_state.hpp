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
    Piece::Team get_top_board_team () const {return top_board_team_;}
    bool is_in_check() const {return false;}
};

