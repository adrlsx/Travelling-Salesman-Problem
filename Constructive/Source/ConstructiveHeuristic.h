#ifndef TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H
#define TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H

#include "../../UndirectedCompleteGraph.h"

void constructive(UndirectedCompleteGraph& graph);
unsigned int nearestVertex(unsigned int vertex, const vector<bool>& discovered, const UndirectedCompleteGraph& graph);
unsigned int lightestEdgeSource(const Graph& graph);

#endif //TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H
