/*
 * Authored by Cauã Eyer Rodrigues (@caua07)
*/

#include <print>
#include <cmath>
#include <iostream>

const double PI = std::acos(-1);
constexpr double EPS = 10e-6;

inline auto func_one_prime(const double x) -> double {
    return 2 * x + std::sin(x);
}

inline auto f(const double x) -> double {
    return x * x - std::cos(x);
}

auto bisect(double a, double b, const double tol, const double n) -> double {
    double FA = f(a);

    for (int i{0}; i < n; ++i) {
        const double p = a + (b - a) / 2;

        const double FP = f(p);

        if (std::abs(FP) < tol || (b - a) / 2 < tol)
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

auto bisect_rec(const double a, const double b, const double tol, const double n) -> double {
    const double FA = f(a);
    const double FB = f(b);
    const double p = a + (b - a) / 2;
    const double FP = f(p);

    if (std::abs(FP) < tol || (b - a) / 2 < tol)
        return p;

    if (n == 0)
        throw std::domain_error("Failed to converge");

    if (FA * FB < 0) {
        if (FA * FP < 0)
            return bisect_rec(a, p, tol, n - 1);

        return bisect_rec(p, b, tol, n - 1);
    }

    throw std::domain_error("Failed to converge");
}

auto main() -> int {
    try {
        double biTest = bisect_rec(-1, 0, EPS, 256);
        std::println("The result of running recursively is: {}", biTest);
    } catch (std::domain_error &e) {
        std::cerr << e.what() << "\n\n";
    }

    try {
        double test = bisect(-1, 0, EPS, 256);
        std::println("The result of running iteratively is: {}", test);
    } catch (std::domain_error &e) {
        std::cerr << e.what() << "\n\n";
    }

    return 0;
}
