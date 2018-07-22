#include<thread>
#include "common.h"
#include "cube.h"
#include "piece.h"
#include "cachedpiece.h"

const unsigned int __max_thread = std::thread::hardware_concurrency();//can return 0
const unsigned int max_thread = __max_thread > 1 ? __max_thread : 1;
const unsigned int last_thread = max_thread - 1;

void place(Piece const start, time_t const time, int& solutions)
{
  static const int max_piece = last_piece;
  static const int last_piece = max_piece - 1;
#if SIMPLEPRINT
  int startcount = 26;//count the remaining nexts in the 27 moves of piece 0
  {
    Piece p = start;
    while(p.next())
      --startcount;
  }
#endif
  CachedPiece pieces[max_piece];//all REMAINING pieces after the first
  for(int i = 0; i < max_piece; ++i)
    pieces[i].set(i + 1);
  int piece_nr = 0;
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
      ++solutions;
      std::cout << "solution found at ";
      get_time(std::cout, time) << ":" << std::endl;
#if SIMPLEPRINT
      std::cout << "0," << startcount << ",0 ";
#else
      std::cout << start << std::endl;
#endif
      for(int i = 0; i < max_piece; ++i)
#if SIMPLEPRINT
        pieces[i].simpleprint(std::cout) << (i == last_piece ? "\n" : " ");
#else
        std::cout << pieces[i] << std::endl;
#endif
      total.remove(pieces[piece_nr]);
    }
    while(not pieces[piece_nr].rotate() && //try rotating piece
      not pieces[piece_nr].next()) //rotated full circle, move piece instead
    {
      if(piece_nr == 0)
        return; //tried all pieces
      pieces[piece_nr].reset(); //reinitialize piece
      total.remove(pieces[--piece_nr]); //all permutations tried, remove previous
      //std::cout << piece_nr + 1 << " doesn't fit, removing " << piece_nr << ":\n" << pieces[piece_nr] << std::endl;
    }
  }
}

int main()
{
  int solutions = 0;
  time_t start;
  time(&start);//measure starting time
  Piece first_piece(0);
  std::thread threads[max_thread];
  bool used_threads[max_thread];
  bool next = true;
  int joins = 0;
  for(unsigned int i = 0; next || joins; i == last_thread ? i = 0 : ++i)
  {
    if(used_threads[i] && joins--)
      threads[i].join();//note: this waits for threads sequentially
    if(next)
    {
      threads[i] = std::thread(place, first_piece, start, std::ref(solutions));
      used_threads[i] = true;
      ++joins;
      next = first_piece.next();
    }
  }
  std::cout << "done at: ";
  get_time(std::cout, start) << std::endl;
  if(solutions) //solved
    std::cout << "found " << solutions << " solutions" << std::endl;
  else //not solved
    std::cout << "unsolvable" << std::endl;
}

