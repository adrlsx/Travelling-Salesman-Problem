#include <iostream>
#include "ExactAlgorithm.h"

#define MAX_VALUE (std::numeric_limits<unsigned long>::max())

void exact(const string& fileName){
    UndirectedCompleteGraph graph = graphFromFile(fileName);
    vector<unsigned long> finalPath, path;
    unsigned long finalDistance = MAX_VALUE, distance = 0, nbVertices = boost::num_vertices(graph);     //initialize the finalDistance with the maximum value and unsigned long can have

    for(unsigned long i = 1; i <= nbVertices; i++){
        path.push_back(i);      //initialize the path with the first lexicographic combination (vertices in ascending order)
    }

    do{
        distance = getDistanceFromPath(path, graph);

        if(distance < finalDistance){       //saves the new permutation as the final path if its total distance is smaller than the current smallest distance
            finalDistance = distance;
            finalPath = path;
        }
    } while(std::next_permutation(path.begin(), path.end()));       //makes the next permutation in lexicographical order

    if(finalDistance != MAX_VALUE){
        resultToFile(finalPath, finalDistance, fileName, "exact");
    }
    else{
        throw std::runtime_error("No optimal path has been found with the exact algorithm.");
    }
}

unsigned long getDistanceFromPath(const vector<unsigned long>& path, const UndirectedCompleteGraph& graph){
    unsigned long distance = 0, indexOfLastVertex = path.size() - 1;

    for (unsigned long i = 0; i < indexOfLastVertex; i++) {     //all values from the path are -1 because the vertex index in the graph starts at 0 not at 1
        distance += getWeight(path[i] - 1, path[i+1] - 1, graph);       //get the weight from each vertex to the next one
    }
    distance += getWeight(path[indexOfLastVertex] - 1, path[0] - 1, graph);        //adds the weight from the last vertex to the first one to complete the cycle

    return distance;
}