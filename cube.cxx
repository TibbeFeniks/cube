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
  map = ((map & zrot[0]) << movxx) | ((map & zrot[1]) << movyy) |
    ((map & zrot[2]) >> movyy) | ((map & zrot[3]) >> movxx);
  map = ((map & zrot[4]) << movx) | ((map & zrot[5]) << movy) |
    ((map & zrot[6]) >> movy) | ((map & zrot[7]) >> movx);
}

void Cube::rotatex()
{
  map = ((map & xrot[0]) << movyy) | ((map & xrot[1]) << movzz) |
    ((map & xrot[2]) >> movzz) | ((map & xrot[3]) >> movyy);
  map = ((map & xrot[4]) << movy) | ((map & xrot[5]) << movz) |
    ((map & xrot[6]) >> movz) | ((map & xrot[7]) >> movy);
}

void Cube::rotatey()
{
  map = ((map & yrot[0]) << movxx) | ((map & yrot[1]) << movzz) |
    ((map & yrot[2]) >> movzz) | ((map & yrot[3]) >> movxx);
  map = ((map & yrot[4]) << movx) | ((map & yrot[5]) << movz) |
    ((map & yrot[6]) >> movz) | ((map & yrot[7]) >> movx);
}

void Cube::rotatezz()
{
  map = ((map & ysplit[0]) << movyy) | ((map & ysplit[1]) >> movyy);
  map = ((map & xsplit[0]) << movxx) | ((map & xsplit[1]) >> movxx);
  map = ((map & ysplit[2]) << movy) | ((map & ysplit[3]) >> movy);
  map = ((map & xsplit[2]) << movx) | ((map & xsplit[3]) >> movx);
}

void Cube::rotatexx()
{
  map = ((map & zsplit[0]) << movzz) | ((map & zsplit[1]) >> movzz);
  map = ((map & ysplit[0]) << movyy) | ((map & ysplit[1]) >> movyy);
  map = ((map & zsplit[2]) << movz) | ((map & zsplit[3]) >> movz);
  map = ((map & ysplit[2]) << movy) | ((map & ysplit[3]) >> movy);
}

void Cube::rotateyy()
{
  map = ((map & zsplit[0]) << movzz) | ((map & zsplit[1]) >> movzz);
  map = ((map & xsplit[0]) << movxx) | ((map & xsplit[1]) >> movxx);
  map = ((map & zsplit[2]) << movz) | ((map & zsplit[3]) >> movz);
  map = ((map & xsplit[2]) << movx) | ((map & xsplit[3]) >> movx);
}

std::ostream& operator<<(std::ostream& out, Cube const& self)
{
  out << "cube(" << self.count() << " bits):";
#if 0
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
#else
  for(Cube::bits i = Cube::max_y; i; i >>= Cube::movy)
    for(Cube::bits j = i & Cube::max_z; i & j; j >>= Cube::movz)
    {
      out << (j & Cube::max_z ? "\n" : "|");
      for(Cube::bits k = j & Cube::max_x; j & k; k >>= Cube::movx)
        out << (k & self.map ? 'X' : 'O');
    }
#endif
  return out;
}

