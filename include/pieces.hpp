//
// Created by bialo on 19.04.2023.
//

#ifndef CHESS_PIECES_HPP
#define CHESS_PIECES_HPP
#include<vector>

struct Position {
    int X_Coordinate;
    int Y_Coordinate;
};

enum class Color {
    None = 0, WHITE, BLACK
};

enum class Team {
    None = 0, WHITE, BLACK
};

class Piece{
protected:
    Position position_;
    Color color_;
    Team team_;
public:
    Piece() = default;
    Piece(const Piece& other);
    Position get_position () const {return position_;}
    Color get_color () const {return color_;}
    Team get_team () const {return team_;}
    virtual std::vector<Position> calculate_possible_moves() = 0;
    void set_position (Position new_position);
    ~Piece() = default;
};

#endif //CHESS_PIECES_HPP