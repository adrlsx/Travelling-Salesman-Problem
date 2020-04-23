#include <iostream>
#include <chrono>

#include "UndirectedCompleteGraph.h"
#include "Exact/Source/ExactAlgorithm.h"
#include "Constructive/Source/ConstructiveHeuristic.h"
#include "Local_Search/Source/LocalSearchHeuristic.h"

#define GET_TIME (std::chrono::high_resolution_clock::now());
#define EXECUTION_TIME(time1, time2) (std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count());

int main() {
    auto time1 = GET_TIME;

    UndirectedCompleteGraph graph("Local_Search/Instances/5915.in");
    localSearch(graph);
    graph.pathToFile("local_search");     //prints out the result in a file

    auto time2 = GET_TIME;
    double execTime = EXECUTION_TIME(time1, time2);
    std::cout << "Execution time:  " << execTime/1000000 << "s" << std::endl;

    return EXIT_SUCCESS;
}
