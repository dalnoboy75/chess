#include <iostream>
#include <cmath>
#include "constants.h"
#include "board.h"

using namespace Graph_lib;


Cell::Type type_of_cell(int i, int j) {
    if (i % 2 == 0)
        return (j % 2 == 0) ? Cell::black : Cell::white;
    else
        return (j % 2 == 0) ? Cell::white : Cell::black;
}


std::string letters() {
    std::string s(Chessboard::N_max, '\0');

    for (int i = 0; i < Chessboard::N_max; ++i)
        s[i] = 'a' + i;

    return s;
}

std::string digits() {
    std::string s(Chessboard::N_max, '\0');

    for (int i = 0; i < Chessboard::N_max; ++i)
        s[i] = '1' + i;

    return s;
}


Chessboard::Chessboard(Point xy)
        : My_window{xy, width, height, "Checkerboard"}, x_labels{letters()}, y_labels{digits()} {
    size_range(width, height, width, height);  // fixed window size

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            cells.push_back(new Cell{Point{margin + j * Cell::size,
                                           margin + (N - 1 - i) * Cell::size},
                                     cb_clicked, type_of_cell(i, j), (i + 1), j});
            attach(cells[cells.size() - 1]);
        }

    for (int i = 0; i < N; ++i) {
        // board corners: left top
        constexpr Point lt{margin + Cell::size / 2,
                           margin + N * Cell::size + 10};
        // and right bottom
        constexpr Point rb{margin - 10,
                           margin + N * Cell::size - Cell::size / 2};

        x_labels.add(Point{lt.x + i * Cell::size, lt.y});
        y_labels.add(Point{rb.x, rb.y - i * Cell::size});
    }
    attach(x_labels);
    attach(y_labels);
}




void Chessboard::clicked(Cell &c) {
    if (!selected) {
        selected = &c;
        c.activate();
    } else if (c.has_figure() && selected) {
        if (!selected->has_figure() || selected->get_figure().is_white() == c.get_figure().is_white() || c.get_figure().get_type() == king){
            selected->deactivate();
            selected = &c;
            c.activate();
        }
        else{
            if (selected -> get_figure().get_type() == pawn){
                if (selected->get_figure().is_white()){
                    if (c.has_figure() && ((c.number - selected -> number == 1) && abs(c.symbol - selected -> symbol) == 1)){
                        Cell &c1 = *selected;
                        c.eat_figure();
                        c.attach_figure(c1.detach_figure());
                    }
                }
                else{
                    if (c.has_figure() && (c.number - selected -> number == -1 && abs(c.symbol - selected -> symbol) == 1)){
                        Cell &c1 = *selected;
                        c.eat_figure();
                        c.attach_figure(c1.detach_figure());
                    }
                }
                selected->deactivate();
                selected = nullptr;
                c.deactivate();

            }   
            else{
                this->move_figure(c);
                selected->deactivate();
                selected = nullptr;
                c.deactivate();
            }
        }
    } else {
        if (selected->has_figure()) {
            //move figure
            this->move_figure(c);
        }
        selected->deactivate();
        selected = nullptr;
        c.deactivate();
    }

    Fl::redraw();
}

void Chessboard::move_figure(Cell &c) {
    if (selected->get_figure().get_type() == pawn){
        if (selected->get_figure().is_white()) {
            if ((c.number - selected->number == 1 || (selected->number == 2 && c.number - selected->number == 2) ) && c.symbol == selected->symbol) {
                Cell &c1 = *selected;
                c.attach_figure(c1.detach_figure());
            }
        }
        else{
            if ((c.number - selected->number == -1 ||(selected->number == 7 && c.number - selected->number == -2)) && c.symbol == selected->symbol) {
                    Cell &c1 = *selected;
                    c.attach_figure(c1.detach_figure());
            }
        }
    }

    else if (selected -> get_figure().get_type() == rook){
        int k = 0;
        if (c.number == selected -> number){
            for (int i = std::min((selected -> symbol), c.symbol) + 1; i < std::max(c.symbol, selected -> symbol); ++i){
                if (this->check_move(c.number,i)){ k += 1;}
            }
            if (k == 0 && (c.number == selected -> number || c.symbol == selected -> symbol)){
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());
            }
        }
        
        else if (c.symbol == selected -> symbol){
            for (int i = std::min(c.number, selected -> number) + 1 ; i < std::max(c.number, selected -> number); ++i){
                if (this -> check_move(i,c.symbol)){k += 1;}
            }
            if (k == 0 && (c.number == selected -> number || c.symbol == selected -> symbol)){
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());
            }

        }
            
    }
    
    else if (selected -> get_figure().get_type() == knight){
        if ((abs(c.symbol - selected -> symbol) == 1 && abs(c.number - selected -> number) == 2) || (abs(c.symbol - selected -> symbol) == 2 && abs(c.number - selected -> number) == 1)){
            Cell &c1 = *selected;
            c.eat_figure();
            c.attach_figure(c1.detach_figure());
        }
    }
    
    else if (selected -> get_figure().get_type() == bishop){
        if ((abs(c.symbol - selected -> symbol) == abs(c.number - selected -> number))){
            Cell &c1 = *selected;
            c.eat_figure();
            c.attach_figure(c1.detach_figure());
        }
    }

    else if (selected -> get_figure().get_type() == queen){
        if ((c.number == selected -> number) || (c.symbol == selected -> symbol) || (abs(c.symbol - selected -> symbol) == abs(c.number - selected -> number))){
            Cell &c1 = *selected;
            c.eat_figure();
            c.attach_figure(c1.detach_figure());
        }
    }

    else if (selected -> get_figure().get_type() == king){
        if ((abs(c.symbol - selected -> symbol) == 1 && abs(c.number - selected -> number) <= 1) || ((c.symbol == selected -> symbol) && abs(c.number - selected -> number) == 1)){
            Cell &c1 = *selected;
            c.eat_figure();
            c.attach_figure(c1.detach_figure());
        }
    }

}

bool Chessboard::check_move(int number, int symbol){
    char f = 'a' + symbol;
    return this -> at(f, number).has_figure();   
}