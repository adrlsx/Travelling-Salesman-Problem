#include "ConstructiveHeuristic.h"

void constructive(const string& fileName){
    UndirectedCompleteGraph graph = graphFromFile(fileName);

    vector<unsigned long> path;
    unordered_set<unsigned long> discoveredVertices;        //use of the unordered_set to verify if a specific vertex is already marked as discovered in constant time
    unsigned long distance = 0, minimumWeightFound, currentVertex = FIRST_VERTEX, nbVertices = boost::num_vertices(graph);

    path.push_back(currentVertex);
    discoveredVertices.insert(currentVertex);       //selects arbitrarily the first vertex and mark it as discovered

    while (discoveredVertices.size() != nbVertices) {       //while all vertices have not been discovered
        minimumWeightFound = MAX_VALUE;     //initialize the minimum weight found as the max possible value in order to replace it easily with a more optimal weigth

        nearestVertex(discoveredVertices, minimumWeightFound, currentVertex, graph);        //find the adjacent vertex with the minimum weight

        distance += minimumWeightFound;     //add the nearest vertex weight to the global distance
        path.push_back(currentVertex);      //adds the nearest vertex to the final path
        discoveredVertices.insert(currentVertex);       //then mark the following vertex as discovered
    }
    distance += getWeight(currentVertex, FIRST_VERTEX, graph);      //adds the last weight from the final vertex to the first one, in order to end the cycle

    resultToFile(path, distance, fileName, "constructive");     //prints out the result in a file
}

void nearestVertex(const unordered_set<unsigned long>& discoveredVertices, unsigned long& minimumWeightFound, unsigned long& currentVertex, const UndirectedCompleteGraph& graph){
    pair<adjacency_iterator, adjacency_iterator> adjacentVertices;
    unsigned long currentWeight, nextVertex = currentVertex;

    for (adjacentVertices = adjacent_vertices(currentVertex, graph);
         adjacentVertices.first != adjacentVertices.second; adjacentVertices.first++) {     //tests every adjacent vertex to the current vertex

        if (!discoveredVertices.contains(*adjacentVertices.first)) {        //if the adjacent vertex is not yet discovered
            currentWeight = getWeight(currentVertex, *adjacentVertices.first, graph);       //gets the distance between the current vertex and the adjacent vertex
            if (currentWeight < minimumWeightFound) {       //if the weight is smaller than the current minimum adjacent weight
                minimumWeightFound = currentWeight;     //then the minimum weight is equal to the adjacent weight
                nextVertex = *adjacentVertices.first;       //and the next vertex to add to the path is the current adjacent vertex
            }
        }

    }
    currentVertex = nextVertex;     //the nearest adjacent vertex becomes the current vertex
}


/*  Version in O(n^3) where we start from every vertex and only keep the best solution
 *
void constructive(const string& fileName){
    UndirectedCompleteGraph graph = graphFromFile(fileName);

    vector<unsigned long> finalPath, path;
    unordered_set<unsigned long> discoveredVertices;
    unsigned long finalDistance = MAX_VALUE, distance, minimumWeightFound, currentVertex, nbVertices = boost::num_vertices(graph);

    for(unsigned long i = 0; i < nbVertices; i++) {
        path.clear();
        discoveredVertices.clear();
        distance = 0;
        currentVertex = 0;
        path.push_back(currentVertex);
        discoveredVertices.insert(currentVertex);
        while (discoveredVertices.size() != nbVertices) {
            minimumWeightFound = MAX_VALUE;

            nearestVertex(discoveredVertices, minimumWeightFound, currentVertex, graph);

            distance += minimumWeightFound;
            path.push_back(currentVertex);
            discoveredVertices.insert(currentVertex);
        }
        distance += getWeight(currentVertex, 0, graph);
        if(distance < finalDistance){
            finalDistance = distance;
            finalPath = path;
        }
    }

    resultToFile(finalPath, finalDistance, fileName, "constructive");
}
 */