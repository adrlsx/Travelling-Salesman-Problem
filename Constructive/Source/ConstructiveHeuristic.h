#ifndef TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H
#define TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H

#include <string>
#include <vector>
#include <unordered_set>
#include "../../FileManagement.h"

#define FIRST_VERTEX 0

using std::string, std::vector, std::unordered_set, std::pair;
using boost::adjacent_vertices;

void constructive(const string& fileName);
void nearestVertex(const unordered_set<unsigned long>& discoveredVertices, unsigned long& minimumWeightFound, unsigned long& currentVertex, const UndirectedCompleteGraph& graph);

#endif //TRAVELLING_SALESMAN_PROBLEM_CONSTRUCTIVEHEURISTIC_H
