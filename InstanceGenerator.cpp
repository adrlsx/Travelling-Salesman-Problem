#include <fstream>
#include <iostream>
#include "InstanceGenerator.h"
#include "Grasp/Source/Grasp.h"

using std::endl; using std::stringstream;

void randomInstance(unsigned int nbVertices){
    if(nbVertices < 1){
        throw std::invalid_argument("The number of vertices cannot be smaller than one.");
    }
    unsigned int maxDistance = nbVertices * 10;
    vector<vector<unsigned int>> instance(nbVertices);
    for(auto& it : instance){
        it.resize(nbVertices);
    }
    unsigned int random;
    for(unsigned int i = 0; i < nbVertices; i++){
        for(unsigned int j = 0; j < nbVertices; j++){
            if(i != j){
                random = randomCandidate(1, maxDistance);
                instance[i][j] = random;
                instance[j][i] = random;
            }
            else{
                instance[i][j] = 0;
            }
        }
    }
    instanceFile(instance);
}

void instanceFile(vector<vector<unsigned int>> instance){
    stringstream fileName;
    fileName << instance.size() << ".in";
    std::ofstream resultFile(fileName.str(), std::ios::out);      //creates the file "fileName_functionName.out"

    if(resultFile.is_open()){
        resultFile << instance.size() << endl;
        for (auto line = instance.begin(); line != instance.end(); line++) {
            for(auto column = (*line).begin(); column != (*line).end(); column++){
                if(*column != 0){
                    resultFile << *column + 1;
                }
                else{
                    resultFile << *column;
                }
                if(column != (*line).end() - 1){
                    resultFile << " ";
                }
            }
            if(line != instance.end() - 1){
                resultFile << endl;
            }
        }
        resultFile.close();
        std::cout << "The file '" << fileName.str() << "' was successfully created." << endl;
    }
    else{
        stringstream ss;
        ss << "The file '" << fileName.str() << "' could not be created.";       //throws and exception if the file could not be created
        throw std::runtime_error(ss.str());
    }
}