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
        if (selected->has_figure()) {
            this->virtual_move();
        }
    } else if (c.has_figure() && selected) {
        if (!selected->has_figure() || selected->get_figure().is_white() == c.get_figure().is_white() ||
            c.get_figure().get_type() == king) {
            selected->deactivate();
            this->delete_moves();
            selected = &c;
            c.activate();
            this->virtual_move();
        } else {
            this->virtual_move();
            if (selected->get_figure().get_type() == pawn) {
                if (selected->get_figure().is_white()) {
                    if (c.has_figure() &&
                        ((c.number - selected->number == 1) && abs(c.symbol - selected->symbol) == 1)) {
                        Cell &c1 = *selected;
                        c.eat_figure();
                        c.attach_figure(c1.detach_figure());
                    }
                } else {
                    if (c.has_figure() &&
                        (c.number - selected->number == -1 && abs(c.symbol - selected->symbol) == 1)) {
                        Cell &c1 = *selected;
                        c.eat_figure();
                        c.attach_figure(c1.detach_figure());
                    }
                }
                selected->deactivate();
                this->delete_moves();
                selected = nullptr;
                c.deactivate();

            } else {
                this->virtual_move();
                this->move_figure(c);
                selected->deactivate();
                this->delete_moves();
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
        this->delete_moves();
        selected = nullptr;
        c.deactivate();
    }

    Fl::redraw();
}

void Chessboard::move_figure(Cell &c) {
    if (selected->get_figure().get_type() == pawn) {
        if (selected->get_figure().is_white()) {
            if ((c.number - selected->number == 1 || (selected->number == 2 && c.number - selected->number == 2)) &&
                c.symbol == selected->symbol) {
                if (selected->number == 2 && c.number - selected->number == 2 &&
                    (this->check_move(3, c.symbol) == true)) {
                    return;
                }
                Cell &c1 = *selected;
                c.attach_figure(c1.detach_figure());
            }
        } else {
            if ((c.number - selected->number == -1 || (selected->number == 7 && c.number - selected->number == -2)) &&
                c.symbol == selected->symbol) {
                if (selected->number == 7 && c.number - selected->number == -2 && (this->check_move(6, c.symbol) == true)) {
                    return;
                }
                Cell &c1 = *selected;
                c.attach_figure(c1.detach_figure());
            }
        }
    } else if (selected->get_figure().get_type() == rook) {
        int k = 0;
        if (c.number == selected->number) {
            for (int i = std::min((selected->symbol), c.symbol) + 1; i < std::max(c.symbol, selected->symbol); ++i) {
                if (this->check_move(c.number, i)) { k += 1; }
            }
            if (k == 0 && (c.number == selected->number || c.symbol == selected->symbol)) {
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());
            }
        } else if (c.symbol == selected->symbol) {
            for (int i = std::min(c.number, selected->number) + 1; i < std::max(c.number, selected->number); ++i) {
                if (this->check_move(i, c.symbol)) { k += 1; }
            }
            if (k == 0 && (c.number == selected->number || c.symbol == selected->symbol)) {
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());
            }

        }

    } else if (selected->get_figure().get_type() == knight) {
        if ((abs(c.symbol - selected->symbol) == 1 && abs(c.number - selected->number) == 2) ||
            (abs(c.symbol - selected->symbol) == 2 && abs(c.number - selected->number) == 1)) {
            Cell &c1 = *selected;
            c.eat_figure();
            c.attach_figure(c1.detach_figure());
        }
    } else if (selected->get_figure().get_type() == bishop) {
        int k = 0;
        if (abs(c.symbol - selected->symbol) == abs(c.number - selected->number)) {
            int j = std::min(selected->number, c.number) + 1;
            for (int i = std::min((selected->symbol), c.symbol) + 1; i < std::max(c.symbol, selected->symbol); ++i) {
                if (this->check_move(j, i)) { k += 1; }
                j++;
            }
            if (k == 0 && (abs(c.symbol - selected->symbol) == abs(c.number - selected->number))) {
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());

            }
        }
    } else if (selected->get_figure().get_type() == queen) {
        int k = 0;
        if (c.number == selected->number) {
            for (int i = std::min((selected->symbol), c.symbol) + 1; i < std::max(c.symbol, selected->symbol); ++i) {
                if (this->check_move(c.number, i)) { k += 1; }
            }
            if (k == 0 && (c.number == selected->number || c.symbol == selected->symbol)) {
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());
            }
        } else if (c.symbol == selected->symbol) {
            for (int i = std::min(c.number, selected->number) + 1; i < std::max(c.number, selected->number); ++i) {
                if (this->check_move(i, c.symbol)) { k += 1; }
            }
            if (k == 0 && (c.number == selected->number || c.symbol == selected->symbol)) {
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());
            }

        } else if (abs(c.symbol - selected->symbol) == abs(c.number - selected->number)) {
            int j = std::min(selected->number, c.number) + 1;
            for (int i = std::min((selected->symbol), c.symbol) + 1; i < std::max(c.symbol, selected->symbol); ++i) {
                if (this->check_move(j, i)) { k += 1; }
                ++j;
            }
            if (k == 0 && (abs(c.symbol - selected->symbol) == abs(c.number - selected->number))) {
                Cell &c1 = *selected;
                c.eat_figure();
                c.attach_figure(c1.detach_figure());

            }
        }

    } else if (selected->get_figure().get_type() == king) {
        if ((abs(c.symbol - selected->symbol) == 1 && abs(c.number - selected->number) <= 1) ||
            ((c.symbol == selected->symbol) && abs(c.number - selected->number) == 1)) {
            Cell &c1 = *selected;
            c.eat_figure();
            c.attach_figure(c1.detach_figure());
        }
    }

}

