#pragma once
#include<cstdint>
#include<iostream>


class Cube
{
public:
  using bits = uint64_t;
protected:
  static constexpr bits max_bit = 0x8000000000000000;
  static constexpr bits max_x = 0x8888888888888888;
  static constexpr bits max_y = 0xf000f000f000f000;
  static constexpr bits max_z = 0xffff000000000000;
  static constexpr int movx = 1;
  static constexpr int movy = 4;
  static constexpr int movz = 16;
  static constexpr int movxx = movx * 2;
  static constexpr int movyy = movy * 2;
  static constexpr int movzz = movz * 2;
  static constexpr bits zrot[8] = {
    0x33003300330033, 0xcc00cc00cc00cc, 0x3300330033003300, 0xcc00cc00cc00cc00,
    0x505050505050505, 0xa0a0a0a0a0a0a0a, 0x5050505050505050, 0xa0a0a0a0a0a0a0a0};
  static constexpr bits xrot[8] = {
    0xff00ff, 0xff00ff00, 0xff00ff00000000, 0xff00ff0000000000,
    0xf0f00000f0f, 0xf0f00000f0f0, 0xf0f00000f0f0000, 0xf0f00000f0f00000};
  static constexpr bits yrot[8] = {
    0x33333333, 0xcccccccc, 0x3333333300000000, 0xcccccccc00000000,
    0x555500005555, 0xaaaa0000aaaa, 0x5555000055550000, 0xaaaa0000aaaa0000};
  static constexpr bits xsplit[4] = {
    0x3333333333333333, 0xcccccccccccccccc, 0x5555555555555555, 0xaaaaaaaaaaaaaaaa};
  static constexpr bits ysplit[4] = {
    0xff00ff00ff00ff, 0xff00ff00ff00ff00, 0xf0f0f0f0f0f0f0f, 0xf0f0f0f0f0f0f0f0};
  static constexpr bits zsplit[4] = {
    0xffffffff, 0xffffffff00000000, 0xffff0000ffff, 0xffff0000ffff0000};

  bits map;

public:
  //create empty cube
  Cube() : map(0) {}

  //create cube from bits origin
  Cube(bits origin) : map(origin) {}

  //count the amount of bits set
  int count() const;

  //when this cube and other do not overlap add other to this, otherwise return false
  bool merge(Cube const& other);

  //when this cube and other do overlap remove other from this, otherwise return false
  bool remove(Cube const& other);

  //shift cube on axis
  void shiftx() {map <<= movx;}
  void shifty() {map <<= movy;}
  void shiftz() {map <<= movz;}

  //shift cube on axis by amount
  void shiftx(int amount) {map <<= (movx * amount);}
  void shifty(int amount) {map <<= (movy * amount);}
  void shiftz(int amount) {map <<= (movz * amount);}

  //when no bits would flow over the sides of cube shift cube on axis, otherwise return false
  //also returns false if cube == 0 as there are no bits that were moved anyway
  bool try_shiftx() {return map & max_x ? false : map <<= movx;}
  bool try_shifty() {return map & max_y ? false : map <<= movy;}
  bool try_shiftz() {return map & max_z ? false : map <<= movz;}

  //rotate cube 90 degrees clockwise around an axis at the center
  void rotatez();
  void rotatex();
  void rotatey();

  //rotate cube 180 degrees around an axis at the center
  void rotatezz();
  void rotatexx();
  void rotateyy();

  //get map
  bits get() const {return map;}

  //print cube to stream in a readable fashion
  friend std::ostream& operator<<(std::ostream& out, Cube const& self);
};

