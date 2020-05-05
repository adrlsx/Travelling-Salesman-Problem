#include <fstream>
#include <iostream>
#include "UndirectedCompleteGraph.h"

using std::endl; using std::stringstream; using std::ios; using std::invalid_argument; using std::runtime_error;

UndirectedCompleteGraph::UndirectedCompleteGraph(const string &fileName) : fileName(fileName), graph(matrixSize()), distance(0) {
    std::ifstream graphFile(fileName, ios::in);  //opens the file "fileName" in input mode

    if(graphFile.is_open()){
        string input;
        getline(graphFile, input);     //first line represents the number of vertices in the graph

        unsigned int weight, matrixLine = 0, matrixColumn = 0;

        while (graphFile.good() && matrixLine <= this->nbVertices) {      //the loop stops if there is an error or an EOF flag or if the last line of the matrix is reached
            getline(graphFile, input, ' ');     //reads the next value from the file

            if(input != "0" && matrixColumn < this->nbVertices){     //an adjacency matrix is symmetric about its diagonal, which is filled with 0
                weight = stoul(input);
                boost::add_edge(matrixLine, matrixColumn, weight, this->graph);   //adds an edge to the adjacency matrix with the corresponding weight, corresponding vertices are automatically created
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
    }
    else{
        stringstream ss;
        ss << "The file '" << fileName << "' could not be open.";       //throws and exception if the file could not be open
        throw runtime_error(ss.str());
    }
}

unsigned int UndirectedCompleteGraph::matrixSize(){
    std::ifstream graphFile(this->fileName, ios::in);  //opens the file "fileName" in input mode

    if(graphFile.is_open()){
        string input;
        getline(graphFile, input);
        this->nbVertices = stoul(input);     //first line represents the number of vertices in the graph

        graphFile.close();
        return this->nbVertices;
    }
    else{
        stringstream ss;
        ss << "The file '" << this->fileName << "' could not be open.";       //throws and exception if the file could not be open
        throw runtime_error(ss.str());
    }
}

void UndirectedCompleteGraph::pathToFile(const string& functionName) const{
    unsigned int pos = this->fileName.find_last_of('.');
    string smallerName = this->fileName.substr(0, pos);        //removes the extension ".in" at the end of the file
    stringstream output(smallerName);

    output.clear();
    output << smallerName << "_" << functionName + ".out";
    std::ofstream resultFile(output.str(), ios::out);      //creates the file "fileName_functionName.out"

    if(resultFile.is_open()){
        for (auto& it : this->path) {
            resultFile << it+1;     //adds 1 to each vertex because the vertex index in the result file should starts at 1, not at 0 like in C++
            if(it != *(this->path.end()-1)){      //avoids having the last space at the end of the line
                resultFile << " ";
            }
        }
        resultFile << endl << this->getDistance();
        resultFile.close();
        std::cout << "The file '" << output.str() << "' was successfully created." << endl;
    }
    else{
        stringstream ss;
        ss << "The file '" << output.str() << "' could not be created.";       //throws and exception if the file could not be created
        throw runtime_error(ss.str());
    }
}
void UndirectedCompleteGraph::removeLastVertex() {
    if(!this->path.empty()){
        if(this->pathSize() > 1){
            this->distance -= this->getWeight(this->path.back(), *(this->path.rbegin()+1));
        }
        else{
            this->distance = 0;
        }
        this->path.pop_back();       //removes the last vertex from the path
    }
    else{
        throw invalid_argument("The last vertex could not be removed to the path, as it is already empty.");       //throws and exception if the path is already full
    }
}

void UndirectedCompleteGraph::updatePath(unsigned int vertex){
    if(this->pathSize() <= this->getNbVertices()){
        if(!path.empty()){
            this->distance += this->getWeight(this->path.back(), vertex);
        }
        this->path.push_back(vertex);       //adds the vertex to the path
    }
    else{
        stringstream ss;
        ss << "The vertex '" << vertex << "' could not be added to the path, as it is already full.";       //throws and exception if the path is already full
        throw invalid_argument(ss.str());
    }
}
void UndirectedCompleteGraph::updatePath(const vector<unsigned int>& newPath) {
    if(newPath.size() <= this->getNbVertices()){
        this->path = newPath;       //updates the path to the new one
        this->distance = 0;
        if(!newPath.empty()){
            auto lastVertex = this->path.end() - 1, firstVertex = this->path.begin();
            for (auto it = firstVertex; it != lastVertex; it++) {       //calculate the new distance corresponding to the new path
                this->distance += this->getWeight(*it, *(it+1));       //get the weight from each vertex to the next one
            }
        }
    }
    else{
        throw invalid_argument("The new path is too big to replace the old one.");      //throws and exception if the new path is too big
    }
}
void UndirectedCompleteGraph::clearPath() {
    this->path.clear();
    this->distance = 0;
}

unsigned int UndirectedCompleteGraph::getWeight(unsigned int firstVertex, unsigned int secondVertex) const{
    if(firstVertex < this->nbVertices && secondVertex < this->nbVertices){
        auto edgeWeightMap = boost::get(edge_weight_t(), this->graph);      //maps edges with their corresponding weight
        Edge correspondingEdge = boost::edge(firstVertex, secondVertex, this->graph).first;
        return edgeWeightMap[correspondingEdge];
    }
    else if(firstVertex == secondVertex){
        return 0;
    }
    else{
        throw invalid_argument("The given vertex was too big and was not found in the graph.");       //throws and exception if a vertex is not in the graph
    }
}
unsigned int UndirectedCompleteGraph::getWeight(const Edge& edge) const{
    unsigned int source = boost::source(edge, this->graph), target = boost::target(edge, this->graph);
    return this->getWeight(source, target);
}

unsigned int UndirectedCompleteGraph::getDistance() const{
    if(this->pathSize() > 1){
        unsigned int lastVertex = this->path.back(), firstVertex = this->path.front();
        return this->distance + this->getWeight(lastVertex, firstVertex);       //gets the distance and add the distance from the last vertex to the first one to finish the cycle
    }
    else{
        return 0;
    }
}