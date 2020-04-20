cmake_minimum_required(VERSION 3.15)
project(Travelling_Salesman_Problem)

set(CMAKE_CXX_STANDARD 20)

add_executable(Travelling_Salesman_Problem main.cpp FileManagement.cpp FileManagement.h Constructive/Source/ConstructiveHeuristic.cpp Constructive/Source/ConstructiveHeuristic.h Exact/Source/ExactAlgorithm.cpp Exact/Source/ExactAlgorithm.h)