// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "list.hpp"

namespace grph {

template<typename DataType, typename Valuetype>
class Graph {
 private:
  size_t nodeCount;
  std::vector<std::vector<__int16_t>> adjacencyMatrix;
  std::vector<grph::List<DataType, Valuetype>> adjacencyList;
  bool isDirected;

 public:
  explicit Graph(size_t nodeCount = 0, bool directed = false)
  :nodeCount(nodeCount),
  adjacencyMatrix(nodeCount, std::vector<__int16_t>(nodeCount)),
  adjacencyList(nodeCount, grph::List<DataType, Valuetype>()),
  isDirected(directed) {
  }

  ~Graph() {
  // delete this->adjacencyMatrix;
  // delete this->adjacencyList;
  }

  /* public:
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

}  // namespace grph

#endif  // GRAPH_HPP
