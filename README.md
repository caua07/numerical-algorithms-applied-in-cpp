# Numerical methods in C++
This project contais implementations of Numerical Methods in C++26.

Tho we are using modern C++ features (like `std::print` and lambdas), we aim for fast and efficient code.

You can run the code in UNIX systems with `gcc` using `./run.sh {NAME OF THE METHOD}`.

**Reference book: Numerical Analysis, by Burden and Faires**

## Method list
### Root finding
- [Bisection](bisection.cpp), basically binary search for finding zeros of functions, it's slow, but it's the most reliable.
- [False Position](false_position.cpp), a variation of bisection that uses a straight line drawn between two points to estimate the root's location, usually converging faster by aiming closer to where the curve hits zero, also very reliable.
- [Newton-Raphsor](newton_raphsor.cpp), a **blazing-fast** method that follows a function's derivative down to the x-axis to find the root, requires a good starting guess, so it's not as reliable.

### Fixed-Point iteration
- [Fixed-Point](false_position.cpp), an algorithm that takes a pre-arranged function $f(x)$ and repeatedly pipes the output back in as the next input ($x_{n+1} = f(x_n)$) until successive values converge to a single, stable number.
- [Steffensen's method](steffensen.cpp), an accelerated version of fixed-point iteration that uses a clever algebraic trick (Aitken's delta squared method) to achieve Newton-like speed without needing to calculate any derivatives.
