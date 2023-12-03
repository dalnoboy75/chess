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
    void invisible(){
        move(10000,10000);
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

struct Rook : Figure{ //это ладья (Иван не понимает, потому что он дурачек и не знает тоже английского)
    Rook (Graph_lib::Window& win, const string& s, Point p, bool color): Figure(win,s,p, rook), color{color}{};
    bool is_white() override{return color;}
private:
    bool color; // true - белый, false - черный
};

struct Knight : Figure{ 
    Knight (Graph_lib::Window& win, const string& s, Point p, bool color): Figure(win,s,p, knight), color{color}{};
    bool is_white() override{return color;}
private:
    bool color; // true - белый, false - черный
};

struct Bishop : Figure{ 
    Bishop (Graph_lib::Window& win, const string& s, Point p, bool color): Figure(win,s,p, bishop), color{color}{};
    bool is_white() override{return color;}
private:
    bool color; // true - белый, false - черный
};

struct Queen : Figure{ 
    Queen (Graph_lib::Window& win, const string& s, Point p, bool color): Figure(win,s,p, queen), color{color}{};
    bool is_white() override{return color;}
private:
    bool color; // true - белый, false - черный
};

struct King : Figure{ 
    King (Graph_lib::Window& win, const string& s, Point p, bool color): Figure(win,s,p, king), color{color}{};
    bool is_white() override{return color;}
private:
    bool color; // true - белый, false - черный
};

struct Virtual_move: Graph_lib::Circle
{
  Virtual_move(Graph_lib::Window& win) : Circle{Point{0, 0}, r}
  {
    win.attach(*this);
  }

  void draw_lines () const override { Circle::draw_lines(); }

  

  void attach (const Cell& c);

  void detach () { cell = nullptr; }

private:
  static constexpr int r = 0.4 * Cell::size / 2;
  const Cell* cell{nullptr};
};

#endif //CHESS_FIGURES_H



/*
    A* ptr = static_cast<A*>(new char[sizeof(A) * 3]);
    A* elems = new(ptr A[3]);
    delete[] static_cast<char*>(ptr);
    
*/