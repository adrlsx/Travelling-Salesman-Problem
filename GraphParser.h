#ifndef TRAVELLING_SALESMAN_PROBLEM_GRAPHPARSER_H
#define TRAVELLING_SALESMAN_PROBLEM_GRAPHPARSER_H

#include <boost/graph/adjacency_matrix.hpp>
#include <fstream>

using boost::property; using boost::edge_weight_t; using boost::adjacency_matrix; using boost::undirectedS; using boost::no_property;
using std::string;

typedef property<edge_weight_t, unsigned long> EdgeWeight;
typedef adjacency_matrix<undirectedS, no_property, EdgeWeight> UndirectedCompleteGraph;   //sets the property for an undirected complete graph

UndirectedCompleteGraph graphFromFile(const string& fileName);


#endif //TRAVELLING_SALESMAN_PROBLEM_GRAPHPARSER_H
