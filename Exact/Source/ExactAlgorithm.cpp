#include "ExactAlgorithm.h"

void exact(UndirectedCompleteGraph& graph){
    vector<unsigned int> path;
    unsigned int distance = MAX_VALUE;     //initialize the distance with the maximum value and unsigned int can have
    vector<bool> discoveredVertices(graph.getNbVertices(), false);     //use of vector of bool to verify if a specific vertex is already marked as discovered in constant time

    backtracking(graph, path, distance, discoveredVertices);

    if(distance != MAX_VALUE){
        graph.updatePath(path);
    }
    else{
        throw std::runtime_error("No optimal path has been found by brute-force.");
    }
}
void backtracking(UndirectedCompleteGraph& graph, vector<unsigned int>& path, unsigned int& distance, vector<bool>& discoveredVertices){
    unsigned int nbVertices = graph.getNbVertices();
    for(unsigned int i = 0; i < nbVertices && graph.getDistance() < distance; i++){
        if(!discoveredVertices[i]){
            discoveredVertices[i] = true;
            graph.updatePath(i);
            backtracking(graph, path, distance, discoveredVertices);
        }
    }
    if(nbVertices == graph.pathSize()){
        unsigned int finalDistance = graph.getDistance();
        if(distance > finalDistance) {
            distance = finalDistance;
            path = graph.getPath();
        }
    }
    if(!graph.isPathEmpty()){
        discoveredVertices[graph.getPath().back()] = false;
        graph.removeLastVertex();
    }
}

/*
void exact(UndirectedCompleteGraph& graph){
    vector<unsigned int> finalPath, path;
    unsigned int finalDistance = MAX_VALUE, distance = 0, nbVertices = graph.getNbVertices();     //initialize the finalDistance with the maximum value and unsigned int can have

    for(unsigned int i = 0; i < nbVertices; i++){
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
        graph.updatePath(finalPath);
    }
    else{
        throw std::runtime_error("No optimal path has been found by brute-force.");
    }
}

unsigned int getDistanceFromPath(const vector<unsigned int>& path, const UndirectedCompleteGraph& graph){
    unsigned int distance = 0;
    auto lastVertex = path.end() - 1, firstVertex = path.begin();

    for (auto it = firstVertex; it != lastVertex; it++) {
        distance += graph.getWeight(*it, *(it+1));       //get the weight from each vertex to the next one
    }

    return distance + graph.getWeight(*lastVertex, *firstVertex);       //adds the weight from the last vertex to the first one to complete the cycle
}
*/