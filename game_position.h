#ifndef CHESS_GAME_POSITION_H
#define CHESS_GAME_POSITION_H
#include <fstream>
#include "constants.h"
#include <iostream>
#include <vector>
#include <string>
#include "board.h"

struct Position {
    char file;
    short int rank;
    string type;

    bool is_correct_type() const;
    bool is_correct_cell_id() const;
};

class GamePosition {
public:
    bool is_cell_vacant(Position &position);
    void reading(const string &file_path);
    void visualise(Chessboard &board);
private:
    vector<Position> game_position;
};




#endif