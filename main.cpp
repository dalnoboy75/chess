#include <exception>
#include <iostream>
#include "game_position.h"

using namespace Graph_lib;

int ex_chessboard() {
    Chessboard board{Point{100, 100}};
    GamePosition game_position;
    game_position.reading("../game_pos.txt");
    game_position.visualise(board);
    board.wait_for_button();
    return 0;

}

int main()
try {
    ex_chessboard();
}
catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
}
catch (...) {
    std::cerr << "Oops, something went wrong..." << std::endl;
    return 2;
}
