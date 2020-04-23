#include <iostream>
#include "LocalSearchHeuristic.h"
#include <algorithm>

using std::reverse;
#define DIST(i, j) (graph.getWeight(path[i], path[j]))

void localSearch(UndirectedCompleteGraph& graph){
    constructive(graph);
    vector<unsigned int> path = graph.getPath();

    unsigned int currentWeight, newWeight, minimumWeightFound, vertexToSwap, pathSize = path.size();

    for(unsigned int i = 0; i < pathSize - 1; i++){

        minimumWeightFound = MAX_VALUE;
        vertexToSwap = MAX_VALUE;
        for(unsigned int j = 0; j < pathSize - 1; j++){
            if(j != i && j != i + 1 && j+1 != i && j+1 != i+1){

                currentWeight = DIST(i, i + 1) + DIST(j, j + 1);
                newWeight = DIST(i, j) + DIST(i + 1, j + 1);

                if(newWeight < currentWeight){
                   if(newWeight < minimumWeightFound){
                        minimumWeightFound = newWeight;
                        vertexToSwap = j+1;
                    }
                }
            }
        }
        if(vertexToSwap != MAX_VALUE){
            swap(i + 1, vertexToSwap, path);
        }
    }
    graph.updatePath(path);
}

void swap(const unsigned int firstVertexPosition, const unsigned int secondVertexPosition, vector<unsigned int>& path){
    /*unsigned int temp = path[firstVertexPosition];
    path[firstVertexPosition] = path[secondVertexPosition];
    path[secondVertexPosition] = temp;*/
    vector<unsigned int>::iterator firstIt, secondIt;
    for(firstIt = path.begin(); *firstIt != path[firstVertexPosition]; firstIt++);
    for(secondIt =path.begin(); *secondIt != path[secondVertexPosition]; secondIt++);
    reverse(firstIt, secondIt);
}