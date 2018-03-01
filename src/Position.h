#ifndef _POSITION_H_
#define _POSITION_H_
#include <cmath>

struct Position {
  int row;
  int col;

  Position(int r, int c) : row(r), col(c) {;}
};

int distance(const Position& a, const Position& b);

#endif //_POSITION_H_
