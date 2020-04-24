#ifndef TRAVELLING_SALESMAN_PROBLEM_UNDIRECTEDCOMPLETEGRAPH_H
#define TRAVELLING_SALESMAN_PROBLEM_UNDIRECTEDCOMPLETEGRAPH_H

#include <boost/graph/adjacency_matrix.hpp>

#define MAX_VALUE (std::numeric_limits<unsigned int>::max()) //this is the max value an unsigned int can hold, it is used in algorithm to model an infinite number

using boost::edge_weight_t, boost::undirectedS, boost::no_property, boost::undirected_tag;
using std::string, std::vector;

typedef boost::property<edge_weight_t, unsigned int> Weight;   //weight type
typedef boost::adjacency_matrix<undirectedS, no_property, Weight> Graph;   //undirected complete graph type
typedef boost::detail::matrix_edge_desc_impl<undirected_tag, unsigned long> Edge;     //edge type

class UndirectedCompleteGraph {
private:
    string fileName;
    Graph graph;
    unsigned int nbVertices;
    vector<unsigned int> path;
    unsigned int distance;
protected:
    unsigned int matrixSize();
public:
    explicit UndirectedCompleteGraph(const string &fileName);
    virtual ~UndirectedCompleteGraph() = default;

    const string &getFileName() const {
        return fileName;
    }
    const Graph &getGraph() const {
        return graph;
    }
    const vector<unsigned int>& getPath() const{
        return path;
    }
    unsigned int pathSize() const{
        return path.size();
    }
    unsigned int getNbVertices() const{
        return this->nbVertices;
    }
    unsigned int getDistance() const;       //returns the distance of the current cycle
    void pathToFile(const string& functionName) const;      //prints the current path and the corresponding distance in a file
    void removeLastVertex();

    void updatePath(unsigned int vertex);       //adds the given vertex to the path
    void updatePath(const vector<unsigned int>& newPath);       //modify the path with the new values and recalculate the distance
    unsigned int getWeight(unsigned int firstVertex, unsigned int secondVertex) const;      //get the weight between 2 vertices
    unsigned int getWeight(const Edge& edge) const;     //get the weight of an edge
};


#endif //TRAVELLING_SALESMAN_PROBLEM_UNDIRECTEDCOMPLETEGRAPH_H