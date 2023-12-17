#ifndef CELL_H
#define CELL_H 1

#include <Graph_lib/Simple_window.h>

using Graph_lib::Point;

struct Figure;

struct Cell : Graph_lib::Button {
    enum Type {
        black,
        white
    };
    int number;
    int symbol;

    Cell(Point xy, Graph_lib::Callback cb, Type t, int number, int symbol);

    void attach(Graph_lib::Window &win) override;

    void activate() {
        if (pw)
            pw->color(101);
    }


    void deactivate() { reset_color(); }

    bool is_black() const { return type == black; }

    Point center() const {
        return Point{loc.x + width / 2, loc.y + height / 2};
    }

    void eat_figure();

    void attach_figure(Figure &f);

    Figure &detach_figure();

    bool has_figure() const {
        return figure != nullptr; 
    }

    Figure &get_figure();
    Figure* get_figure_ptr(){
        return figure;
    }
    static constexpr int size = 90;
private:
    Type type;

    void reset_color();

    Figure *figure{nullptr};

};


#endif  // #ifndef CELL_H
