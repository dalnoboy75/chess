#include "figures.h"
#include "cell.h"
using namespace Graph_lib;

void Figure::attach(const Cell& c){
    move(c.center().x - x, c.center().y - y);
    x += c.center().x - x;
    y += c.center().y - y;
    cell = &c;
}