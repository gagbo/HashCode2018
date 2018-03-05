#include "Vehicle.h"

// Assignment operator
Vehicle &Vehicle::operator=(const Vehicle &rhs) {
  if (&rhs == this) {
    return *this;
  }
  id = rhs.id;
  avail_pos = rhs.avail_pos;
  avail_time = rhs.avail_time;
  score = rhs.score;
  ride_with_bonus = rhs.ride_with_bonus;
  priority = rhs.priority;
  rides_id = rhs.rides_id;
  can_take_ride = rhs.can_take_ride;
  return *this;
}

void Vehicle::add_ride(const Ride &affected_ride, int bonus) {
  rides_id.push_back(affected_ride.id);
  int added_score = 0;
  // To uncomment with the std::cerr block below
  // bool got_bonus(false);
  avail_time += distance(avail_pos, affected_ride.s_pos);
  if (avail_time < affected_ride.min_start) {
    int wait_time = affected_ride.min_start - avail_time;
    avail_time += wait_time;
    added_score += bonus;
    ride_with_bonus++;
    // To uncomment with the std::cerr block below
    // got_bonus = true;
  }
  avail_time += affected_ride.dist;
  if (avail_time <= affected_ride.max_finish) {
    added_score += affected_ride.dist;
  }
  avail_pos = affected_ride.f_pos;
  score += added_score;

  update_priority();

  // Used to output the new state of the Vehicle after taking the course
  // Leave commented out for the larger cases
  /*
  std::cerr << "New avail pos = " << avail_pos.row << " " << avail_pos.col
            << " ; new avail_time = " << avail_time
            << " ; Added score = " << added_score
            << (got_bonus ? " (got bonus)\n" : "\n");
            */
}

int Vehicle::potential_score(const Ride &pot_ride, int bonus) const {
  int pot_score = 0;

  int theoretical_time = avail_time;
  theoretical_time += distance(avail_pos, pot_ride.s_pos);

  int th_start_time = theoretical_time;
  theoretical_time += pot_ride.dist;

  if (th_start_time < pot_ride.min_start) {
    pot_score += bonus;
  }
  pot_score += pot_ride.dist;

  if (theoretical_time < pot_ride.max_finish) {
    return pot_score;
  } else {
    return 0;
  }
}

void Vehicle::print() const {
  std::cout << rides_id.size() << " ";
  if (rides_id.size()) {
    for (unsigned int i = 0; i < rides_id.size() - 1; ++i) {
      std::cout << rides_id[i] << " ";
    }
    if (rides_id.size() >= 1) {
      std::cout << rides_id[rides_id.size() - 1] << "\n";
    }
  } else {
    std::cout << "\n";
  }
  return;
}

void Vehicle::printDebug() const {
  std::cerr << "ID(" << id << ") : "
  << rides_id.size() << " ";
  for (unsigned int i = 0; i < rides_id.size(); ++i) {
    std::cerr << rides_id[i] << " ";
  }
  std::cerr << " Score : " << score << " ; Priority : " << priority << "\n";
  return;
}

int Vehicle::find_and_affect_ride(const std::map<int, Ride> &rides_map,
                                  int bonus) {
  int max_score = 0;
  int max_id = -1;

  for (auto it : rides_map) {

    int pot_score = potential_score(it.second, bonus);

    if (pot_score > max_score) {
      max_score = pot_score;
      max_id = it.second.id;
    }
  }

  // max_id is >= 0 only if there is a ride that's possible
  if (max_id >= 0) {
    add_ride(rides_map.find(max_id)->second, bonus);
  }

  return max_id;
}

void Vehicle::update_priority() {
  // The less rides we have, the higher the priority
  // priority = -1 * rides_id.size();
  // The earlier the car is ready, the higher the priority;
  priority = 1000000000 - avail_time;
}

void Vehicle::make_unavailable() {
  priority = std::numeric_limits<int>::min();
  can_take_ride = false;
  return;
}
