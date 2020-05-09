#ifndef TRAVELLING_SALESMAN_PROBLEM_GRASP_H
#define TRAVELLING_SALESMAN_PROBLEM_GRASP_H

#include "../../UndirectedCompleteGraph.h"

void grasp(UndirectedCompleteGraph& graph, unsigned int alpha, unsigned int improvedIteration, unsigned int graspMaxIteration, unsigned int localSearchMaxIteration);
void greedyRandomizedConstruction(UndirectedCompleteGraph& graph, unsigned int alpha);
unsigned int restrictedCandidateList(unsigned int RCL_size, unsigned int vertex, const vector<bool>& discovered, const UndirectedCompleteGraph& graph);
float satisfyingCriteria(unsigned int alpha, unsigned int vertex, const vector<bool>& discovered, const UndirectedCompleteGraph& graph);
unsigned int randomCandidate(unsigned int startRange, unsigned int endRange);

#endif //TRAVELLING_SALESMAN_PROBLEM_GRASP_H
