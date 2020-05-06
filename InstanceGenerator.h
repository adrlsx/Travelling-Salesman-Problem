#ifndef TRAVELLING_SALESMAN_PROBLEM_INSTANCEGENERATOR_H
#define TRAVELLING_SALESMAN_PROBLEM_INSTANCEGENERATOR_H

#include <vector>

using std::vector;

void randomInstance(unsigned int nbVertices);
void instanceFile(vector<vector<unsigned int>> instance);

#endif //TRAVELLING_SALESMAN_PROBLEM_INSTANCEGENERATOR_H
