#pragma once
#include<iostream>
#include<ctime>
#include<mutex>
#include "cube.h"


using bits = Cube::bits;

const bits vv_piece = 0x10031;
//█
//
//--
//█
//██
const bits xi_piece = 0x272;
// █
//███
// █
const bits yi_piece = 0x172;
// █
//███
//█
const bits wi_piece = 0x136;
// ██
//██
//█
const bits zs_piece = 0x30062;
//██
//
//---
// █
// ██
const bits jl_piece = 0x10047;
//█
//
//---
//███
//  █
const bits tt_piece = 0x20027;
// █
//
//---
//███
// █
const bits ll_piece = 0x10017;
//█
//
//---
//███
//█
const bits zl_piece = 0x10063;
//█
//
//---
//██
// ██
const bits zt_piece = 0x20063;
// █
//
//---
//██
// ██
const bits lv_piece = 0x10223;
//█
//
//
//---
//██
// █
// █
const bits tl_piece = 0x10027;
//█
//
//---
//███
// █
const bits at_piece = 0x20072;
// █
//
//---
// █
//███
const int max_piece = 13;
const int last_piece = max_piece - 1;
const int max_rotations = 24;
const int last_rotation = max_rotations - 1;
const bits pieces[max_piece] = {
  vv_piece, xi_piece, wi_piece, zs_piece,
  jl_piece, tt_piece, yi_piece, ll_piece,
  zl_piece, zt_piece, lv_piece, tl_piece, at_piece};

std::ostream& get_time(std::ostream& out, time_t const& start);

//_Tp should have ++ and < defined
template<typename _Tp> class Tracker
{
  std::mutex lock;
  _Tp value;
  const _Tp max;
public:
  Tracker(_Tp const& end) : lock(), value(), max(end) {}
  Tracker(_Tp const& start, _Tp const& end) : lock(), value(start), max(end) {}

  bool get()
  {
    lock.lock();
    if(value < max)
      return true;
    lock.unlock();
    return false;
  }

  _Tp release()
  {
    _Tp out = value++;
    lock.unlock();
    return out;
  }
};
