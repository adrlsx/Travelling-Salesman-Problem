#ifndef TRAVELLING_SALESMAN_PROBLEM_ARGUMENTPARSER_H
#define TRAVELLING_SALESMAN_PROBLEM_ARGUMENTPARSER_H

#include <map>
#include <string>
#include <getopt.h>

using std::map, std::string;

map<char, string> arguments(const int& argc, char* const* argv, const char* shortOpts, const struct option longOpts[]);

#endif //TRAVELLING_SALESMAN_PROBLEM_ARGUMENTPARSER_H
