cmake_minimum_required(VERSION 4.1)

project(NumericalCPPMethods LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

add_executable(bisection RootFinding/bisection.cpp)
add_executable(newton_raphsor RootFinding/newton_raphsor.cpp)
