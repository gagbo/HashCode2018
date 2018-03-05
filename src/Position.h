#ifndef _POSITION_H_
#define _POSITION_H_
#include <cmath>

// Class that represents a position on the map
struct Position {
  // Row index (given first in (r,c) tuples in Google's syntax)
  int row;
  // Column index (given second in (r,c) tuples in Google's syntax)
  int col;

  // Assignment operator
  inline Position& operator=(const Position& rhs) {
    row = rhs.row;
    col = rhs.col;
    return *this;
  }

  // Overloaded constructor
  Position(int r, int c) : row(r), col(c) { ; }
  // Default constructor
  Position() : row(0), col(0) { ; }
  // Destructor
  ~Position() { ; }
};

// Compute the Manhattan distance between 2 positions
int distance(const Position &a, const Position &b);

#endif //_POSITION_H_
