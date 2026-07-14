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
template <RealFunction F, RealFunction DF>
auto
newton_raphsor (const double p0, const F &f, const DF &f_prime)
    -> std::pair<double, size_t>
{
  static constexpr double minimum_derivative{ 1e-12 };

  double p{}, pp{ p0 };

  for (size_t i{ 1 }; i <= MAX_ITER; ++i)
    {
      const double fpp = f_prime (pp);

      // Probably diverged, we would get division by 0 (or near 0) here
      if (std::abs (fpp) < minimum_derivative)
        {
          std::println ("Derivative too small, the method diverged");
          return std::make_pair (stub, -1);
        }

      const double fp = f (pp);
      p = pp - fp / fpp;
      // std::println("Iteration {}: {}", i, p);

      // Converged
      if (std::abs (p - pp) < EPS or std::abs (fp) < EPS)
        return std::make_pair (p, i);

      // Next iteration
      pp = p;
    }

  // No convergence
  std::println ("Maximum iteration limit achieved, possible divergence");
  return std::make_pair (stub, -1);
}

// Driver code
#ifndef HERMES_TEST
int
main ()
{
  // Functions to test and their derivatives
  std::array<std::pair<Func, Func>, 3> functions
      = { { // x^2 - cos(x), 2x + sin(x)
            { [] (const double x) { return x * x - std::cos (x); },
              [] (const double x) { return 2 * x + std::sin (x); } },

            // x^3 - 1, 3x^2
            { [] (const double x) { return x * x * x - 1; },
              [] (const double x) { return 3 * x * x; } },

            // e^x - 10x, e^x - 10
            { [] (const double x) { return std::exp (x) - 10 * x; },
              [] (const double x) { return std::exp (x) - 10; } } } };

  std::println ("Testing newton's method for functions:");
  std::println ("f(x) = x^2 - cos(x)");
  std::println ("f(x) = x^3 - 1");
  std::println ("f(x) = e^x - 10x\n");

  // Testing
  std::ranges::for_each (
      functions,
      [] (auto &&fs)
        {
          double p0{};
          std::println ("Give an initial guess p0");
          std::cin >> p0;

          auto r{ newton_raphsor (p0, fs.first, fs.second) };
          if (r.second == -1) // Stub
            std::println (
                "Method failed, maybe try a better initial guess latter?");
          else
            std::println ("Newton's method returned {} in {} iterations\n",
                          r.first, r.second);
        });

  return 0;
}
#endif
