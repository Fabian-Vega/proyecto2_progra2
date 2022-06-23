#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP
#endif // GRAPH_HPP

/*
Class Graph
attributes:
size_t                  nodeCount
size_t*                 adjacencyMatrix
vector <List<DataType>> adjacencyList 
bool                    isDirected
bool       
*/

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

  
  
};