//
// Created by bialo on 20.04.2023.
//

#ifndef CHESS_GAME_GAME_STATE_HPP
#define CHESS_GAME_GAME_STATE_HPP
#include<vector>
#include<pieces.hpp>
#include<memory>

enum class move_type{
    NORMAL, CASTLE, EN_PASSANT, PROMOTION
};

struct Game_State{
    static std::vector<Piece> pieces_;
    bool is_in_check();
    std::pair<Position,bool> is_occupied;
};

#endif //CHESS_GAME_GAME_STATE_HPP
