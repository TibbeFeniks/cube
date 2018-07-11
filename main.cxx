#include "piece.cxx"
#include <ctime>

int main()
{
  const int max_piece = 13;
  time_t start;
  time_t end;
  time(&start);//measure starting time
#if 0
  Piece p = Piece(0);
  int c = 0;
  for(int i = 0; i < max_piece; p.set(++i))
    do
      do
        std::cout << "piece " << i << " nr " << c++ << std::endl;
      while(p.rotate());
    while(p.next());
  std::cout << "total: " << c << std::endl;
#endif
  Cube total;
  Piece pieces[max_piece];
  for(int i = 0; i < max_piece; ++i)
    pieces[i].set(i);
  int piece_nr = 1;
  bool merge = true;
  do
  {
    total = pieces[0];
    while(true)
    {
      if(merge && total.merge(pieces[piece_nr])) //try fitting piece
      {
        //std::cout << piece_nr << ":\n" << total << std::endl;
        if(piece_nr >= max_piece - 1)
          break; //fit the last piece
        ++piece_nr; //piece fits, go to next piece
      }
      else if(not pieces[piece_nr].rotate()) //try rotating piece
        if(not pieces[piece_nr].next()) //rotated full circle, move piece instead
        {
          if(piece_nr <= 1)
            break; //tried all pieces
          pieces[piece_nr].set(piece_nr); //reinitialize piece
          total.remove(pieces[--piece_nr]); //all permutations tried, go back and remove previous
          merge = false;
          //std::cout << piece_nr + 1 << " doesn't fit, removing " << piece_nr << ":\n" << pieces[piece_nr] << std::endl;
          continue;
        }
      merge = true;
    }
    if(piece_nr >= max_piece - 1)
      break; //done
  }
  while(pieces[0].next());
  time(&end);//measure time when the calculation is done
  if(piece_nr == max_piece - 1) //all pieces fit
  {
    std::cout << "solution found:" << std::endl;
    for(int i = 0; i < max_piece; ++i)
      std::cout << pieces[i] << std::endl;
  }
  else
    std::cout << "unsolvable" << std::endl;
  int seconds = difftime(end, start);//subtract start from end and return seconds
  int mins = seconds / 60;
  seconds %= 60;
  int hours = mins / 60;
  mins %= 60;
  std::cout << "total time: " << hours << 'h' << mins << 'm' << seconds << 's' << std::endl;
}

