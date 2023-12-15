#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H

#include <Graph_lib/Point.h>
#include <Graph_lib/Simple_window.h>
#include "cell.h"
#include "constants.h"

using namespace std;
using namespace Graph_lib;

struct Figure : Graph_lib::Image {
    Figure(Graph_lib::Window &win, const string &s, Point p, char type, bool color) : Graph_lib::Image(Point{0, 0}, s),
                                                                                      type{type}, color{color} {
        this->set_mask(p, size, size);
        win.attach(*this);
    }

    virtual bool is_white() = 0;

    void attach(const Cell &c);

    void detach() {
        cell = nullptr;
    }

    char get_type() { return type; }

protected:
    bool color; // true - белый, false - черный
private:
    const Cell *cell{nullptr};
    const int size = 90;
    char type;
};

struct Pawn : Figure { // это пешка (Матвей не понимает потому что он дурачок и не знает английского)
    Pawn(Graph_lib::Window &win, const string &s, bool color) : Figure(win, s, color ? white_pawn : black_pawn, pawn,
                                                                       color) {};

    bool is_white() override { return color; }
};

struct Rook : Figure { //это ладья (Иван не понимает, потому что он дурачек и не знает тоже английского)
    Rook(Graph_lib::Window &win, const string &s, bool color) : Figure(win, s, color ? white_rook : black_rook, rook,
                                                                       color) {};

    bool is_white() override { return color; }

};

struct Knight : Figure {
    Knight(Graph_lib::Window &win, const string &s, bool color) : Figure(win, s, color ? white_knight : black_knight,
                                                                         knight, color) {};

    bool is_white() override { return color; }

};

struct Bishop : Figure {
    Bishop(Graph_lib::Window &win, const string &s, bool color) : Figure(win, s, color ? white_bishop : black_bishop,
                                                                         bishop, color) {};

    bool is_white() override { return color; }

};

struct Queen : Figure {
    Queen(Graph_lib::Window &win, const string &s, bool color) : Figure(win, s, color ? white_queen : black_queen,
                                                                        queen, color) {};

    bool is_white() override { return color; }
};

struct King : Figure {
    King(Graph_lib::Window &win, const string &s, bool color) : Figure(win, s, color ? white_king : black_king, king,
                                                                       color) {};

    bool is_white() override { return color; }

};


#endif //CHESS_FIGURES_H

