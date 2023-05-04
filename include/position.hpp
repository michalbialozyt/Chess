//
// Created by bialo on 25.04.2023.
//

#pragma once

struct Position {
    explicit Position(int x = -1, int y = -1) : X_Coordinate(x), Y_Coordinate(y){}
    int X_Coordinate;
    int Y_Coordinate;
    bool operator==(const Position& other) const  {
        return this->X_Coordinate == other.X_Coordinate && this->Y_Coordinate == other.Y_Coordinate;
    }

};