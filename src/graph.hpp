#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "list.hpp"

namespace grph{

template<typename DataType>
class Graph{
    private:
    size_t nodeCount;
    std::vector<std::vector<size_t>> adjacencyMatrix;
    std::vector <List<DataType>> adjacencyList;
    bool isDirected;
    
    public:
    explicit Graph(size_t initialNodeCount = 0, bool directed = false)
    :nodeCount(initialNodeCount)
    ,adjacencyMatrix(new size_t[this->nodeCount]()){
        if (this->adjacencyMatrix == nullptr) {
        throw std::runtime_error("no memory to create matrix");
        } else {
            for (int i = 0; i <= nodeCount; i++){
                if ((adjacencyMatrix[i] = new size_t[this->nodeCount]()) == NULL) {
                    
                }
            }
            
        }
    ,adjacencyList(new List<DataType>[this->nodeCount]()){
        if (this->adjacencyList == nullptr) {
            throw std::runtime_error("no memory to create adjacency list");
        }
    }
    ,isDirected(directed)
    }
    ~Graph() {
        /*
        for (size_t row = 0; row < nodeCount; ++row) {
            delete[] this->matrix[row];
        }
        */
        delete[] this->adjacencyMatrix;
        delete[] this->adjacencyList;
    }
    public:
    DataType& operator()(){

    }

    public:
    inline bool isEmpty(){
        return ((nodeCount ==0) ? true : false);
    }
    
    bool isAdjacent(x, y){

    }
    DataType& getNeighbors(x){

    }
    bool addVertex(x){

    }
    bool removeVertex(x){

    }
    bool addEdge(x, y, value){

    }
    bool removeEdge(x, y){

    }
    DataType& getEdge(x, y){

    }
    void setEdge(x, y, v){

    }*/
};
}//namespace grph
#endif // GRAPH_HPP
