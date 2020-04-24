#include "UndirectedCompleteGraph.h"

UndirectedCompleteGraph::UndirectedCompleteGraph(const string &fileName) : fileName(fileName), graph(matrixSize()), distance(0) {
    std::ifstream graphFile(fileName, ios::in);  //opens the file "fileName" in input mode

    if(graphFile.is_open()){
        string input;
        getline(graphFile, input);     //first line represents the number of vertices in the graph

        unsigned int weight, matrixLine = 0, matrixColumn = 0;

        while (graphFile.good() && matrixLine <= this->nbVertices) {      //the loop stops if there is an error or an EOF flag or if the last line of the matrix is reached
            getline(graphFile, input, ' ');     //reads the next value from the file

            if(input != "0" && matrixColumn < this->nbVertices){     //an adjacency matrix is symmetric about its diagonal, which is filled with 0
                weight = STRING_TO_ULONG(input);
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
        throw std::runtime_error(ss.str());
    }
}

unsigned int UndirectedCompleteGraph::matrixSize(){
    std::ifstream graphFile(this->fileName, ios::in);  //opens the file "fileName" in input mode

    if(graphFile.is_open()){
        string input;
        getline(graphFile, input);
        this->nbVertices = STRING_TO_ULONG(input);     //first line represents the number of vertices in the graph

        graphFile.close();
        return this->nbVertices;
    }
    else{
        stringstream ss;
        ss << "The file '" << this->fileName << "' could not be open.";       //throws and exception if the file could not be open
        throw std::runtime_error(ss.str());
    }
}

void UndirectedCompleteGraph::pathToFile(const string& functionName) const{
    stringstream output(this->fileName);
    string smallerName;
    getline(output, smallerName, '.');      //removes the extension ".in" at the end of the file

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
    }
    else{
        stringstream ss;
        ss << "The file '" << output.str() << "' could not be created.";       //throws and exception if the file could not be created
        throw std::runtime_error(ss.str());
    }
}
void UndirectedCompleteGraph::removeLastVertex() {
    if(!this->path.empty()){
        this->distance -= this->getWeight(*(this->path.rbegin()), *(this->path.rbegin() - 1));
        this->path.pop_back();       //removes the last vertex from the path
    }
    else{
        throw std::invalid_argument("The last vertex could not be removed to the path, as it is already empty.");       //throws and exception if the path is already full
    }
}

void UndirectedCompleteGraph::updatePath(unsigned int vertex){
    if(this->pathSize() <= this->getNbVertices()){
        if(!this->path.empty()){
            this->distance += this->getWeight(*(this->path.rbegin()), vertex);
        }
        this->path.push_back(vertex);       //adds the vertex to the path
    }
    else{
        stringstream ss;
        ss << "The vertex '" << vertex << "' could not be added to the path, as it is already full.";       //throws and exception if the path is already full
        throw std::invalid_argument(ss.str());
    }
}
void UndirectedCompleteGraph::updatePath(const vector<unsigned int>& newPath) {
    if(newPath.size() <= this->getNbVertices()){
        this->path = newPath;       //updates the path to the new one
        this->distance = 0;
        auto lastVertex = this->path.end() - 1, firstVertex = this->path.begin();
        for (auto it = firstVertex; it != lastVertex; it++) {       //calculate the new distance corresponding to the new path
            this->distance += this->getWeight(*it, *(it+1));       //get the weight from each vertex to the next one
        }
    }
    else{
        stringstream ss;
        ss << "The new path is too big to replace the old one.";       //throws and exception if the new path is too big
        throw std::invalid_argument(ss.str());
    }
}

unsigned int UndirectedCompleteGraph::getWeight(unsigned int firstVertex, unsigned int secondVertex) const{
    auto edgeWeightMap = boost::get(edge_weight_t(), this->graph);      //maps edges with their corresponding weight
    Edge correspondingEdge = boost::edge(firstVertex, secondVertex, this->graph).first;
    return edgeWeightMap[correspondingEdge];
}
unsigned int UndirectedCompleteGraph::getWeight(const Edge& edge) const{
    unsigned int source = boost::source(edge, this->graph), target = boost::target(edge, this->graph);
    return this->getWeight(source, target);
}

unsigned int UndirectedCompleteGraph::getDistance() const{
    unsigned int lastVertex = *(this->path.rbegin()), firstVertex = *(this->path.begin());
    return this->distance + this->getWeight(lastVertex, firstVertex);       //gets the distance and add the distance from the last vertex to the first one to finish the cycle
}