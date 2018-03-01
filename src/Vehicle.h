#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "Position.h"
#include "Ride.h"
#include <map>
#include <vector>

// Class that represent a car of the fleet
struct Vehicle {
  // (unique) ID of the car
  int id;
  // The position of the car after its last planned course
  Position avail_pos;
  // The turn at which the car is available after its last planned course
  int avail_time;
  // The score this car contributes to the fleet
  int score;
  // The array of the (ordered) IDs of the rides this car plans
  std::vector<int> rides_id;

  // Default constructor
  Vehicle() : id(0), avail_pos(0, 0), avail_time(0), score(0) { ; }
  // Overloaded constructor
  Vehicle(int _id) : id(_id), avail_pos(0, 0), avail_time(0), score(0) { ; }

  // Add a ride to the car's queue.
  // Use the 'bonus' argument to properly update the score of the car if it
  //     arrives before the beginning of the ride
  void add_ride(const Ride &affected_ride, int bonus);

  // Find a ride for the car within the map, and also add it to its queue
  // Return the ID of the ride that was added, or -1 if no ride is feasible
  int find_and_affect_ride(const std::map<int, Ride> &rides_map, int bonus);

  // Compute the score the car would get IF the given ride is added to the car
  // Return 0 if the ride is impossible
  int potential_score(const Ride &pot_ride, int bonus) const;

  // Print the car to stdout for the output
  void print() const;

  // Print the car rides and the score it contributes to stderr
  void printDebug() const;
};

#endif // _VEHICLE_H_
