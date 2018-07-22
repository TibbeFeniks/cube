#pragma once
#include<array>
#include<vector>
#include<iostream>
#include "piece.h"


class CachedPiece : public Piece
{
protected:
  using rot_array = std::array<bits, max_rotations>;
  std::vector<rot_array> permutations;
  unsigned int pos;
  int last;

  bool repeat_check() const;

public:
  CachedPiece() : pos(0), last(-1) {}

  CachedPiece(int number);

  void reset();

  void set(int number);

  bool next();

  bool rotate();

  std::ostream& simpleprint(std::ostream& out) const;
};

