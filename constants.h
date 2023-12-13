#ifndef CHESS_CONSTANTS_H
#define CHESS_CONSTANTS_H

#include <Graph_lib/Point.h>

using namespace Graph_lib;
constexpr char mate = 'm';
constexpr char pawn = 'p';
constexpr char rook = 'r';
constexpr char knight = 'k';
constexpr char bishop = 'b';
constexpr char queen = 'q';
constexpr char king = 'g';
constexpr Point white_pawn{550, 15};
constexpr Point black_pawn{550, 122};
constexpr Point white_rook{443, 15};
constexpr Point black_rook{443, 122};
constexpr Point white_knight{336, 15};
constexpr Point black_knight{336, 122};
constexpr Point white_bishop{229, 12};
constexpr Point black_bishop{229, 119};
constexpr Point white_queen{119, 12};
constexpr Point black_queen{119, 119};
constexpr Point white_king{12, 12};
constexpr Point black_king{12, 119};
constexpr int chess_green = 115;
constexpr int chess_white = 215;
#endif //CHESS_CONSTANTS_H
