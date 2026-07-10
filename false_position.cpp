#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <print>

// Tolerance
constexpr double EPS = 1e-6;
// Max iterations
constexpr size_t MAX_ITER = 256;
// STUB
constexpr double stub = std::numeric_limits<double>::max();

// Real functions template
template <typename F>
concept RealFunction = requires(F f, double x) {
  { f(x) } -> std::convertible_to<double>;
};

// Function type signature
using Func = std::function<double(double)>;

// The method
template <RealFunction F>
auto false_position(const double a, const double b, const F &f) -> double {
  double la{a}, lb{b}, c{}, fa{f(la)}, fb{f(lb)}, fc{};
  if (fa * fb >= 0) {
    std::println("Bolzano's theorem not satisfied");
    return stub;
  }

  size_t i{1};
  while (i <= MAX_ITER) {
    if (std::abs(fb - fa) < EPS) {
      std::println("Division by zero: denominator too small");
      return stub;
    }

    c = la - ((fa * (lb - la)) / (fb - fa));
    fc = f(c);

    std::println("Iteration {}: a = {}, b = {}, c = {}", i, la, lb, c);

    if (std::abs(fc) < EPS or std::abs(lb - la) < EPS)
      return c;

    if (fc * fa < 0) {
      lb = c;
      fb = fc;
    } else {
      la = c;
      fa = fc;
    }

    ++i;
  }

  // No convergence
  std::println("Max iteration limit exceeded");
  return stub;
}

// Driver code
int main() {
  // Functions to test
  std::array<Func, 3> functions = {
      [](const double x) { return x * x - std::cos(x); },
      [](const double x) { return x * x * x - 1; },
      [](const double x) { return std::exp(x) - 10 * x; },
  };

  std::println("Testing false position method for functions:");
  std::println("f(x) = x^2 - cos(x)");
  std::println("f(x) = x^3 - 1");
  std::println("f(x) = e^x - 10x\n");

  // Testing
  std::ranges::for_each(functions, [](auto &f) {
    double a{}, b{};
    std::println("Give an initial range [a, b] (space separated)");
    std::cin >> a >> b;

    double r{false_position(a, b, f)};
    if (r == stub)
      std::println("Method failed, maybe try a better initial guess latter?");
    else
      std::println("False position method returned {}\n", r);
  });

  return 0;
}
