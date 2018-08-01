#pragma once
#include "cube.h"
#include "common.h"


class Piece : public Cube
{
protected:
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

