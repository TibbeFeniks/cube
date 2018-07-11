#include<cstdint>

class Coord
{
  using bits = uint8_t;
  static const bits mapmask = 0x3fU;
  static const bits splitmask = 0x3U;
  static const int splitwidth = 2;

  bits map;
 public:
  Coord(int x, int y, int z) : map(((x & splitmask) + (y & splitmask) << splitwidth + (z & splitmask) << (2 * splitwidth))) {}

  int getx() const {return map & splitmask;}
  int gety() const {return (map >> splitwidth) & splitmask;}
  int getz() const {return map >> (2 * splitwidth);}
  int getnumber() const {return map;}
  void rotatez()
  {
    map = map ^ ((((map << splitwidth) ^ map) & (splitmask << splitwidth)) | (((~map >> splitwidth) ^ map) & splitmask));
  }
  void rotatey()
  {
    map = map ^ ((((map << (2 * splitwidth)) ^ map) & (splitmask << (2 * splitwidth))) | (((~map >> (2 * splitwidth) ^ map) & splitmask));
  }
  void rotatex()
  {
    bits temp = map >> splitwidth;
    temp = temp ^ ((((temp << splitwidth) ^ temp) & (splitmask << splitwidth)) | (((~temp >> splitwidth) ^ temp) & splitmask));
    map = (temp << splitwidth) | (map & splitmask);
  }
  bool next() {return ++map;}

  bool operator<(Coord const& other) const {return map < other.map;}
};

class Block
{
  using coords = uint64_t;
  
  static const coords xaxis = 0x1U;
  static const coords yaxis = 0x4U;
  static const coords zaxis = 0x10U;

  coords components;

  Block(int seed)
  {
    components = construct(seed);
  }

  void add(Coord in)
  {
    components |= 1 << Coord.getnumber();
  }

  void rotate(int dir)
  {
    switch(dir){
      case 0:
	break;
      case 1:
	break;
      case 2:
    }
  }

  friend std::ostream& operator<<(std::ostream& out, Block const& in)
  {
    coords components = in.components;
    for(coord i = 0; components > 0; ++i)
    {
      if(i % yaxis == 0)
        out << std::newl;
      if(i % zaxis == 0)
        out << "----" << std::newl;
      if(components & xaxis == 0)
        out << ' ';
      else
        out << 'X';
      components >> 1;
    }
    out << std::newl;
    return out;
  }
};

int main()
{
  
}

