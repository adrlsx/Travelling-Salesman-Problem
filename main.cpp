#include <iostream>
#include <chrono>
#include "OptionProcess.h"

#define GET_TIME std::chrono::high_resolution_clock::now();
#define EXECUTION_TIME(time1, time2) std::chrono::duration_cast<std::chrono::microseconds>((time2) - (time1)).count();

using std::exception; using std::endl; using std::cout;

int main(int argc, char** argv) {
    try{
        auto time1 = GET_TIME;

        processArguments(argc, argv);

        auto time2 = GET_TIME;
        double execTime = EXECUTION_TIME(time1, time2);
        cout << "Execution time:  " << execTime/1000000 << "s" << endl;

        return EXIT_SUCCESS;
    }
    catch(exception& e){
        cout << endl << "Error: " << e.what() << endl << endl;
        printHelp();
        return EXIT_FAILURE;
    }
}