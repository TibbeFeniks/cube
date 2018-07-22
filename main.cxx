#include "common.h"
#include "cube.h"
#include "piece.h"
#include "cachedpiece.h"


int place(Cube const& start, CachedPiece* pieces, time_t const time)
{
  int solutions = 0;
  int piece_nr = 1;
  Cube total = start;
  while(true)
  {
    if(total.merge(pieces[piece_nr])) //try fitting piece
    {
      //std::cout << "placed piece " << piece_nr << ":\n" << total << std::endl;
      if(piece_nr != last_piece) //there is more pieces
      {
        ++piece_nr; //piece fits, go to next piece
        continue;
      }
      std::cout << "solution " << ++solutions << " found at ";
      get_time(std::cout, time) << ":" << std::endl;
      for(int i = 0; i < max_piece; ++i)
        std::cout << pieces[i] << std::endl;
        //pieces[i].simpleprint(std::cout) << (i == last_piece ? "\n" : " ");
      total.remove(pieces[piece_nr]);
    }
    while(not pieces[piece_nr].rotate() && //try rotating piece
      not pieces[piece_nr].next()) //rotated full circle, move piece instead
    {
      pieces[piece_nr].reset(); //reinitialize piece
      if(piece_nr == 1)
        return solutions; //tried all pieces
      total.remove(pieces[--piece_nr]); //all permutations tried, remove previous
      //std::cout << piece_nr + 1 << " doesn't fit, removing " << piece_nr << ":\n" << pieces[piece_nr] << std::endl;
    }
  }
}

int main()
{
  time_t start;
  int solutions = 0;
  time(&start);//measure starting time
  CachedPiece pieces[max_piece];
  for(int i = 0; i < max_piece; ++i)
    pieces[i].set(i);
  do
    solutions += place(pieces[0], pieces, start);//place all pieces starting with first piece
  while(pieces[0].next());//only move first piece, never rotate it
  std::cout << "done at: ";
  get_time(std::cout, start) << std::endl;
  if(solutions) //solved
    std::cout << "found " << solutions << " solutions" << std::endl;
  else //not solved
    std::cout << "unsolvable" << std::endl;
}

