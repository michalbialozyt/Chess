//
// Created by michal bialozyt on 20.04.2023.
//

#pragma once
#include <vector>
#include "pieces.hpp"
#include <memory>
#include <map>
#include <unordered_set>

class Game_State{
public:
    enum Game_Result {
        NO_RESULT, WHITE_WIN, BLACK_WIN, DRAW_BY_STALEMATE, DRAW_BY_50_MOVES
    };
    Game_State();
    Piece* board_[8][8]{};
    std::map<Piece*,std::vector<std::pair<Position, Piece::Move_type>>> possible_moves_;

    bool is_legal_move(Position position, Piece* piece);

    //for checkmate
    [[nodiscard]] std::vector<Position> get_postitions_attacked_by_team (Piece::Team team) const;

    Game_Result check_game_result();

    //return yes if possible moves were found
    void calculate_all_possible_moves_with_check(Piece::Team team_on_move);

    void make_move(Piece* piece, const Position& new_position, const Piece::Move_type& Move_type, bool is_test);
    void undo_move(Piece* piece, Piece* taken_piece, Position original_position, Position new_position,Piece::Move_type Move_type);

    //for move being legal
    bool check_check_after_move(Piece* piece, Position new_position, Piece::Move_type Move_type);
    ~Game_State() = default;

private:
    std::size_t num_of_pieces_on_the_board_;
    int number_of_turns_without_progress_;
    Piece* white_king_;
    Piece* black_king_;
    //Piece::Team top_board_team_;
    std::vector<std::unique_ptr<Piece>> pieces_;

};
