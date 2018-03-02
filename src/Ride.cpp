#include "Ride.h"

Ride::Ride(int _id, int start_row, int start_col, int finish_row,
           int finish_col, int min_start_time, int max_finish_time)
    : id(_id), s_pos(start_row, start_col), f_pos(finish_row, finish_col),
      min_start(min_start_time), max_finish(max_finish_time) {
  dist = distance(s_pos, f_pos);
}

void Ride::print() const {
  std::cerr << "Ride no " << id << " : \n";
  std::cerr << "Start : " << s_pos.row << ", " << s_pos.col << "\n";
  std::cerr << "Finish : " << f_pos.row << ", " << f_pos.col << "\n";
  std::cerr << "Must start at (or after) " << min_start << " and finish before "
            << max_finish << " (distance = " << dist << ")\n";
  return;
}
