#define HERMES_TEST
#include "../newton_raphsor.cpp"

#include <cassert>
#include <cmath>

auto main() -> int {
  auto f1 = [](const double x) { return x * x - std::cos(x); };
  auto df1 = [](const double x) { return 2 * x + std::sin(x); };
  const auto root1 = newton_raphsor(1.0, f1, df1);
  assert(root1.second != static_cast<size_t>(-1));
  assert(std::abs(root1.first - 0.8241323123) < 1e-5);
  assert(std::abs(f1(root1.first)) < 1e-5);

  auto f2 = [](const double x) { return x * x * x - 1; };
  auto df2 = [](const double x) { return 3 * x * x; };
  const auto root2 = newton_raphsor(0.5, f2, df2);
  assert(root2.second != static_cast<size_t>(-1));
  assert(std::abs(root2.first - 1.0) < 1e-5);
  assert(std::abs(f2(root2.first)) < 1e-5);

  auto f3 = [](const double x) { return std::exp(x) - 10 * x; };
  auto df3 = [](const double x) { return std::exp(x) - 10; };
  const auto root3 = newton_raphsor(0.1, f3, df3);
  assert(root3.second != static_cast<size_t>(-1));
  assert(std::abs(root3.first - 0.1118325592) < 1e-5);
  assert(std::abs(f3(root3.first)) < 1e-5);

  return 0;
}
