#include <cstdlib>
#include <iostream>
#include "pieces.hpp"
#include "game_state.hpp"

int main() {
    //some basic temporary tests
    Piece* board[8][8];
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            Piece piece = Piece(Position(i,j), Piece::NONE_TEAM, Piece::NONE_PIECE);
            board[i][j] = &piece;
        }
    }
    Pawn p1 = Pawn(Position(1,2), Pawn::BLACK);
    std::cout << p1.get_position().X_Coordinate << "  " << p1.get_position().Y_Coordinate << std::endl;
    board[1][1] = &p1;
    auto legal_moves = p1.calculate_possible_moves(board);
    for(const auto& elem : legal_moves) {
        std::cout << elem.X_Coordinate << "  " << elem.Y_Coordinate << std::endl;
    }
    return EXIT_SUCCESS;
}
