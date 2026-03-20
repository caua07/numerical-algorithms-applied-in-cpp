#include <print>
#include <cmath>
#include <string>


const double PI = std::acos(-1);
const double EPS = 10e-6;

inline auto func_one_prime(const double x) -> double {
  return 2*x + std::sin(x);
}

inline auto f(const double x) -> double  {
  return (x*x) - std::cos(x); 
}

auto bisect(double a, double b, double tol, double n) -> double
{
  double FA = f(a);

  for (int i{0}; i < n; ++i) {
    double p = a + (b - a)/2;

    double FP = f(p); 

    if (std::abs(FP) < tol || (b - a)/2 < tol)
      return p;

    if (FA * FP > 0) {
      a = p;
      FA = FP;
    } else { 
      b = p;
    }
  }

  return std::numeric_limits<double>::quiet_NaN();
}

auto bisect_rec(double a, double b, double tol, double n) -> double
{
  double FA = f(a);
  double FB = f(b);

  double p = a + (b - a)/2;
  double FP = f(p);

  
  if (std::abs(FP) < tol || (b - a)/2 < tol)
    return p;

  if (n == 0) 
    return std::numeric_limits<double>::quiet_NaN();

  if (FA*FB < 0) {
    if (FA * FP < 0) 
      return bisect_rec(a, p, tol, n-1);
    else
      return bisect_rec(p, b, tol, n-1);
  }

  return std::numeric_limits<double>::quiet_NaN();
}

auto main() -> int {

  double a{0}, b{PI/2};

  auto biTest = bisect_rec(-1, 0, EPS, 256);
  auto test = bisect(-1, 0, EPS, 256);
  std::print("the result of the recursive test was: ");
  std::print("{}", biTest);
  std::println();
  std::print("the result of the normal test was: ");
  std::print("{}", test);

  return 0;
}
