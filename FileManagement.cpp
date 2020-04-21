#include "FileManagement.h"

UndirectedCompleteGraph graphFromFile(const string& fileName){
    std::ifstream graphFile(fileName, ios::in);  //opens the file "fileName" in input mode

    if(graphFile.is_open()){
        string input;
        getline(graphFile, input);
        unsigned long nbVertices = STRING_TO_ULONG(input);     //first line represents the number of vertices in the graph

        UndirectedCompleteGraph graph(nbVertices);  //initialize and undirected graph with the right number of vertices

        unsigned long weight, matrixLine = 0, matrixColumn = 0;

        while (graphFile.good() && matrixLine <= nbVertices) {      //the loop stops if there is an error or an EOF flag or if the last line of the matrix is reached
            getline(graphFile, input, ' ');     //reads the next value from the file

            if(input != "0" && matrixColumn < nbVertices){     //an adjacency matrix is symmetric about its diagonal, which is filled with 0
                weight = STRING_TO_ULONG(input);
                boost::add_edge(matrixLine, matrixColumn, weight, graph);   //adds an edge to the adjacency matrix with the corresponding weight, corresponding vertices are automatically created
                matrixColumn++;
            }
            else{
                getline(graphFile,input);
                matrixColumn = 0;
                matrixLine++;
            }
        }
        graphFile.close();

        /*Code to make sure the graph is complete from https://www.technical-recipes.com/2015/getting-started-with-the-boost-graph-library/
         *
        typedef boost::graph_traits<UndirectedCompleteGraph>::edge_iterator edge_iterator;
        boost::property_map<UndirectedCompleteGraph, boost::edge_weight_t>::type EdgeWeightMap = get(boost::edge_weight_t(), graph);
        std::pair<edge_iterator, edge_iterator> edgePair;
        for (edgePair = edges(graph); edgePair.first != edgePair.second; ++edgePair.first){
            std::cout << *edgePair.first << " " << EdgeWeightMap[*edgePair.first] << std::endl;
        }
         */

        return graph;
    }
    else{
        stringstream ss;
        ss << "The file '" << fileName << "' could not be open.";       //throws and exception if the file could not be open
        throw std::runtime_error(ss.str());
    }
}


void resultToFile(const vector<unsigned long>& path, const unsigned long& distance, const string& fileName, const string& functionName){
    stringstream output(fileName);
    string smallerName;
    getline(output, smallerName, '.');      //removes the extension ".in" at the end of the file

    output.clear();
    output << smallerName << "_" << functionName + ".out";
    std::ofstream resultFile(output.str(), ios::out);      //creates the file "fileName_functionName.out"

    if(resultFile.is_open()){
        for (auto& it : path) {
            resultFile << it+1;     //adds 1 to each vertex because the vertex index in the result file should starts at 1, not at 0 like in C++
            if(it != *(path.end()-1)){      //avoids having the last space at the end of the line
                resultFile << " ";
            }
        }
        resultFile << endl << distance;
        resultFile.close();
    }
    else{
        stringstream ss;
        ss << "The file '" << output.str() << "' could not be created.";       //throws and exception if the file could not be created
        throw std::runtime_error(ss.str());
    }
}

unsigned long getWeight(const unsigned long& firstVertex, const unsigned long& secondVertex, const UndirectedCompleteGraph& graph){
    auto edgeWeightMap = boost::get(edge_weight_t(), graph);
    auto correspondingEdge = boost::edge(firstVertex, secondVertex, graph).first;
    return edgeWeightMap[correspondingEdge];
}