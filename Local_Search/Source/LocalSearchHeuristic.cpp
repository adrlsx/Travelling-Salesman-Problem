#include "LocalSearchHeuristic.h"
#include "../../Constructive/Source/ConstructiveHeuristic.h"

using std::reverse;

void localSearch(UndirectedCompleteGraph& graph){
    constructive(graph);
    vector<unsigned int> path = graph.getPath();

    unsigned int currentWeight, newWeight, minimumWeightFound, firstEdgeWeight, distance = MAX_VALUE;
    vector<unsigned int>::iterator vertexToSwap, iNext, jNext;

    while(graph.getDistance() < distance){      //repeat until no improvement is made
        for(auto i = path.begin(); i < path.end(); i++){        //for each vertex
            minimumWeightFound = MAX_VALUE;     //no minimum weight found yet, MAX_VALUE = infinite
            iNext = (i != path.end() - 1)? i+1 : path.begin();      //iNext is the following vertex, if i is the last vertex, iNext will point to the first one to end the cycle
            firstEdgeWeight = graph.getWeight(*i, *iNext);      //weight of the edge between i and iNext

            for(auto j = path.begin(); j < path.end(); j++){        //for each vertex to potentially swap
                jNext = (j != path.end() - 1)? j+1 : path.begin();      //same operation as for iNext
                if(j != i && j != iNext && jNext != i){     //makes sure the potential edges to swap are not identical or adjacent

                    currentWeight = firstEdgeWeight + graph.getWeight(*j, *jNext);      //weight of the 2 edges in the current path
                    newWeight = graph.getWeight(*i, *j) + graph.getWeight(*iNext, *jNext);      //new weight of the 2 edges if we swap them in the path

                    if(newWeight < currentWeight){      //if the new weight is smaller than the current weight then the swap is interesting
                        if(newWeight < minimumWeightFound){     //if the new weight is smaller than the best swap we have found
                            minimumWeightFound = newWeight;     //this edge becomes the new best edge to swap
                            vertexToSwap = jNext;       //iterator which points toward to vertex to swap
                        }
                    }
                }
            }
            if(minimumWeightFound != MAX_VALUE){        //if a interesting swap has been found
                (iNext < vertexToSwap)? reverse(iNext, vertexToSwap) : reverse(vertexToSwap, iNext);
                //applies the swap by reversing the path in the right order, reverse [smallest iterator, biggest iterator)
                //it reverses the path from the first iterator to the last iterator, it includes the first one but not the second one
                //if iterators are not in ascending order (second iterator bigger than first iterator) it does not do anything
            }
        }
        distance = graph.getDistance();     //gets the distance before it is updated
        graph.updatePath(path);     //update the final path and the final distance with the better one we just found
    }
}