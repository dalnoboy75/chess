#include <exception>
#include <iostream>

#include "board.h"
#include "figures.h"
using namespace Graph_lib;


int ex_chessboard ()
{
  Chessboard board{Point{100, 100}};
  for(int i = 0; i < 8; i++){
      Pawn* pw = new Pawn(board,"pieces.png",white_pawn,true);
      char m = 'a'+i;
      board.at(m,2).attach_figure(*pw);
      Pawn* pb = new Pawn(board, "pieces.png", black_pawn,false);
      board.at(m, 7).attach_figure(*pb);
  }
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
  std::cout << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
