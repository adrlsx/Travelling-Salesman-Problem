#include <iostream>
#include "OptionProcess.h"
#include "UndirectedCompleteGraph.h"
#include "Grasp/Source/Grasp.h"
#include "Local_Search/Source/LocalSearchHeuristic.h"
#include "Constructive/Source/ConstructiveHeuristic.h"
#include "Exact/Source/ExactAlgorithm.h"

#define RCL_SIZE_DEFAULT 20
#define MAX_ITERATION_DEFAULT 5

using std::endl; using std::invalid_argument;
enum algorithm {EXACT, CONSTRUCTIVE_HEURISTIC, LOCAL_SEARCH, GRASP};

void printHelp() noexcept{
    std::cout << "For more information on this program, please refer to https://github.com/adrienls/Travelling-Salesman-Problem" << endl << endl << "Available options:" << endl <<
    "   -f, --file                                                Select the *.in instance to create the graph from" << endl <<
    "   -a, --algo  <exact, constructive, local_search, grasp>    Chose the algorithm to run" << endl <<
    "   -r, --rcl-size                                            Integer between 1 and the number of vertices in the graph. Default value is " << RCL_SIZE_DEFAULT << "." << endl <<
    "   -m, --max-iteration                                       Integer greater than or equal to 1. Default value is " << MAX_ITERATION_DEFAULT << "." << endl <<
    "   -h, --help:                                               Print Help (this message) and exit" << endl << endl;
}

void getArguments(const int argc, char* const* argv, argValues& input){
    if(argc < 2){
        throw invalid_argument("At least one argument is required.");
    }
    else if(argc > 9){
        throw invalid_argument("Too many arguments!");
    }

    const char* const shortOpts = "f:a:r:m:h";
    const struct option longOpts[] = {
            {"file", required_argument, nullptr, 'f'},
            {"algo", required_argument, nullptr, 'a'},
            {"rcl-size", required_argument, nullptr, 'r'},
            {"max-iteration", required_argument, nullptr, 'm'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    const map<char, string> options = arguments(argc, argv, shortOpts, longOpts);

    for(const auto& opt : options) {
        switch (opt.first) {
            case 'f':
                input.instance = opt.second;
                break;
            case 'a':
                if (opt.second == "grasp") {
                    input.algoChoice = GRASP;
                }
                else if (opt.second == "local_search") {
                    input.algoChoice = LOCAL_SEARCH;
                }
                else if (opt.second == "constructive") {
                    input.algoChoice = CONSTRUCTIVE_HEURISTIC;
                }
                else if (opt.second == "exact") {
                    input.algoChoice = EXACT;
                }
                else {
                    std::stringstream invalidArgument;
                    invalidArgument << opt.second << " is not a valid option. Please check the valid options.";
                    throw invalid_argument(invalidArgument.str());
                }
                break;
            case 'r':
                input.rclSize = stoul(opt.second);
                break;
            case 'm':
                input.maxIteration = stoul(opt.second);
                break;
            default:
                printHelp();
                break;
        }
    }
}

void processArguments(const int argc, char* const* argv){
    string algoName;
    argValues input = {"", -1, RCL_SIZE_DEFAULT, MAX_ITERATION_DEFAULT};
    getArguments(argc, argv, input);
    if(input.algoChoice == -1 || input.instance.empty()){
        throw invalid_argument("Invalid arguments were given.");
    }

    UndirectedCompleteGraph graph(input.instance);

    switch (input.algoChoice){
        case GRASP:
            grasp(graph, input.rclSize, input.maxIteration);
            algoName = "grasp";
            break;
        case LOCAL_SEARCH:
            localSearch(graph);
            algoName = "local_search";
            break;
        case CONSTRUCTIVE_HEURISTIC:
            constructive(graph);
            algoName = "constructive";
            break;
        case EXACT:
            exact(graph);
            algoName = "exact";
            break;
        default:
            throw std::runtime_error("Unknown algorithm to call.");
    }
    graph.pathToFile(algoName);     //prints out the result in a file
}