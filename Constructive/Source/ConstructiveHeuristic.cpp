#include "ConstructiveHeuristic.h"

void constructive(UndirectedCompleteGraph& graph){
    unsigned int vertex = FIRST_VERTEX, nbVertices = graph.getNbVertices();

    vector<bool> discoveredVertices(nbVertices, false);     //use of vector of bool to verify if a specific vertex is already marked as discovered in constant time

    while (graph.pathSize() != nbVertices) {        //while all vertices have not been discovered
        graph.updatePath(vertex);                   //adds the nearest vertex to the path and updates the distance
        discoveredVertices[vertex] = true;          //marks the vertex as discovered
        vertex = nearestVertex(vertex, discoveredVertices, graph);      //finds the adjacent vertex with the smallest weight and moves to it
    }
}

unsigned int nearestVertex(unsigned int vertex, const vector<bool>& discovered, const UndirectedCompleteGraph& graph){
    pair<adjacency_iterator, adjacency_iterator> adjacentVertices;
    unsigned int currentWeight, nextVertex = vertex, minimumWeightFound = MAX_VALUE;

    for (adjacentVertices = adjacent_vertices(vertex, graph.getGraph());
         adjacentVertices.first != adjacentVertices.second; adjacentVertices.first++) {     //tests every adjacent vertex to the current vertex

        if (!discovered[*adjacentVertices.first]) {        //if the adjacent vertex is not yet discovered

            currentWeight = graph.getWeight(vertex, *adjacentVertices.first);       //gets the distance between the current vertex and the adjacent vertex
            if (currentWeight < minimumWeightFound) {       //if the weight is smaller than the current minimum adjacent weight
                minimumWeightFound = currentWeight;     //then the minimum weight is equal to the adjacent weight
                nextVertex = *adjacentVertices.first;       //and the next vertex to add to the path is the current adjacent vertex
            }
        }
    }
    return nextVertex;     //the nearest adjacent vertex becomes the current vertex
}