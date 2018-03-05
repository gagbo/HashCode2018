#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "Position.h"
#include "Ride.h"
#include <map>
#include <vector>
#include <limits>

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
  // The number of rides taken with bonus
  int ride_with_bonus;
  // The array of the (ordered) IDs of the rides this car plans
  std::vector<int> rides_id;
  // The priority of the vehicle in the fleet
  int priority;
  // Boolean that tells if the car can take any more ride
  bool can_take_ride;

  // Default constructor
  Vehicle()
      : id(0),
        avail_pos(0, 0),
        avail_time(0),
        score(0),
        ride_with_bonus(0),
        priority(0),
        can_take_ride(true) {
      ;
  }
  // Overloaded constructor
  Vehicle(int _id)
      : id(_id),
        avail_pos(0, 0),
        avail_time(0),
        score(0),
        ride_with_bonus(0),
        priority(0),
        can_take_ride(true) {
      ;
  }
  // Copy constructor
  Vehicle(const Vehicle &other) {
    id = other.id;
    avail_pos = other.avail_pos;
    avail_time = other.avail_time;
    score = other.score;
    ride_with_bonus = other.ride_with_bonus;
    priority = other.priority;
    rides_id = other.rides_id;
    can_take_ride = other.can_take_ride;
  }
  // Assignment operator
  Vehicle &operator=(const Vehicle &rhs);
  // Destructor
  ~Vehicle() { ; }

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

  // Update the priority of the car for the priority queue
  void update_priority();

  // Reduce priority to minimum and set can_take_ride to false
  void make_unavailable();

  // Comparison operators for the priority queue
  inline bool operator>(const Vehicle &rhs) const {
    return priority > rhs.priority;
  }
  inline bool operator<(const Vehicle &rhs) const {
    return priority < rhs.priority;
  }
};

#endif // _VEHICLE_H_
