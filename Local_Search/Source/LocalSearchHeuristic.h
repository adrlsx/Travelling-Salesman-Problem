#ifndef TRAVELLING_SALESMAN_PROBLEM_LOCALSEARCHHEURISTIC_H
#define TRAVELLING_SALESMAN_PROBLEM_LOCALSEARCHHEURISTIC_H

#include <algorithm>
#include "../../UndirectedCompleteGraph.h"
#include "../../Constructive/Source/ConstructiveHeuristic.h"

#define DIST(i, j) (graph.getWeight(*(i), *(j)))
using std::reverse;

void localSearch(UndirectedCompleteGraph& graph);

#endif //TRAVELLING_SALESMAN_PROBLEM_LOCALSEARCHHEURISTIC_H
