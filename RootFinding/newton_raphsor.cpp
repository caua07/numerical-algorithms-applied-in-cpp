/*
* Authored by The ADM (@bernardobrust)
*/

#include <algorithm>
#include <cmath>
#include <print>
#include <functional>
#include <iostream>

// Tolerance
constexpr double EPS = 1e-6;
// Max iterations
constexpr size_t MAX_ITER = 256;

// Real functions template
template<typename F>
concept RealFunction =
        requires(F f, double x)
        {
            { f(x) } -> std::convertible_to<double>;
        };

// Function type signature
using Func = std::function<double(double)>;

// The method
template<RealFunction F, RealFunction DF>
auto newton_raphsor(const double p0, const F &f, const DF &f_prime) -> double {
    size_t i{1};
    double p{}, pp{p0};
    while (i <= MAX_ITER) {
        const double fpp = f_prime(pp);

        // Probably diverged, we would get division by 0 (or near 0) here
        if (std::abs(fpp) < 1e-12)
            throw std::runtime_error("Derivative too small, possible divergence");

        p = pp - f(pp) / fpp;
        std::println("Iteration {}: {}", i, p);

        // Converged
        if (std::abs(p - pp) < EPS or std::abs(f(p)) < EPS)
            return p;

        // Next iteration
        pp = p;
        ++i;
    }

    // No convergence
    throw std::runtime_error("Max iteration limit exceeded");
}

// Driver code
int main() {
    // Functions to test
    std::array<std::pair<Func, Func>, 3> functions = {
        {
            {
                [](const double x) { return x * x - std::cos(x); },
                [](const double x) { return 2 * x + std::sin(x); }
            },
            {
                [](const double x) { return x * x * x - 1; },
                [](const double x) { return 3 * x * x; }
            },
            {
                [](const double x) { return std::exp(x) - 10 * x; },
                [](const double x) { return std::exp(x) - 10; }
            }
        }
    };

    std::println("Testing newton's method for functions:");
    std::println("f(x) = x^2 - cos(x)");
    std::println("f(x) = x^3 - 1");
    std::println("f(x) = e^x - 10x\n");

    // Testing
    std::ranges::for_each(functions, [](auto &&fs) {
        double p0{};
        std::println("Give an initial guess p0");
        std::cin >> p0;

        try {
            double r{newton_raphsor(p0, fs.first, fs.second)};
            std::println("Newton's method returned {}\n", r);
        } catch (const std::domain_error &e) {
            std::print("Method failed because: {}\n\n", e.what());
        } catch (const std::runtime_error &e) {
            std::print("{}\n\n", e.what());
        }
    });

    return 0;
}
