#pragma once
#include<cstdint>
#include<iostream>


class Cube
{
protected:
  using bits = uint64_t;
  static constexpr bits max_bit = 0x8000000000000000;
  static constexpr bits max_x = 0x8888888888888888;
  static constexpr bits max_y = 0xf000f000f000f000;
  static constexpr bits max_z = 0xffff000000000000;
  static constexpr int movx = 1;
  static constexpr int movy = 4;
  static constexpr int movz = 16;
  static constexpr bits zrot[8] = {
    0x33003300330033, 0xcc00cc00cc00cc, 0x3300330033003300, 0xcc00cc00cc00cc00,
    0x505050505050505, 0xa0a0a0a0a0a0a0a, 0x5050505050505050, 0xa0a0a0a0a0a0a0a0};
  static constexpr bits xrot[8] = {
    0xff00ff, 0xff00ff00, 0xff00ff00000000, 0xff00ff0000000000,
    0xf0f00000f0f, 0xf0f00000f0f0, 0xf0f00000f0f0000, 0xf0f00000f0f00000};
  static constexpr bits yrot[8] = {
    0x33333333, 0xcccccccc, 0x3333333300000000, 0xcccccccc00000000,
    0x555500005555, 0xaaaa0000aaaa, 0x5555000055550000, 0xaaaa0000aaaa0000};
  static constexpr int steps = 6;
  static constexpr bits splits[steps] = {
    0xaaaaaaaaaaaaaaaa, 0xcccccccccccccccc, 0xf0f0f0f0f0f0f0f0,
    0xff00ff00ff00ff00, 0xffff0000ffff0000, 0xffffffff00000000};

  bits map;

public:
  Cube() : map(0) {}

  Cube(bits origin) : map(origin) {}

  int count() const;

  bool merge(Cube const& other);

  bool remove(Cube const& other);

  void rotatez();

  void rotatex();

  void rotatey();

  friend std::ostream& operator<<(std::ostream& out, Cube const& self);
};

class Piece : public Cube
{
protected:
  static constexpr bits vv_piece = 0x10031;
  //█
  //
  //--
  //█
  //██
  static constexpr bits xi_piece = 0x272;
  // █
  //███
  // █
  static constexpr bits yi_piece = 0x172;
  // █
  //███
  //█
  static constexpr bits wi_piece = 0x136;
  // ██
  //██
  //█
  static constexpr bits zs_piece = 0x30062;
  //██
  //
  //---
  // █
  // ██
  static constexpr bits jl_piece = 0x10047;
  //█
  //
  //---
  //███
  //  █
  static constexpr bits tt_piece = 0x20027;
  // █
  //
  //---
  //███
  // █
  static constexpr bits ll_piece = 0x10017;
  //█
  //
  //---
  //███
  //█
  static constexpr bits zl_piece = 0x10063;
  //█
  //
  //---
  //██
  // ██
  static constexpr bits zt_piece = 0x20063;
  // █
  //
  //---
  //██
  // ██
  static constexpr bits lv_piece = 0x10223;
  //█
  //
  //
  //---
  //██
  // █
  // █
  static constexpr bits tl_piece = 0x10027;
  //█
  //
  //---
  //███
  // █
  static constexpr bits at_piece = 0x20072;
  // █
  //
  //---
  // █
  //███
  static constexpr int max_piece = 13;
  static constexpr bits all[max_piece] = {
    vv_piece, xi_piece, yi_piece,
    wi_piece, zs_piece, jl_piece, tt_piece, ll_piece,
    zl_piece, zt_piece, lv_piece, tl_piece, at_piece};
  static constexpr int max_rotations = 24;
  static constexpr int cycle_rotations[max_rotations] = {
    1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 3};

  int rotation;

public:
  Piece() : rotation(0) {}

  Piece(int number);

  void set(int number);

  bool next();

  bool rotate();

  int get_rotation() const {return rotation;}
};
