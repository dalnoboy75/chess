#include "cell.h"
#include "checker.h"
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

void Cell::attach_checker(Checker& ch)
{
  ch.attach(*this);
  checker = &ch;
}

Checker& Cell::detach_checker()
{
  Checker* ch = checker;
  checker = nullptr;
  ch->detach();
  return *ch;
}

Checker& Cell::get_checker() { return *checker; }
