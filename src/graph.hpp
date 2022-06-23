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
  bool isValued;

 public:
  explicit Graph(bool directed = false, bool valued = false)
  :vertexCount(0),
  adjacencyMatrix(),
  adjacencyList(),
  isDirected(directed),
  isValued(valued) {
  }

  // ~Graph() {
  // delete this->adjacencyMatrix;
  // delete this->adjacencyList;
  // }

 public:
  inline bool isEmpty() const {
    return this->vertexCount == 0;
  }
  size_t whereIsVertex(const DataType& vertex) const {
    for (size_t position = 0; position < this->vertexCount; position++) {
      if (!this->adjacencyList[position].isEmpty() &&
      this->adjacencyList[position].getHead() == vertex) {
        return ++position;
      }
    }
    return 0;
  }

 public:
  /*DataType& operator()() {

  }
  bool isAdjacent(x, y){

  }
  DataType& getNeighbors(x){

  }*/
  bool addVertex(const DataType& vertex) {
    if (this->whereIsVertex(vertex)) {
      return false;
    }
    for (size_t row = 0; row < this->vertexCount; row++) {
      this->adjacencyMatrix[row].push_back(0);
    }
    this->adjacencyMatrix.push_back(
      std::vector<__int16_t>(++this->vertexCount, 0));
    this->adjacencyList.push_back(
      grph::List<DataType, Valuetype>(vertex));
    return true;
  }
  bool removeVertex(const DataType& vertex) const {
    size_t position = this->whereIsVertex(vertex);
    if (position == 0) {
      return false;
    }
    this->adjacencyList.erase(
      this->adjacencyList.begin()+--position);
    this->adjacencyMatrix.erase(
      this->adjacencyMatrix.begin()+position);
    for (size_t row = 0; row < this->vertexCount; row++) {
      this->adjacencyMatrix[row].erase(
        this->adjacencyMatrix[row].begin()+position);
    }
    --this->vertexCount;
    return true;
  }
  /*bool addEdge(x, y, value){

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
