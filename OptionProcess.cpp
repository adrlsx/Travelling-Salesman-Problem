#include <iostream>
#include "OptionProcess.h"
#include "UndirectedCompleteGraph.h"
#include "Grasp/Source/Grasp.h"
#include "Local_Search/Source/LocalSearchHeuristic.h"
#include "Constructive/Source/ConstructiveHeuristic.h"
#include "Exact/Source/ExactAlgorithm.h"
#include "InstanceGenerator.h"

#define RCL_QUALITY_DEFAULT 5
#define IMPROVED_ITERATION_DEFAULT 15
#define GRASP_MAX_ITERATION_DEFAULT 100
#define LOCAL_SEARCH_MAX_ITERATION_DEFAULT 100
#define GENERATOR_DEFAULT 15

using std::endl; using std::invalid_argument;
enum algorithm {EXACT, CONSTRUCTIVE_HEURISTIC, LOCAL_SEARCH, GRASP};

void printHelp() noexcept{
    std::cout << "For more information on this program, please refer to https://github.com/adrienls/Travelling-Salesman-Problem" << endl << endl << "Available options:" << endl <<
              "   -f, --file                                                Select the *.in instance to create the graph from" << endl <<
              "   -a, --algo  <exact, constructive, local_search, grasp>    Chose the algorithm to run" << endl <<
              "   -r, --rcl-quality                                         Positive percentage value. Default value is " << RCL_QUALITY_DEFAULT << "." << endl <<
              "   -i, --improved-iteration                                  Integer greater than or equal to 1. Default value is " << IMPROVED_ITERATION_DEFAULT << "." << endl <<
              "   -g, --grasp-max-iteration                                 Integer greater than or equal to 1. Default value for GRASP is " << GRASP_MAX_ITERATION_DEFAULT << "." << endl <<
              "   -l, --local-search-max-iteration                          Integer greater than or equal to 1. Default value for Local Search is " << LOCAL_SEARCH_MAX_ITERATION_DEFAULT << "." << endl <<
              "   -n, --new-instance                                        Integer greater than or equal to 1. Default value is " << GENERATOR_DEFAULT << "." << endl <<
              "   -h, --help:                                               Print Help (this message) and exit" << endl << endl;
}

void getArguments(const int argc, char* const* argv, argValues& input){
    if(argc < 2){
        throw invalid_argument("At least one argument is required.");
    }

    const char* const shortOpts = "f:a:r:i:g:l:n:h";
    const struct option longOpts[] = {
            {"file", required_argument, nullptr, 'f'},
            {"algo", required_argument, nullptr, 'a'},
            {"rcl-quality", required_argument, nullptr, 'r'},
            {"improved-iteration", required_argument, nullptr, 'i'},
            {"grasp-max-iteration", required_argument, nullptr, 'g'},
            {"local-search-max-iteration", required_argument, nullptr, 'l'},
            {"new-instance", required_argument, nullptr, 'n'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    const map<char, string> options = arguments(argc, argv, shortOpts, longOpts);

    for(const auto& opt : options) {
        switch (opt.first) {
            case 'f':
                if(opt.second.empty()){
                    throw invalid_argument("You need to specify the file name.");
                }
                input.instance = opt.second;
                break;
            case 'a':
                if(opt.second.empty()){
                    throw invalid_argument("You need to specify the algorithm to run.");
                }
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
                if(!opt.second.empty()){
                    input.rclQuality = stoul(opt.second);
                }
                break;
            case 'i':
                if(!opt.second.empty()){
                    input.improvedIteration = stoul(opt.second);
                }
                break;
            case 'g':
                if(!opt.second.empty()){
                    input.graspMaxIteration = stoul(opt.second);
                }
                break;
            case 'l':
                if(!opt.second.empty()){
                    input.localSearchMaxIteration = stoul(opt.second);
                }
                break;
            case 'n':
                if(!opt.second.empty()){
                    input.generateInstance = true;
                    input.nbVertices = stoul(opt.second);
                }
                break;
            default:
                printHelp();
                break;
        }
    }
}

void processArguments(const int argc, char* const* argv){
    string algoName;
    argValues input = {"", -1, RCL_QUALITY_DEFAULT, IMPROVED_ITERATION_DEFAULT, GRASP_MAX_ITERATION_DEFAULT, LOCAL_SEARCH_MAX_ITERATION_DEFAULT, false, GENERATOR_DEFAULT};
    getArguments(argc, argv, input);
    if(input.generateInstance){
        randomInstance(input.nbVertices);
    }

    if(!input.instance.empty()){
        UndirectedCompleteGraph graph(input.instance);

        switch (input.algoChoice){
            case GRASP:
                grasp(graph, input.rclQuality, input.improvedIteration, input.graspMaxIteration, input.localSearchMaxIteration);
                algoName = "grasp";
                break;
            case LOCAL_SEARCH:
                localSearch(graph, input.localSearchMaxIteration);
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
}