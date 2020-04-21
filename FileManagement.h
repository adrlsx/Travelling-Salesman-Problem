#ifndef TRAVELLING_SALESMAN_PROBLEM_FILEMANAGEMENT_H
#define TRAVELLING_SALESMAN_PROBLEM_FILEMANAGEMENT_H

#include <boost/graph/adjacency_matrix.hpp>
#include <fstream>

#define STRING_TO_ULONG(string) (strtoul(string.c_str(), nullptr, 10))
#define MAX_VALUE (std::numeric_limits<unsigned long>::max()) //this is the max value an unsigned long can hold, it is used in algorithm to model an infinite number

using boost::property, boost::edge_weight_t, boost::adjacency_matrix, boost::undirectedS, boost::no_property;
using std::string, std::vector, std::endl, std::stringstream, std::ios;

typedef property<edge_weight_t, unsigned long> EdgeWeight;
typedef adjacency_matrix<undirectedS, no_property, EdgeWeight> UndirectedCompleteGraph;   //sets the property for an undirected complete graph
typedef boost::graph_traits<UndirectedCompleteGraph>::adjacency_iterator adjacency_iterator;      //sets the property for an adjacency iterator

unsigned long getWeight(const unsigned long& firstVertex, const unsigned long& secondVertex, const UndirectedCompleteGraph& graph);
UndirectedCompleteGraph graphFromFile(const string& fileName);
void resultToFile(const vector<unsigned long>& path, const unsigned long& distance, const string& fileName, const string& functionName);

#endif //TRAVELLING_SALESMAN_PROBLEM_FILEMANAGEMENT_H
