#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "list.hpp"

namespace grph{

template<typename DataType>
class Graph{
   private:
    size_t nodeCount;
    size_t* adjacencyMatrix;
    std::vector <List<DataType>> adjacencyList;
    bool isDirected;
    
 public:
  explicit Graph(size_t initialNodeCount = 0, bool direction = false)
  :nodeCount(initialNodeCount)
  ,adjacencyMatrix(new size_t[this->nodeCount]()){
    if (this->adjacencyMatrix == nullptr) {
      throw std::runtime_error("no memory to create dynamic array");
    }
  ,adjacencyList(new List<DataType>[this->nodeCount]()){
    if (this->adjacencyList == nullptr) {
      throw std::runtime_error("no memory to create dynamic array");
    }
  }
  ,isDirected(direction)
  }
  ~Graph() {
    delete[] this->adjacencyMatrix;
    delete[] this->adjacencyList;
  }
    /*public:
    DataType& operator()(){

    }

    public:
    inline bool isEmpty(){
        return (nodeCount ==0 ? true : false);
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
