#include "cube.h"


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
  for(Cube::bits i = self.max_bit; i; i = i >> 1)
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

