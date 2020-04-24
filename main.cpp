#include <iostream>
#include <chrono>
#include "OptionProcess.h"

#define GET_TIME std::chrono::high_resolution_clock::now();
#define EXECUTION_TIME(time1, time2) std::chrono::duration_cast<std::chrono::microseconds>((time2) - (time1)).count();

using std::exception;

int main(int argc, char** argv) {
    try{
        auto time1 = GET_TIME;

        processArguments(argc, argv);

        auto time2 = GET_TIME;
        double execTime = EXECUTION_TIME(time1, time2);
        std::cout << "Execution time:  " << execTime/1000000 << "s" << std::endl;

        return EXIT_SUCCESS;
    }
    catch(exception& e){
        std::cout << e.what() << std::endl << std::endl;
        printHelp();
        return EXIT_FAILURE;
    }
}