#include "ConstructiveHeuristic.h"
#include "../../FileManagement.h"

using std::vector;

void constructive(const string& fileName){
    UndirectedCompleteGraph graph = graphFromFile(fileName);

    vector<unsigned long> finalPath, path;
    unsigned long finalDistance = 0, distance = 0;

    

    resultToFile(finalPath, finalDistance, fileName, "constructive");
}