#include <iostream>
#include "OptionProcess.h"
#include "UndirectedCompleteGraph.h"
#include "Grasp/Source/Grasp.h"
#include "Local_Search/Source/LocalSearchHeuristic.h"
#include "Constructive/Source/ConstructiveHeuristic.h"
#include "Exact/Source/ExactAlgorithm.h"

using std::endl, std::invalid_argument;
enum algorithm {EXACT, CONSTRUCTIVE_HEURISTIC, LOCAL_SEARCH, GRASP};

void printHelp() noexcept{
    std::cout << "For more information on this program please refer to https://github.com/adrienls/Travelling-Salesman-Problem" << endl <<
    "   -f, --file                                                   Select the *.in instance to create the graph from" << endl <<
    "   -a, --algo  <exact, constructive, local_search, grasp>:      Chose the algorithm to run" << endl <<
    "   -h, --help:                                                  Print Help (this message) and exit" << endl << endl;
}

void getArguments(const int argc, char* const* argv, string& instance, char& algo){
    if(argc < 2){
        throw invalid_argument("At least one argument is required.");
    }
    else if(argc > 5){
        throw invalid_argument("Too many arguments!");
    }

    const char* const shortOpts = "f:a:h";
    const struct option longOpts[] = {
            {"file", required_argument, nullptr, 'f'},
            {"algo", required_argument, nullptr, 'a'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    const map<char, string> options = arguments(argc, argv, shortOpts, longOpts);

    for(const auto& opt : options) {
        switch (opt.first) {
            case 'f':
                instance = opt.second;
                break;
            case 'a':
                if (opt.second == "grasp") {
                    algo = GRASP;
                }
                else if (opt.second == "local_search") {
                    algo = LOCAL_SEARCH;
                }
                else if (opt.second == "constructive") {
                    algo = CONSTRUCTIVE_HEURISTIC;
                }
                else if (opt.second == "exact") {
                    algo = EXACT;
                }
                else {
                    std::stringstream invalidArgument;
                    invalidArgument << opt.second << " is not a valid option. Please check the valid options.";
                    throw invalid_argument(invalidArgument.str());
                }
                break;
            default:
                printHelp();
                break;
        }
    }
    if(algo == -1 || instance.empty()){
        throw invalid_argument("Invalid arguments were given.");
    }
}

void processArguments(const int argc, char* const* argv){
    string instance, algoName;
    char algo = -1;
    getArguments(argc, argv, instance, algo);

    UndirectedCompleteGraph graph(instance);

    switch (algo){
        case GRASP:
            grasp(graph);
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