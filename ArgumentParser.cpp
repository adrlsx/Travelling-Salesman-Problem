#include <sstream>
#include "ArgumentParser.h"

using std::pair; using std::stringstream; using std::invalid_argument;

map<char, string> arguments(const int& argc, char* const* const argv, const char* const shortOpts, const struct option longOpts[]) {
    int optionIndex = 0; //getopt_long stores the option index here
    int optionValue = getopt_long(argc, argv, shortOpts, longOpts, &optionIndex);

    map<char, string> options = {};

    while (optionValue != -1) {
        if (optionValue != 0) { //optionValue is 0 if a flag is set
            string arg = (optarg == nullptr) ? "" : optarg; //makes sure a valid string is added to the map
            options.insert(pair<char, string>(optionValue, arg));
        }
        optionValue = getopt_long(argc, argv, shortOpts, longOpts, &optionIndex);
    }

    if (optind < argc) {
        stringstream invalidArguments;
        invalidArguments << "Invalid value: '";
        //Saves any remaining command line argument in a stringstream (not options)
        invalidArguments << argv[optind];
        optind++;
        while (optind < argc) {
            invalidArguments << ", " << argv[optind];
            optind++;
        }
        invalidArguments << "' used in function arguments(). Invalid arguments were input, please check the valid arguments.";
        throw invalid_argument(invalidArguments.str());
    }
    return options;
}