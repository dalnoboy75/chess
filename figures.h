#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H
#include <Graph_lib/Point.h>
#include <Graph_lib/Simple_window.h>
#include "cell.h"
using namespace std;
using namespace Graph_lib;
struct Figure:Graph_lib::Image{
    Figure(Graph_lib::Window& win, const string& s, Point p): Graph_lib::Image(Point{0,0},s){
        this->set_mask(p,size, size);
        win.attach(*this);
    }

    virtual bool is_black() = 0;
    void attach(const Cell& c);
    void detach(){
        cell = nullptr;
    }
private:
    const Cell* cell{nullptr};
    const int size = 90;
    int x = 45, y = 45;
};

struct Pawn: Figure{ // это пешка (Матвей не понимает потому что он дурачок и не знает английского)
    Pawn(Graph_lib::Window& win, const string& s,Point p, bool color):Figure(win, s,p), color{color}{};
    bool is_black() override{return color;}
private:
    bool color; // true - белый, false - черный
};

#endif //CHESS_FIGURES_H
