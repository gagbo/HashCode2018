#ifndef _RIDE_H_
#define _RIDE_H_

#include "Position.h"
#include <iostream>

// Class that reprensents an ordered ride
struct Ride {
  // Unique id for the ride
  int id;
  // Starting position
  Position s_pos;
  // Destination position
  Position f_pos;
  // Earliest turn we can start the ride
  int min_start;
  // Last possible turn we can complete the ride
  int max_finish;
  // Manhattan distance between the start and the destination
  int dist;

  // Print info on the ride on stderr
  void print() const ;

  // Overloaded constructor
  Ride(int _id, int start_row, int start_col, int finish_row, int finish_col,
       int min_start_time, int max_finish_time);

  // Default constructor
  Ride() : s_pos(0,0), f_pos(0,0) {;}

  // Copy constructor
  Ride(const Ride& other) {
    id = other.id;
    s_pos = other.s_pos;
    f_pos = other.f_pos;
    min_start = other.min_start;
    max_finish = other.max_finish;
    dist = other.dist;
  }

  // Assignment operator
  Ride& operator= (const Ride& other) {
    id = other.id;
    s_pos = other.s_pos;
    f_pos = other.f_pos;
    min_start = other.min_start;
    max_finish = other.max_finish;
    dist = other.dist;
    return *this;
  }

  // Destructor
  ~Ride() {;}
};
#endif // _RIDE_H_
