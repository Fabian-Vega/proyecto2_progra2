// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#include <vector>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "list.hpp"

namespace grph {

template<typename DataType, typename Valuetype>
class Graph {
 private:
  size_t vertexCount;
  std::vector<std::vector<__int16_t>> adjacencyMatrix;
  std::vector<grph::List<DataType, Valuetype>> adjacencyList;
  bool isDirected;

 public:
  explicit Graph(size_t vertexCount = 0, bool directed = false)
  :vertexCount(vertexCount),
  adjacencyMatrix(vertexCount, std::vector<__int16_t>(vertexCount)),
  adjacencyList(vertexCount, grph::List<DataType, Valuetype>()),
  isDirected(directed) {
  }

  // ~Graph() {
  // delete this->adjacencyMatrix;
  // delete this->adjacencyList;
  // }

 public:
  inline bool isEmpty() {
    return vertexCount == 0;
  }

 public:
  DataType& operator()() {

  }
  bool isAdjacent(x, y){

  }
  DataType& getNeighbors(x){

  }
  bool addVertex(DataType vertex){
    if (this->isVertexThere(vertex)) {
      return false;
    } else {
      
    }
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

  }
};

}  // namespace grph

#endif  // GRAPH_HPP
