#ifndef CHESS_GAME_POSITION_H
#define CHESS_GAME_POSITION_H
#include <fstream>
#include "constants.h"
#include <iostream>
#include <vector>
#include <string>
#include "board.h"
using namespace std;



struct Position {
    char file;
    short int rank;
    string type;

    [[nodiscard]] bool is_correct_cell_id() const;
};

struct Game_Position {
    vector<Position> game_position;
    bool is_sell_vacant(Position &position);
    void reading_game_position(const string &file_path);
    void visualise_game_position(Chessboard &board);
};
string get_type_of_figure(char type, char color);




#endif