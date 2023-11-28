#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H
#include <Graph_lib/Point.h>
#include <Graph_lib/Simple_window.h>
#include "cell.h"
#include "constants.h"
using namespace std;
using namespace Graph_lib;
struct Figure:Graph_lib::Image{
    Figure(Graph_lib::Window& win, const string& s, Point p, char type): Graph_lib::Image(Point{0,0},s), type{type}{
        this->set_mask(p,size, size);
        win.attach(*this);
    }

    virtual bool is_white() = 0;
    void attach(const Cell& c);
    void detach(){
        cell = nullptr;
    }
    char get_type(){return type;}
private:
    const Cell* cell{nullptr};
    const int size = 90;
    int x = 45, y = 45;
    char type;
};

struct Pawn: Figure{ // это пешка (Матвей не понимает потому что он дурачок и не знает английского)
    Pawn(Graph_lib::Window& win, const string& s,Point p, bool color):Figure(win, s,p, pawn), color{color}{};
    bool is_white() override{return color;}
private:
    bool color; // true - белый, false - черный
};

#endif //CHESS_FIGURES_H
