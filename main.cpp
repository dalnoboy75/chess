#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <bits/stdc++.h>
using namespace std;
using namespace Graph_lib;

class MyCanvas : public Shape
{
protected:
    void draw_lines () const override { fl_line(0, 0, 200, 200); }
};

class MyArc : public Ellipse
{
public:
    MyArc(Point p, int ww, int hh, int alpha, int beta)
            : Ellipse(p, ww, hh), phi1{alpha}, phi2{beta} {};

protected:
    void draw_lines () const override
    {
        int w = major(), h = minor();
        if (fill_color().visibility())
        {
            fl_color(fill_color().as_int());
            fl_pie(point(0).x, point(0).y, 2 * w - 1, 2 * h - 1, phi1, phi2);
        }
        fl_color(color().as_int());
        if (color().visibility())  // проверяем видимость границы
        {
            fl_arc(point(0).x, point(0).y, 2 * w, 2 * h, phi1, phi2);
        }
    }

private:
    int phi1, phi2;
};

struct Regular_hexagon : Shape
{
    Regular_hexagon(Point c, int r);
    Point center () const;
    int width () const;
    int height () const;
    int edge () const;

protected:
    void draw_lines () const override;
};

Regular_hexagon::Regular_hexagon(Point c, int r)
{
    constexpr int n = 6;  // number of vertices
    for (int i = 0; i < n; ++i)
    {
        Point p;
        double phi = 2 * pi * i / n;
        p.x = c.x + round(r * cos(phi));
        p.y = c.y + round(r * sin(phi));
        add(p);
    };
}

Point Regular_hexagon::center() const
{
    return {(point(0).x + point(3).x) / 2, point(0).y};
}

int Regular_hexagon::width() const { return point(0).x - point(3).x; }

int Regular_hexagon::height() const { return point(1).y - point(5).y; }

int Regular_hexagon::edge() const { return point(1).x - point(2).x; }

void Regular_hexagon::draw_lines() const
{
    if (fill_color().visibility())
    {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i)
        {
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());  // reset color
        if (color().visibility())
            Shape::draw_lines();
        // draw closing line
        fl_line(point(number_of_points() - 1).x,
                point(number_of_points() - 1).y, point(0).x, point(0).y);
    }
}

struct Hexagon_tile : Rectangle
{
    Hexagon_tile(Point p, int ww, int hh, int rr);
    void move (int dx, int dy) override;

protected:
    void draw_lines () const override;

private:
    Vector_ref<Regular_hexagon> tile;
};

Hexagon_tile::Hexagon_tile(Point p, int ww, int hh, int rr)
        : Rectangle{p, ww, hh}
{
    std::array<Color, 3> colors{Color::dark_cyan, Color::dark_magenta,
                                Color::dark_yellow};
    Regular_hexagon h{Point{0, 0}, rr};
    const int x_max = point(0).x + width() - h.width() / 2;
    const int y_max = point(0).y + height() - h.height() / 2;
    const int dx = h.width() + h.edge();
    const int dy = h.height() / 2;
    int y = point(0).y + dy;
    for (int i = 0; y <= y_max; ++i, y += dy)
    {
        int x = point(0).x + h.width() / 2;
        if (i % 2)
            x += dx / 2;
        for (; x <= x_max; x += dx)
        {
            tile.push_back(new Regular_hexagon{Point{x, y}, rr});
            tile[tile.size() - 1].set_fill_color(colors[i % colors.size()]);
        }
    }
    set_color(Color::invisible);
}

void Hexagon_tile::move(int dx, int dy)
{
    Rectangle::move(dx, dy);
    for (int i = 0; i < tile.size(); ++i)
        tile[i].move(dx, dy);
}

void Hexagon_tile::draw_lines() const
{
    Rectangle::draw_lines();
    for (int i = 0; i < tile.size(); ++i)
        tile[i].draw();
}

int main ()

{
    Simple_window win{Point{100, 100}, 600, 600, "window"};

    // Vector_ref<MyArc> arcs;
    // arcs.push_back(new MyArc{Point{300, 300}, 20, 20, 180, 360});
    // arcs.push_back(new MyArc{Point{280, 300}, 40, 40, 0, 90});
    // arcs.push_back(new MyArc{Point{280, 320}, 60, 60, 90, 180});
    // arcs.push_back(new MyArc{Point{320, 320}, 100, 100, 180, 270});
    // arcs.push_back(new MyArc{Point{320, 260}, 160, 160, 270, 360});
    // for (int i = 0; i < arcs.size(); i++)
    //{
    // win.attach(arcs[i]);
    //}
    Hexagon_tile ht{Point{50, 50}, 300, 300, 20};
    win.attach(ht);
    win.wait_for_button();
}
