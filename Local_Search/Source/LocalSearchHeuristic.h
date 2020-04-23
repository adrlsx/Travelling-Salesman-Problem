#ifndef TRAVELLING_SALESMAN_PROBLEM_LOCALSEARCHHEURISTIC_H
#define TRAVELLING_SALESMAN_PROBLEM_LOCALSEARCHHEURISTIC_H

#include "../../UndirectedCompleteGraph.h"
#include "../../Constructive/Source/ConstructiveHeuristic.h"

void localSearch(UndirectedCompleteGraph& graph);
void swap(unsigned int firstVertexPosition, unsigned int secondVertexPosition, vector<unsigned int>& path);

#endif //TRAVELLING_SALESMAN_PROBLEM_LOCALSEARCHHEURISTIC_H
