#ifndef _RIDE_H_
#define _RIDE_H_

#include "Position.h"
#include <iostream>

struct Ride {
  int id;
  Position s_pos;
  Position f_pos;
  int min_start;
  int max_finish;
  int dist;

  void print() const ;

  Ride(int _id, int start_row, int start_col, int finish_row, int finish_col,
       int min_start_time, int max_finish_time);

  Ride() : s_pos(0,0), f_pos(0,0) {;}
  Ride& operator= (const Ride& other) {
    id = other.id;
    s_pos = other.s_pos;
    f_pos = other.f_pos;
    min_start = other.min_start;
    max_finish = other.max_finish;
    dist = other.dist;
    return *this;
  }

  ~Ride() {;}

  bool operator<(const Ride& other) const { return id < other.id;}

};
#endif // _RIDE_H_
