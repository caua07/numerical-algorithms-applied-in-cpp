#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <functional>
#include <iostream>
#include <limits>
#include <print>
#include <utility>

// Tolerance
constexpr double EPS = 1e-6;
// Max iterations
constexpr size_t MAX_ITER = 256;
// STUB
constexpr double stub = std::numeric_limits<double>::max ();

// Real functions template
template <typename F>
concept RealFunction = requires (F f, double x) {
  { f (x) } -> std::convertible_to<double>;
};

// Function type signature
using Func = std::function<double (double)>;

template <RealFunction F>
auto
steffensen (const double p0, const F &f) -> std::pair<double, int>
{
  double p{}, pp{ p0 }, p1{}, p2{};

  for (int i{ 1 }; i <= MAX_ITER; ++i)
    {
      p1 = f (pp);
      p2 = f (p1);
      p = (pp) - ((p1 - pp) * (p1 - pp)) / (p2 - 2 * p1 + pp);

      if (std::abs (p - pp) <= EPS)
        return std::make_pair (p, i);

      pp = p;
    }

  return std::make_pair (p, -1);
}

// Driver code
int
main ()
{
  std::array<Func, 3> functions = {
    [] (double x) { return std::pow (-x + 2, 1.0 / 3.0); },
    [] (double x)
      { return (1.0 / 2.0) * std::pow (10 - (x * x * x), 1.0 / 2.0); },
    [] (double x) { return std::exp (-x) * -x + 1; },
  };

  std::println ("Testing fixed-point iteration for functions:");
  std::println ("f(x) = (-x + 2)^(1/3)");
  std::println ("f(x) = 1/2(10 - x^3)^(1/2)");
  std::println ("f(x) = e^-x * -x + 1\n");

  std::ranges::for_each (
      functions,
      [] (auto &&f)
        {
          double p0{};
          std::println ("Give an initial guess p0");
          std::cin >> p0;

          auto r{ steffensen (p0, f) };
          if (r.second == -1) // Stub
            std::println (
                "Method failed, maybe try a better initial guess latter?");
          else
            std::println (
                "Fixed-point iteration returned {} in {} iterations\n",
                r.first, r.second);
        });
}
