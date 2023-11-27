#include "cell.h"
#include "figures.h"
using namespace Graph_lib;

Cell::Cell(Point xy, Callback cb, Type t)
    : Button{xy, size, size, "", cb}, type{t}
{
  /* All done */
}

void Cell::attach(Graph_lib::Window& win)
{
  Button::attach(win);
  reset_color();
}

void Cell::reset_color()
{
  if (!pw)
    error("Cell is not attached to a window");

  if (is_black())
    pw->color(Color::black);
  else
    pw->color(Color::white);
}

void Cell::attach_figure(Figure& f)
{
  f.attach(*this);
  figure = &f;
}

Figure& Cell::detach_figure()
{
  Figure* f = figure;
  figure = nullptr;
  f->detach();
  return *f;
}

Figure& Cell::get_figure() { return *figure; }
