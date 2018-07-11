#pragma once
#include "cube.cxx"


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

