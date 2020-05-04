#include <random>
#include "Grasp.h"
#include "../../Local_Search/Source/LocalSearchHeuristic.h"
#include "../../Constructive/Source/ConstructiveHeuristic.h"

typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_iterator;      //adjacency iterator type
using std::pair;

void grasp(UndirectedCompleteGraph& graph, unsigned int RCL_size, unsigned int nbIteration){
    if(RCL_size > graph.getNbVertices()){
        throw std::invalid_argument("The restricted candidate list size cannot be bigger than the total number of vertices in the graph.");
    }
    else if(RCL_size < 1){
        throw std::invalid_argument("The restricted candidate list size cannot be smaller than one.");
    }

    vector<unsigned int> finalPath;
    unsigned int finalDistance = MAX_VALUE;

    for(unsigned int i = 0; i < nbIteration; i++){          //repeat until no improvement is made
        greedyRandomizedConstruction(graph, RCL_size);  //construct a greedy randomized solution with a restricted candidate list of size RCL_size
        localSearch(graph);                             //locally improves the solution

        if(graph.getDistance() < finalDistance){            //saves the new path as the final path if its total distance is smaller than the current smallest distance
            finalDistance = graph.getDistance();
            finalPath = graph.getPath();
            i = 0;
        }
    }
    graph.updatePath(finalPath);                            //update the final path and the final distance with the best one we just found
}

void greedyRandomizedConstruction(UndirectedCompleteGraph& graph, unsigned int RCL_size){
    unsigned int vertex = lightestEdgeSource(graph.getGraph()), nbVertices = graph.getNbVertices();
    graph.clearPath();
    vector<bool> discoveredVertices(nbVertices, false);     //use of vector of bool to verify if a specific vertex is already marked as discovered in constant time

    while (graph.pathSize() != nbVertices) {        //while the path is not complete
        graph.updatePath(vertex);                   //adds the nearest vertex to the path and updates the distance
        discoveredVertices[vertex] = true;          //marks the vertex as discovered
        vertex = restrictedCandidateList(RCL_size, vertex, discoveredVertices, graph);      //gets a random vertex in the restricted candidate list and moves to it
    }
}

unsigned int restrictedCandidateList(unsigned int RCL_size, unsigned int vertex, vector<bool> discovered, const UndirectedCompleteGraph& graph){
    pair<adjacency_iterator, adjacency_iterator> adjacentVertices;
    vector<unsigned int> list;
    unsigned int nextVertex;

    for(unsigned int i = 0; i < RCL_size; i++){                 //while the restricted candidate list is not full
        nextVertex = nearestVertex(vertex, discovered, graph);  //gets the nearest vertex, return the same vertex if no adjacent vertex is available (all discovered)
        if(nextVertex != vertex){                               //if a vertex has been found
            list.push_back(nextVertex);                         //adds the vertex in the restricted candidate list
            discovered[nextVertex] = true;                      //marks the vertex as discovered only in this function spec
        }
    }
    if(!list.empty()){                                                          //if a vertex has been added in the restricted candidate list
        return list[randomCandidate(0, list.size() - 1)];   //returns a random candidate from the list
    }
    else{                                                                       //otherwise returns the input vertex
        return vertex;
    }
}

unsigned int randomCandidate(unsigned int startRange, unsigned int endRange){
    std::random_device seed;
    std::mt19937_64 generator(seed());                                              //generates the seed
    std::uniform_int_distribution<unsigned short> range(startRange, endRange);      //specifies the range
    return range(generator);                                                    //return a random number in the specified range
}