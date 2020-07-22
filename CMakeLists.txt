cmake_minimum_required(VERSION 3.16)
project(Polynomial)

set(CMAKE_CXX_STANDARD 14)

add_executable(Polynomial polynomialDriver.cpp polynomial.cpp polynomial.h)