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

class Game_State{
private:
    std::vector<std::unique_ptr<Piece>> pieces_;
public:
    std::vector<Piece*> get_pieces() const;
    bool is_in_check() const;
    bool is_occupied(Position& position) const;
};

#endif //CHESS_GAME_GAME_STATE_HPP
