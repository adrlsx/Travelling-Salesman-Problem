#ifndef TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H
#define TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H

#include <unordered_set>
#include "../../UndirectedCompleteGraph.h"

#define FIRST_VERTEX 0

using std::unordered_set, std::pair;

typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_iterator;      //adjacency iterator type

void constructive(UndirectedCompleteGraph& graph);
unsigned int nearestVertex(unsigned int vertex, const unordered_set<unsigned int>& discovered, const UndirectedCompleteGraph& graph);
#endif //TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H
