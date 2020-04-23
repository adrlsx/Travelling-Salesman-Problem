#ifndef TRAVELLING_SALESMAN_PROBLEM_EXACTALGORITHM_H
#define TRAVELLING_SALESMAN_PROBLEM_EXACTALGORITHM_H

#include "../../UndirectedCompleteGraph.h"

void exact(UndirectedCompleteGraph& graph);
unsigned int getDistanceFromPath(const vector<unsigned int>& path, const UndirectedCompleteGraph& graph);

#endif //TRAVELLING_SALESMAN_PROBLEM_EXACTALGORITHM_H
