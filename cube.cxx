#include <ctime>
#include "cube.h"


//Cube
int Cube::count() const
{
  int c = 0;
  for(bits i = map; i; i &= i - 1)
    ++c;
  return c;
}

bool Cube::merge(Cube const& other)
{
  if(map & other.map)
    return false;
  map |= other.map;
  return true;
}

bool Cube::remove(Cube const& other)
{
  if(~map & other.map)
    return false;
  map ^= other.map;
  return true;
}

void Cube::rotatez()
{
  map = ((map & zrot[0]) << (movx * 2)) | ((map & zrot[1]) << (movy * 2)) |
    ((map & zrot[2]) >> (movy * 2)) | ((map & zrot[3]) >> (movx * 2));//optimizable
  map = ((map & zrot[4]) << movx) | ((map & zrot[5]) << movy) |
    ((map & zrot[6]) >> movy) | ((map & zrot[7]) >> movx);
}

void Cube::rotatex()
{
  map = ((map & xrot[0]) << (movy * 2)) | ((map & xrot[1]) << (movz * 2)) |
    ((map & xrot[2]) >> (movz * 2)) | ((map & xrot[3]) >> (movy * 2));
  map = ((map & xrot[4]) << movy) | ((map & xrot[5]) << movz) |
    ((map & xrot[6]) >> movz) | ((map & xrot[7]) >> movy);
}

void Cube::rotatey()
{
  map = ((map & yrot[0]) << (movx * 2)) | ((map & yrot[1]) << (movz * 2)) |
    ((map & yrot[2]) >> (movz * 2)) | ((map & yrot[3]) >> (movx * 2));
  map = ((map & yrot[4]) << movx) | ((map & yrot[5]) << movz) |
    ((map & yrot[6]) >> movz) | ((map & yrot[7]) >> movx);
}

std::ostream& operator<<(std::ostream& out, Cube const& self)
{
  for(Piece::bits i = self.max_bit; i; i = i >> 1)
  {
    if(i & self.max_x)
      if(i & self.max_y)
        if(i & self.max_z)
          out << "cube(" << self.count() << " bits):\n";
        else
          out << "\n----\n";
      else
        out << '\n';
    out << ((i & self.map) ? 'X' : 'O');
  }
  out << std::endl;
  return out;
}


//Piece
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
  int n = cycle_rotations[rotation];
  switch(n)
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
  if(rotation == max_rotations - 1)
  {
    rotation = 0;
    return false;
  }
  ++rotation;
  return true;
}

constexpr Piece::bits Piece::all[Piece::max_piece];
constexpr int Piece::cycle_rotations[Piece::max_rotations];


//Main
int main()
{
  const int max_piece = 13;
  time_t start;
  time_t end;
  time(&start);
  std::cout << start << std::endl;
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
  return 0;
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
  if(piece_nr == max_piece - 1) //all pieces fit
  {
    std::cout << "solution found:" << std::endl;
    for(int i = 0; i < max_piece; ++i)
      std::cout << pieces[i] << std::endl;
  }
  else
    std::cout << "unsolvable" << std::endl;
  time(&end);
  std:: cout << difftime(start, end) / 60.0 << std::endl;
}

