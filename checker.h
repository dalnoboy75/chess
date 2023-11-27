#pragma once
#include <Graph_lib/Point.h>
#include <Graph_lib/Simple_window.h>
#include "cell.h"
using namespace Graph_lib;
struct Checker : Graph_lib::Circle
{
  Checker(Graph_lib::Window& win) : Circle{Point{0, 0}, r}
  {
    win.attach(*this);
  }

  void draw_lines () const override { Circle::draw_lines(); }

  virtual bool is_black () = 0;

  void attach (const Cell& c);
  void detach(){
    cell = nullptr;
  }
private:
  static constexpr int r = 0.9 * Cell::size / 2;
  const Cell* cell{nullptr};
};

struct WhiteChecker : Checker
{
  WhiteChecker(Graph_lib::Window& win) : Checker(win)
  {
    set_fill_color(Graph_lib::Color{17});
  }

  bool is_black () override { return false; }
};

struct BlackChecker : Checker
{
  BlackChecker(Graph_lib::Window& win) : Checker(win)
  {
    set_fill_color(Graph_lib::Color{30});
  }

  bool is_black () override { return true; }
};