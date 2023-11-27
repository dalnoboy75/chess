#include "checker.h"

#include "cell.h"
using namespace Graph_lib;

void Checker::attach(const Cell& c)
{
  move(c.center().x - center().x, c.center().y - center().y);
  cell = &c;
}