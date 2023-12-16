#include "figures.h"
#include "cell.h"

using namespace Graph_lib;

void Figure::attach(const Cell &c) {
    move(c.center().x - (point(0).x + size/2), c.center().y - (point(0).y + size/2));
    cell = &c;
}

