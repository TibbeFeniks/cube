#include "piece.h"


constexpr Piece::bits Piece::all[Piece::max_piece];
constexpr int Piece::cycle_rotations[Piece::max_rotations];

Piece::Piece(int number) : rotation(0)
{
  set(number);
}

void Piece::set(int number)
{
  number = number % max_piece;
  if(number >= 0 and number < max_piece)
    map = all[number];
  else
    map = 0;
}

bool Piece::next()
{
  if(map & max_x)
    if(map & max_y)
      if(map & max_z)
        return false;
      else
        do
          map <<= movx;
        while(map & (max_y | max_x));
    else
      do
        map <<= movx;
      while(map & max_x);
  else
    map <<= movx;
  return true;
}

bool Piece::rotate()
{
  switch(cycle_rotations[rotation])
  {
    case 1:
      rotatez();
      break;
    case 2:
      rotatex();
      break;
    case 3:
      rotatey();
      rotatey();
      break;
  }
  if(rotation == last_rotation)
  {
    rotation = 0;
    return false;
  }
  ++rotation;
  return true;
}

