#include "cachedpiece.h"

CachedPiece::CachedPiece(int number) : pos(0), last(-1)
{
  set(number);
}

void CachedPiece::reset()
{
  map = permutations[pos = 0][rotation = 0];
}

void CachedPiece::set(int number)
{
  if(number != last)
  {
    last = number;
    permutations.clear();
    Piece::set(number);
    do
    {
      rot_array rotset;
      do
        rotset[rotation] = map;
      while(Piece::rotate());
      permutations.push_back(rotset);
    }
    while(Piece::next());
  }
  reset();
}

bool CachedPiece::next()
{
  if(++pos < permutations.size())
  {
    map = permutations[pos][rotation];
    return true;
  }
  return false;
}

bool CachedPiece::rotate()
{
  if(rotation < last_rotation)
  {
    map = permutations[pos][++rotation];
    return true;
  }
  map = permutations[pos][rotation = 0];
  return false;
}

std::ostream& CachedPiece::simpleprint(std::ostream& out) const
{
  return out << last << "," << pos << "," << rotation;
}
