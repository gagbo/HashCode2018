#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "Ride.h"
#include "Position.h"
#include <vector>
#include <map>

struct Vehicle {
  int id;
  Position avail_pos;
  int avail_time;
  int score;
  std::vector<int> rides_id;

  Vehicle() : id(0), avail_pos(0,0), avail_time(0), score(0) {;}
  Vehicle(int _id) : id(_id), avail_pos(0,0), avail_time(0), score(0) {;}

  void add_ride(const Ride & affected_ride, int bonus);
  bool can_affect_ride(const Ride& affected_ride) const;
  bool can_affect_ride_and_get_bonus(const Ride& affected_ride) const;

  int find_and_affect_ride(const std::map<int, Ride>& rides_map, int bonus);
  int potential_score(const Ride& pot_ride, int bonus);

  void print() const;
  void printDebug() const;
};

#endif // _VEHICLE_H_
