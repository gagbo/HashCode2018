#include <iostream>

#include "Position.h"
#include "Ride.h"
#include "Vehicle.h"
#include <map>

int main() {
  std::cerr << "Hello Oracle !" << std::endl;

  // Read the input data
  int row_max, col_max, fleet_size, ride_count, start_bonus, sim_steps;

  std::cin >> row_max >> col_max >> fleet_size >> ride_count >> start_bonus >>
      sim_steps;
  std::cin.ignore();

  Ride rides[ride_count];
  std::map<int, Ride> rides_map;

  Vehicle vehicles[fleet_size];
  for (int i = 0; i < fleet_size; ++i) {
    vehicles[i].id = i;
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
  /*
  for (int i = 0; i < ride_count; ++i) {
    vehicles[0].add_ride(rides_map.find(i)->second, start_bonus);
  }
  */

  /* bool work_left_to_do = (rides_map.size() != 0); */
  bool has_affected_car = true;
  int compteur = 0;
  while (rides_map.size() != 0 && has_affected_car) {
    has_affected_car = false;
    int max_score = 0;
    int max_ride_id = -1;
    int max_car_id = -1;
    Ride max_ride;
    compteur += 1;
    if (compteur % 100 == 0) {
      std::cerr << "Affecting " << compteur << "th ride\n";
    }
    /* if (rides_map.size() == 0) { */
    /*   break; */
    /* } */

    for (int i = 0; i < fleet_size; ++i) {
      for (auto it : rides_map) {

        int pot_score = vehicles[i].potential_score(it.second, start_bonus);

        if (pot_score > max_score) {
          max_score = pot_score;
          max_ride = it.second;
          max_ride_id = it.second.id;
          max_car_id = i;
          has_affected_car = true;
        }
      }
    }

    if (has_affected_car) {
      auto p_ride = rides_map.find(max_ride_id);
      vehicles[max_car_id].add_ride(p_ride->second, start_bonus);
      rides_map.erase(p_ride);
    }
  }

  // Print the result
  int sum = 0;
  for (int i = 0; i < fleet_size; ++i) {
    vehicles[i].print();
    sum += vehicles[i].score;
  }

  std::cerr << "Score total : " << sum << "\n";

  return 0;
}
