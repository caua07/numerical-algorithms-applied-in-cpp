#!/bin/bash

g++ $1.cpp --std=c++26 -Ofast -march=native -fno-rtti -o build/$1 && ./build/$1
