#ifndef TRAVELLING_SALESMAN_PROBLEM_EXACTALGORITHM_H
#define TRAVELLING_SALESMAN_PROBLEM_EXACTALGORITHM_H

#include <string>
#include <vector>
#include "../../FileManagement.h"

using std::string, std::vector;

void exact(const string& fileName);
unsigned long getDistanceFromPath(const vector<unsigned long>& path, const UndirectedCompleteGraph& graph);

#endif //TRAVELLING_SALESMAN_PROBLEM_EXACTALGORITHM_H
