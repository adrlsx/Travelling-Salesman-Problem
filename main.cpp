#include <iostream>
#include <chrono>

#include "Exact/Source/ExactAlgorithm.h"
#include "Constructive/Source/ConstructiveHeuristic.h"

#define GET_TIME (std::chrono::high_resolution_clock::now());
#define EXECUTION_TIME(time1, time2) (std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count());

int main() {
    auto time1 = GET_TIME;
    constructive("1379.in");
    auto time2 = GET_TIME;
    double execTime = EXECUTION_TIME(time1, time2);
    std::cout << "Execution time:  " << execTime/1000000 << "s" << std::endl;
    return 0;
}
