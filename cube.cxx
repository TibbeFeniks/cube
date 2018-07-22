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
  map = ((map & zrot[0]) << (movxx)) | ((map & zrot[1]) << (movyy)) |
    ((map & zrot[2]) >> (movyy)) | ((map & zrot[3]) >> (movxx));
  map = ((map & zrot[4]) << movx) | ((map & zrot[5]) << movy) |
    ((map & zrot[6]) >> movy) | ((map & zrot[7]) >> movx);
}

void Cube::rotatex()
{
  map = ((map & xrot[0]) << (movyy)) | ((map & xrot[1]) << (movzz)) |
    ((map & xrot[2]) >> (movzz)) | ((map & xrot[3]) >> (movyy));
  map = ((map & xrot[4]) << movy) | ((map & xrot[5]) << movz) |
    ((map & xrot[6]) >> movz) | ((map & xrot[7]) >> movy);
}

void Cube::rotatey()
{
  map = ((map & yrot[0]) << (movxx)) | ((map & yrot[1]) << (movzz)) |
    ((map & yrot[2]) >> (movzz)) | ((map & yrot[3]) >> (movxx));
  map = ((map & yrot[4]) << movx) | ((map & yrot[5]) << movz) |
    ((map & yrot[6]) >> movz) | ((map & yrot[7]) >> movx);
}

std::ostream& operator<<(std::ostream& out, Cube const& self)
{
  out << "cube(" << self.count() << " bits):";
  for(Cube::bits i = self.max_bit; i; i = i >> 1)
  {
    if(i & self.max_x)
    {
      if(i & self.max_y & ~self.max_z)
        out << "\n----";
      out << '\n';
    }
    out << ((i & self.map) ? 'X' : 'O');
  }
  out << std::endl;
  return out;
}

