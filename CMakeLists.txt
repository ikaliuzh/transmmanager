cmake_minimum_required(VERSION 3.17)
project(transmissionmanager)

set(CMAKE_CXX_STANDARD 20)

add_executable(transmissionmanager main.cpp graph.h date.h tests.h test_runner.h)