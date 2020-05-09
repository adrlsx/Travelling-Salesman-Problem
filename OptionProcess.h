#ifndef TRAVELLING_SALESMAN_PROBLEM_OPTIONPROCESS_H
#define TRAVELLING_SALESMAN_PROBLEM_OPTIONPROCESS_H

#include "ArgumentParser.h"

typedef struct argValues{
    string instance;
    char algoChoice;
    unsigned int rclQuality;
    unsigned int improvedIteration;
    unsigned int graspMaxIteration;
    unsigned int localSearchMaxIteration;
    bool generateInstance;
    unsigned int nbVertices;
} argValues;

void printHelp() noexcept;
void getArguments(int argc, char* const* argv, argValues& input);
void processArguments(int argc, char* const* argv);

#endif //TRAVELLING_SALESMAN_PROBLEM_OPTIONPROCESS_H
