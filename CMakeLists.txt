cmake_minimum_required(VERSION 3.15)
project(Travelling_Salesman_Problem)

set(CMAKE_CXX_STANDARD 20)

add_executable(Travelling_Salesman_Problem main.cpp Constructive/Source/ConstructiveHeuristic.cpp Constructive/Source/ConstructiveHeuristic.h Exact/Source/ExactAlgorithm.cpp Exact/Source/ExactAlgorithm.h UndirectedCompleteGraph.cpp UndirectedCompleteGraph.h Local_Search/Source/LocalSearchHeuristic.cpp Local_Search/Source/LocalSearchHeuristic.h)