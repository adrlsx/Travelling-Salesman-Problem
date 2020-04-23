#include "LocalSearchHeuristic.h"

void localSearch(UndirectedCompleteGraph& graph){
    constructive(graph);
    vector<unsigned int> path = graph.getPath();

    unsigned int currentWeight, newWeight, minimumWeightFound;
    vector<unsigned int>::iterator vertexToSwap;

    for(auto i = path.begin(); i < path.end() - 1; i++){
        minimumWeightFound = MAX_VALUE;

        for(auto j = path.begin(); j < path.end() - 1; j++){
            if(j != i && j != (i+1) && (j+1) != i){

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
        if(minimumWeightFound != MAX_VALUE){
            reverse(i+1, vertexToSwap);
        }
    }
    graph.updatePath(path);
}