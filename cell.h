#ifndef CELL_H
#define CELL_H 1

#include <Graph_lib/Simple_window.h>

using Graph_lib::Point;

struct Checker;

struct Cell : Graph_lib::Button
{
  enum Type
  {
    black,
    white
  };

  Cell(Point xy, Graph_lib::Callback cb, Type t);

  void attach (Graph_lib::Window& win) override;

  void activate ()
  {
    if (pw)
      pw->color(FL_SELECTION_COLOR);
  }

  void deactivate () { reset_color(); }

  bool is_black () const { return type == black; }

  Point center () const
  {
    return Point{loc.x + width / 2, loc.y + height / 2};
  }

  void attach_checker (Checker& ch);

  Checker& detach_checker ();

  bool has_checker() const{
    return checker != nullptr;
  }

  Checker& get_checker();

  static constexpr int size = 90;

private:
  Type type;

  void reset_color ();

  Checker* checker{nullptr};
};


#endif  // #ifndef CELL_H
