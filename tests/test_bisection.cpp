#define HERMES_TEST
#include "../bisection.cpp"

#include <cassert>
#include <cmath>

auto main() -> int {
  constexpr double expected = -0.8241323123;

  const double recursive = bisect_rec(-1, 0, EPS, 256);
  const double iterative = bisect(-1, 0, EPS, 256);

  assert(std::abs(recursive - expected) < 1e-5);
  assert(std::abs(iterative - expected) < 1e-5);
  assert(std::abs(f(recursive)) < 1e-5);
  assert(std::abs(f(iterative)) < 1e-5);

  return 0;
}
