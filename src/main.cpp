#include <iostream>

#include "Position.h"
#include "Ride.h"
#include "Vehicle.h"
#include <limits>
#include <map>
#include <queue>

int main() {
  std::cerr << "Hello Oracle !" << std::endl;

  // Read the input data
  int row_max, col_max, fleet_size, ride_count, start_bonus, sim_steps;

  std::cin >> row_max >> col_max >> fleet_size >> ride_count >> start_bonus >>
      sim_steps;
  std::cin.ignore();

  Ride rides[ride_count];
  std::map<int, Ride> rides_map;

  std::priority_queue<Vehicle, std::vector<Vehicle>, std::less<Vehicle>> fleet;
  for (int i = 0; i < fleet_size; ++i) {
    fleet.emplace(i);
  }

  for (int i = 0; i < ride_count; ++i) {
    int start_row, start_column, finish_row, finish_column, min_start_time,
        max_finish_time;
    std::cin >> start_row >> start_column >> finish_row >> finish_column >>
        min_start_time >> max_finish_time;
    std::cin.ignore();

    rides_map.insert(std::make_pair(i, Ride(i, start_row, start_column,
                                            finish_row, finish_column,
                                            min_start_time, max_finish_time)));
    /* rides[i].print(); */
  }

  // Do stuff now that problem is read

  // Here we find the best ride for the car with the best priority on each loop.
  // The loop stops once we have no ride left, or if the Fleet queue is filled
  // with only cars that cannot take one of the remaining rides;
  bool car_was_available = true;
  int compteur = 0;
  while (rides_map.size() != 0) {
    // Init
    car_was_available = false;
    int max_score = 0;
    int max_ride_id = -1;
    Ride max_ride;
    compteur += 1;
    if (compteur % 100 == 0) {
      std::cerr << "Affecting " << compteur << "th ride\n";
    }

    // Get the highest priority car that is available
    Vehicle current_car;
    int cars_left = fleet_size;
    do {
      current_car = fleet.top();
      fleet.pop();
      if (!current_car.can_take_ride) {
        cars_left--;
        current_car.make_unavailable();
        fleet.push(current_car);
      }
    } while (!current_car.can_take_ride && cars_left > 0);

    if (cars_left == 0) {
      break;
    }

    // Assign a ride to the best car
    for (auto it : rides_map) {

      int pot_score = current_car.potential_score(it.second, start_bonus);

      if (pot_score > max_score) {
        max_score = pot_score;
        max_ride = it.second;
        max_ride_id = it.second.id;
        car_was_available = true;
      }
    }

    if (car_was_available) {
      auto p_ride = rides_map.find(max_ride_id);
      current_car.add_ride(p_ride->second, start_bonus);
      rides_map.erase(p_ride);
    } else { // If no ride is available to the car, nuke priority and update
             // flag
      current_car.make_unavailable();
    }
    // Debug to see the cars update
    // current_car.printDebug();

    // Put the car back in the list
    fleet.push(current_car);
  }

  // Print the result
  int sum = 0;
  int total_rides = 0;
  int total_rides_with_bonus = 0;
  while (!fleet.empty()) {
    Vehicle top_car = fleet.top();
    top_car.print();
    sum += top_car.score;
    total_rides += top_car.rides_id.size();
    total_rides_with_bonus += top_car.ride_with_bonus;

    fleet.pop();
  }

  std::cerr << "##################################################\n"
               "With "
            << fleet_size << " cars : \n"
            << "Score total    : " << sum << "\n"
            << "Rides taken    : " << total_rides << "\n"
            << "... with bonus : " << total_rides_with_bonus << "\n"
            << "Rides left     : " << rides_map.size() << "\n";

  return 0;
}
