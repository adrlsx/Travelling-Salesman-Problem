#include <random>
#include "Grasp.h"
#include "../../Local_Search/Source/LocalSearchHeuristic.h"
#include "../../Constructive/Source/ConstructiveHeuristic.h"

typedef boost::graph_traits<Graph>::adjacency_iterator adjacency_iterator;      //adjacency iterator type
using std::pair;

void grasp(UndirectedCompleteGraph& graph, unsigned int alpha, unsigned int improvedIteration, unsigned int graspMaxIteration, unsigned int localSearchMaxIteration){
    if(alpha < 0){
        throw std::invalid_argument("The quality criteria for the restricted candidate list cannot be smaller than one.");
    }
    if(improvedIteration < 1){
        throw std::invalid_argument("The number of improved iteration cannot be smaller than one.");
    }
    if(graspMaxIteration < 1){
        throw std::invalid_argument("The maximum number of iteration cannot be smaller than one.");
    }

    vector<unsigned int> finalPath;
    unsigned int finalDistance = MAX_VALUE;

    for(unsigned int i = 0, j = 0; i < improvedIteration && j < graspMaxIteration; i++, j++){          //repeat until no improvement is made
        greedyRandomizedConstruction(graph, alpha);      //construct a greedy randomized solution with a restricted candidate list of size alpha
        localSearch(graph, localSearchMaxIteration);     //locally improves the solution

        if(graph.getDistance() < finalDistance){            //saves the new path as the final path if its total distance is smaller than the current smallest distance
            finalDistance = graph.getDistance();
            finalPath = graph.getPath();
            i = 0;
        }
    }
    graph.updatePath(finalPath);                            //update the final path and the final distance with the best one we just found
}

void greedyRandomizedConstruction(UndirectedCompleteGraph& graph, unsigned int alpha){
    unsigned int vertex = lightestEdgeSource(graph.getGraph()), nbVertices = graph.getNbVertices();
    graph.clearPath();
    vector<bool> discoveredVertices(nbVertices, false);     //use of vector of bool to verify if a specific vertex is already marked as discovered in constant time

    while (graph.pathSize() != nbVertices) {        //while the path is not complete
        graph.updatePath(vertex);                   //adds the nearest vertex to the path and updates the distance
        discoveredVertices[vertex] = true;          //marks the vertex as discovered
        vertex = restrictedCandidateList(alpha, vertex, discoveredVertices, graph);      //gets a random vertex in the restricted candidate list and moves to it
    }
}

unsigned int restrictedCandidateList(unsigned int alpha, unsigned int vertex, const vector<bool>& discovered, const UndirectedCompleteGraph& graph){
    pair<adjacency_iterator, adjacency_iterator> adjacentVertices;
    vector<unsigned int> list;
    unsigned int currentWeight;
    float acceptableWeight = satisfyingCriteria(alpha, vertex, discovered, graph);          //gets the nearest vertex, return the same vertex if no adjacent vertex is available (all discovered);

    for (adjacentVertices = adjacent_vertices(vertex, graph.getGraph());
         adjacentVertices.first != adjacentVertices.second; adjacentVertices.first++) {     //tests every adjacent vertex to the current vertex

        if (!discovered[*adjacentVertices.first]) {                                         //if the adjacent vertex is not yet discovered
            currentWeight = graph.getWeight(vertex, *adjacentVertices.first);               //gets the distance between the current vertex and the adjacent vertex
            if ((float)currentWeight < acceptableWeight) {                                  //if the weight satisfies the given criteria
                list.push_back(*adjacentVertices.first);                                    //adds the the adjacent vertex in the RCL
            }
        }
    }
    if(!list.empty()){                                                          //if a vertex has been added in the restricted candidate list
        return list[randomCandidate(0, list.size() - 1)];   //returns a random candidate from the list
    }
    else{                                                                       //otherwise returns the input vertex
        return vertex;
    }
}

float satisfyingCriteria(unsigned int alpha, unsigned int vertex, const vector<bool>& discovered, const UndirectedCompleteGraph& graph){
    unsigned int bestVertex = nearestVertex(vertex, discovered, graph);
    unsigned int bestWeight = graph.getWeight(vertex, bestVertex);
    return (float)bestWeight * (1 + (float)alpha / 100);
}

unsigned int randomCandidate(unsigned int startRange, unsigned int endRange){
    std::random_device seed;
    std::mt19937_64 generator(seed());                                              //generates the seed
    std::uniform_int_distribution<unsigned short> range(startRange, endRange);      //specifies the range
    return range(generator);                                                    //return a random number in the specified range
}