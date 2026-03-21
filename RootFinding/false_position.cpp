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
template<RealFunction F>
auto false_position(const double a, const double b, const F &f) -> double {
    double la{a}, lb{b}, c{}, fa{f(la)}, fb{f(lb)}, fc{};
    if (fa * fb >= 0) throw std::domain_error("Bolzano's theorem not satisfied");

    size_t i{1};
    while (i <= MAX_ITER) {
        if (std::abs(fb - fa) < EPS)
            throw std::runtime_error("Division by zero: denominator too small");

        c = la - ((fa * (lb - la)) / (fb - fa));
        fc = f(c);

        std::println("Iteration {}: a = {}, b = {}, c = {}", i, la, lb, c);

        if (std::abs(fc) < EPS or std::abs(lb - la) < EPS) return c;

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
    throw std::runtime_error("Max iteration limit exceeded");
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

        try {
            double r{false_position(a, b, f)};
            std::println("False position method returned {}\n", r);
        } catch (const std::domain_error &e) {
            std::print("Method failed because: {}\n\n", e.what());
        } catch (const std::runtime_error &e) {
            std::print("{}\n\n", e.what());
        }
    });

    return 0;
}
