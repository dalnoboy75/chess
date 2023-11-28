#include <exception>
#include <iostream>

#include "board.h"
#include "cell.h"
#include "figures.h"
using namespace Graph_lib;


int ex_chessboard ()
{
  Chessboard board{Point{100, 100}};
  Pawn p(board,"pieces.png",white_pawn,true);
  board.at('b',2).attach_figure(p);
  board.wait_for_button();
  return 0;
  // return gui_main();
}

int main ()
try
{
  //  ex_my_window();
  ex_chessboard();
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
