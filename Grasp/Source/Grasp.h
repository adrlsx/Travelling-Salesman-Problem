#ifndef TRAVELLING_SALESMAN_PROBLEM_GRASP_H
#define TRAVELLING_SALESMAN_PROBLEM_GRASP_H

#include "../../UndirectedCompleteGraph.h"

void grasp(UndirectedCompleteGraph& graph, unsigned int RCL_size = 20, unsigned int nbIteration = 5);
void greedyRandomizedConstruction(UndirectedCompleteGraph& graph, unsigned int RCL_size);
unsigned int restrictedCandidateList(unsigned int RCL_size, unsigned int vertex, vector<bool> discovered, const UndirectedCompleteGraph& graph);
unsigned int randomCandidate(unsigned int startRange, unsigned int endRange);

#endif //TRAVELLING_SALESMAN_PROBLEM_GRASP_H
