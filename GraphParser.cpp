#include <iostream>
#include "GraphParser.h"

#define STRING_TO_ULONG(string) (strtoul(string.c_str(), nullptr, 10))

UndirectedCompleteGraph graphFromFile(const string& fileName){
    std::ifstream graphFile(fileName, std::ios::in);  //opens the file "fileName" in input mode

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
                boost::add_edge(matrixLine, matrixColumn, weight, graph);   //adds an edge to the adjacency matrix with the corresponding weight
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
        std::stringstream ss;
        ss << "The file '" << fileName << "' could not be open." << std::endl;       //throws and exception if the file could not be open
        throw std::runtime_error(ss.str());
    }
}