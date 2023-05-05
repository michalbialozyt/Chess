//
// Created by michal bialozyt on 20.04.2023.
//

#pragma once
#include <vector>
#include "pieces.hpp"
#include <memory>
#include <map>

class Game_State{
private:
    Piece* white_king_;
    Piece* black_king_;
    Piece::Team top_board_team_;
    std::vector<std::unique_ptr<Piece>> pieces_;
public:
    Piece* board_[8][8];
    std::map<Piece*,std::vector<std::pair<Position, Piece::Move_type>>> possible_moves_;
    Game_State();
    bool is_legal_move(Position position, Piece* piece);
    //for checkmate
    std::vector<Position> get_postitions_attacked_by_team (Piece::Team team) const;
    Piece::Team get_top_board_team () const {return top_board_team_;}

    void calculate_all_possible_moves_with_check();
    void make_move(Piece* piece, Position new_position, Piece::Move_type Move_type, bool is_test);
    void undo_move(Piece* piece, Piece* taken_piece, Position original_position, Position new_position,Piece::Move_type Move_type);
    //for move being legal
    bool check_check_after_move(Piece* piece, Position new_position, Piece::Move_type Move_type);
    ~Game_State() = default;
};
