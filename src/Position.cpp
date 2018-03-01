#include "Position.h"

int distance(const Position &a, const Position &b) {
  return std::abs(a.row - b.row) + std::abs(a.col - b.col);
}
