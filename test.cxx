#include "common.h"
#include "cube.h"
#include "piece.h"
#include "cachedpiece.h"


int main()
{
  CachedPiece p = CachedPiece(0);
  int c = 0;
  for(int i = 0; i < max_piece; p.set(++i))
    do
      do
        p.simpleprint(std::cout << "piece ") << " nr " << c++ << ":\n" << p << std::endl;
      while(p.rotate());
    while(p.next());
  std::cout << "total: " << c << std::endl;
}

