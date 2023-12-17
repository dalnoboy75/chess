#ifndef BOARD_H
#define BOARD_H

#include "figures.h"
#include "cell.h"

using Graph_lib::Address;
using Graph_lib::Point;

struct My_window : Simple_window {
    My_window(Point xy, int w, int h, const std::string &title)
            : Simple_window{xy, w, h, title},
              quit_button{Point{x_max() - 70, 20}, 70, 20, "Quit", cb_quit} {
        attach(quit_button);
    }

    Graph_lib::Button quit_button;

private:
    static void cb_quit(Address, Address widget) {
        auto &btn = Graph_lib::reference_to<Graph_lib::Button>(widget);
        dynamic_cast<My_window &>(btn.window()).quit();
    }

    void quit() { hide(); }
};

struct Chessboard : Graph_lib::Window {
    Chessboard(Point xy);

    static constexpr int N = 8;  // board N by N
    static constexpr int N_max = 8;
    int step_cnt = 0;

    static_assert(N <= N_max,
                  "do not allow board larger than N_max by N_max");

    Cell &at(char c, int i) {
        i--;
        int j = c - 'a';
        return cells[i * N + j];
    }


    bool check_move(int number, int symbol);

private:
    bool which_move = true;
    static constexpr int margin = 30;
    static constexpr int width = N * Cell::size + 2 * margin;
    static constexpr int height = N * Cell::size + 2 * margin;
    vector<Graph_lib::Circle *> green_circles;
    Graph_lib::Vector_ref<Cell> cells;
    Graph_lib::Marks x_labels;
    Graph_lib::Marks y_labels;

    Cell *selected{nullptr};  // activated cell

    static void cb_clicked(Address, Address widget) {
        auto &btn = Graph_lib::reference_to<Cell>(widget);
        dynamic_cast<Chessboard &>(btn.window()).clicked(btn);
    }
    int is_check(bool color); // true - белый, false - черный

    void virtual_move();

    void delete_moves();

    void clicked(Cell &c);

    void move_figure(Cell &c);

    void virtual_move_rook();

    void virtual_move_bishop();

    void virtual_move_king();

    void virtual_move_knight();

    void draw_check_inf();
    void game_over();
    void all_pawns_no_big_step();
};

#endif  // #ifndef BOARD_H
