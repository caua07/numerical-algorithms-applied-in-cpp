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

// The method
template <RealFunction F>
auto
false_position (const double a, const double b, const F &f)
    -> std::pair<double, size_t>
{
  double la{ a }, lb{ b }, c{}, fa{ f (la) }, fb{ f (lb) }, fc{};

  if (fa * fb >= 0)
    {
      std::println ("Bolzano's theorem not satisfied");
      return std::make_pair (stub, -1);
    }

  size_t i{ 1 };
  while (i <= MAX_ITER)
    {
      if (std::abs (fb - fa) < EPS)
        {
          std::println ("Division by zero: denominator too small");
          return std::make_pair (stub, -1);
        }

      c = la - ((fa * (lb - la)) / (fb - fa));
      fc = f (c);

      // std::println("Iteration {}: a = {}, b = {}, c = {}", i, la, lb, c);

      if (std::abs (fc) < EPS or std::abs (lb - la) < EPS)
        return std::make_pair (c, i);

      if (fc * fa < 0)
        {
          lb = c;
          fb = fc;
        }
      else
        {
          la = c;
          fa = fc;
        }

      ++i;
    }

  // No convergence
  std::println ("Max iteration limit exceeded");
  return std::make_pair (c, -i);
}

// Driver code
#ifndef HERMES_TEST
int
main ()
{
  // Functions to test
  std::array<Func, 3> functions = {
    [] (const double x) { return x * x - std::cos (x); },  // x^2 - cos(x)
    [] (const double x) { return x * x * x - 1; },         // x^3 - 1
    [] (const double x) { return std::exp (x) - 10 * x; }, // e^x - 10x
  };

  std::println ("Testing false position method for functions:");
  std::println ("f(x) = x^2 - cos(x)");
  std::println ("f(x) = x^3 - 1");
  std::println ("f(x) = e^x - 10x\n");

  // Testing
  std::ranges::for_each (
      functions,
      [] (const auto &f)
        {
          double a{}, b{};
          std::println ("Give an initial range [a, b] (space separated)");
          std::cin >> a >> b;

          auto r{ false_position (a, b, f) };
          if (r.second == -1) // Stub hit
            std::println (
                "Method failed, maybe try a better initial guess latter?");
          else
            std::println (
                "False position method returned {} on {} iterations\n",
                r.first, r.second);
        });

  return 0;
}
#endif
