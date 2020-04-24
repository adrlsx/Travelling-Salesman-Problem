#ifndef TRAVELLING_SALESMAN_PROBLEM_OPTIONPROCESS_H
#define TRAVELLING_SALESMAN_PROBLEM_OPTIONPROCESS_H

#include "ArgumentParser.h"

void printHelp() noexcept;
void getArguments(int argc, char* const* argv, string& instance, char& algo);
void processArguments(int argc, char* const* argv);

#endif //TRAVELLING_SALESMAN_PROBLEM_OPTIONPROCESS_H