bool Chessboard::check_move(int number, int symbol) {
    char f ='a' + symbol;
    return this->at(f, number).has_figure();
}

void Chessboard::virtual_move_bishop(){
    int i = selected -> number + 1;
        int i_1 = selected -> symbol + 1;
        while (i < 9 && i_1 < 8){
            Cell *c_1 = &this -> at('a' + i_1, i);
            if (!c_1->has_figure()){
                Circle *vm = new Circle({c_1->center().x, c_1->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                ++i;
                ++i_1;
            }else{
                if (c_1 -> get_figure().get_type() != king){
                    if (selected->get_figure().is_white() != c_1 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_1->center().x, c_1->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }

        int j = selected -> number - 1;
        int j_2 = selected -> symbol - 1;
        while (j > 0 && j_2 > -1){
            Cell *c_2 = &this -> at('a' + j_2, j);
            if (!c_2->has_figure()){
                Circle *vm = new Circle({c_2->center().x, c_2->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                --j;
                --j_2;
            }else{
                if (c_2 -> get_figure().get_type() != king){
                    if (selected->get_figure().is_white() != c_2 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_2->center().x, c_2->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }

        int i_plus = selected -> number + 1;
        int j_minus = selected -> symbol - 1;
        while (i_plus < 9 && j_minus > -1){
            Cell *c_3 = &this -> at('a' + j_minus, i_plus);
            if (!c_3->has_figure()){
                Circle *vm = new Circle({c_3->center().x, c_3->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                ++i_plus;
                --j_minus;
            }else{
                if (c_3 -> get_figure().get_type() != king){
                    if (selected->get_figure().is_white() != c_3 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_3->center().x, c_3->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }

        int i_minus = selected -> number - 1;
        int j_plus = selected -> symbol + 1;
        while (i_minus > 0 && j_plus < 8){
            Cell *c_4 = &this -> at('a' + j_plus, i_minus);
            if (!c_4->has_figure()){
                Circle *vm = new Circle({c_4->center().x, c_4->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                --i_minus;
                ++j_plus;
            }else{
                if (c_4 -> get_figure().get_type() != king){
                    if (selected->get_figure().is_white() != c_4 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_4->center().x, c_4->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }

}

void Chessboard::virtual_move_rook(){
    int i = (selected -> number + 1);
        int j = (selected -> number - 1);
        while (i < 9){
            Cell *c_1 = &this -> at('a' + selected -> symbol, i);
            if (!c_1->has_figure()){
                Circle *vm = new Circle({c_1->center().x, c_1->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                ++i;
            }else{
                if (c_1 -> get_figure().get_type() != king){
                    if (selected->get_figure().is_white() != c_1 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_1->center().x, c_1->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }

        while (j > 0){
            Cell *c_2 = &this -> at('a' + selected -> symbol, j);
            if (!c_2->has_figure()){
                Circle *vm = new Circle({c_2->center().x, c_2->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                --j;
            }else{
                if (c_2 -> get_figure().get_type() != king){
                    if (selected->get_figure().is_white() != c_2 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_2->center().x, c_2->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                    break;
                }
            }
        }

        int p = (selected -> symbol + 1);
        int k = (selected -> symbol - 1);

        while (p < 8){
            Cell *c_3 = &this -> at('a' + p, selected -> number);
            if (!c_3->has_figure()){
                Circle *vm = new Circle({c_3->center().x, c_3->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                p++;
            }else{
                if ((c_3 -> get_figure().get_type()) != king){
                    if (selected->get_figure().is_white() != c_3 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_3->center().x, c_3->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }

        while (k > -1){
            Cell *c_4 = &this -> at('a' + k, selected -> number);
            if (!c_4->has_figure()){
                Circle *vm = new Circle({c_4->center().x, c_4->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                k--;
            }else{
                if ((c_4 -> get_figure().get_type()) != king){
                    if (selected->get_figure().is_white() != c_4 ->get_figure().is_white()){
                        Circle *vm = new Circle({c_4->center().x, c_4->center().y}, 20);
                        vm->set_fill_color(FL_DARK_GREEN);
                        this->green_circles.push_back(vm);
                        this->attach(*vm);
                    }
                }
                break;
            }
        }
}

void Chessboard::virtual_move_king(){
    
}

void Chessboard::virtual_move() {
    if (selected->get_figure().get_type() == pawn) {
        if (selected->get_figure().is_white()) {
            Cell *c = &this->at('a' + selected->symbol, selected->number + 1);
            if (!c->has_figure()) {
                Circle *vm = new Circle({c->center().x, c->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                Cell *cs = &this->at('a' + selected->symbol, selected->number + 2);
                if (selected->number == 2 && !cs->has_figure()) {
                    Circle *vm2 = new Circle({cs->center().x, cs->center().y}, 20);
                    vm2->set_fill_color(FL_DARK_GREEN);
                    this->green_circles.push_back(vm2);
                    this->attach(*vm2);
                }
            }
        } else {
            Cell *c = &this->at('a' + selected->symbol, selected->number - 1);
            if (!c->has_figure()) {
                Circle *vm = new Circle({c->center().x, c->center().y}, 20);
                vm->set_fill_color(FL_DARK_GREEN);
                this->green_circles.push_back(vm);
                this->attach(*vm);
                Cell *cs = &this->at('a' + selected->symbol, selected->number - 2);
                if (selected->number == 7 && !cs->has_figure()) {
                    Circle *vm2 = new Circle({cs->center().x, cs->center().y}, 20);
                    vm2->set_fill_color(FL_DARK_GREEN);
                    this->green_circles.push_back(vm2);
                    this->attach(*vm2);
                }
            }
        }
    }
    if (selected -> get_figure().get_type() == rook){
        virtual_move_rook();
    }

    if (selected -> get_figure().get_type() == bishop){
        virtual_move_bishop();
    }

    if (selected -> get_figure().get_type() == queen){
        virtual_move_rook();
        virtual_move_bishop();
    }

    if (selected -> get_figure().get_type() == king){
        virtual_move_king();
    }

}

void Chessboard::delete_moves() {
    if (this->green_circles.size()) {
        for (int i = 0; i < int(this->green_circles.size()); i++){
            this->green_circles[i]->set_fill_color(Color::invisible);
            this->green_circles[i]->set_color(Color::invisible);
        }
        this->green_circles.clear();
    }
}