#define HERMES_TEST
#include "../bisection.cpp"

#include <cassert>
#include <cmath>
#include <limits>

auto main() -> int {
  const double recursive = bisect_rec(-1, 1, EPS, 256);
  const double iterative = bisect(-1, 1, EPS, 256);

  assert(recursive == std::numeric_limits<double>::max());
  assert(iterative == std::numeric_limits<double>::max());

  return 0;
}
