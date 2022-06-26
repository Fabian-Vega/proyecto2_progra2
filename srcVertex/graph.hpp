// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

#include "list.hpp"

const size_t INITIAL_CAPACITY = 10;
const size_t INCREASE_FACTOR = 3;

namespace grph {

template<typename DataType, typename Valuetype>
class Graph {
 private:
  size_t vertexCount;
  size_t capacity;
  std::vector<std::vector<__int16_t>> adjacencyMatrix;
  std::vector<List<DataType, Valuetype>> Vecters;
  bool isDirected;

  private:
  class Vertex{
   public:
    Datatype             data;
    size_t               connectionCounter;
    std::vector<Edge*>   connectionArray;

   public:
    explicit Vertex(const Datatype& data,size_t connectionCounter = INITIAL_CAPACITY ,
    std::vector<Edge*> connectionArray = nullptr)
    :data(data),
    connectionCounter(connectionCounter),
    connectionArray(connectionCounter),
    {
    }

    Vertex(const Datatype& data,size_t connectionCounter = INITIAL_CAPACITY ,
    std::vector<Edge*> connectionArray = nullptr)
    :data(data),
    connectionCounter(connectionCounter),
    connectionArray(connectionCounter),
    {
    }
  };


 public:
  explicit Graph(size_t capacity = INITIAL_CAPACITY, bool directed = false)
  :vertexCount(0),
  capacity(capacity),
  adjacencyMatrix(capacity, std::vector<__int16_t>(capacity, 0)),
  Vecters(capacity),
  isDirected(directed) {
  }

  // ~Graph() {
  // delete this->adjacencyMatrix;
  // delete this->adjacencyList;
  // }

 public:
  inline bool isEmpty() const {
    return this->vertexCount == 0;
  }

  /*friend const Valuetype& operator()(
    const DataType& origin, const DataType& destination) const {
    return 
  }
  friend Valuetype& operator()() {
  }*/

 private:
  size_t whereIsVertex(const Vertex& vertex) const {
    for (size_t position = 0; position < this->vertexCount; ++position){
        if (!(this->Vecters[position].head.vecter == nullptr) &&
          this->&Vecters[position].head.vecter == &vertex) {
        return ++position;
      }
    }
    return 0;
  }

 public:
  /*bool isAdjacent(x, y) {
  }
  DataType& getNeighbors(x) {
  }*/

  bool addVertex(const Vertex& vertex) {
    if (this->whereIsVertex() -1) {
      return false;
    }

    if (this->vertexCount == this->capacity) {
      this->increaseCapacity();
    }

    this->vertexCount++;
    Vecters[vertexCount].head.vecter = vertex;
    return true;
  }

  bool removeVertex(const Vertex& vertex) const {
    size_t position = this->whereIsVertex(vertex);
    if (position-- == 0) {  
      return false;
    }

    findRemove(vertex);
    Vecters.erase(position,position++);
    --this->vertexCount;
    
    
    return true;
  }

  void findRemove( Vertex& vertex) const {
    for (size_t i = 0; i < vertexCount; i++){
       removeConnection( Vecters[i],vertex);
    }
  }
  void removeConnection(nodeList*  head,Vertex& vertex ){
      while (head.next != nullptr){
          if(head& == vertex&){
              (head.previous).next = (head.next);
              (head.next).previous = (head.previous);
          }
      }
      

  }

///////////////////////////////////////////////////////////////////////////////////////////////////
  bool addEdge(const Vertex& origin, const Vertex& destination,
  const Valuetype& value) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition == 0 || destinPosition == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to add the edge");
    }

    if (this->adjacencyMatrix[--originPosition][--destinPosition]) {
      return false;
    }

    if (origin == destination) {
      this->
      this->adjacencyList[originPosition].setEdgeValue(origin, value);
      this->adjacencyMatrix[originPosition][originPosition] = 2;
    } else {
      this->adjacencyList[originPosition].append(destination, value);
      this->adjacencyMatrix[originPosition][destinPosition] = 1;
    }
    return true;
  }

  bool removeEdge(const DataType& origin, const DataType& destination) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition == 0 || destinPosition == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to remove the edge");
    }

    if (this->adjacencyMatrix[--originPosition][--destinPosition]) {
      return false;
    }

    if (origin != destination) {
      this->adjacencyList[originPosition].remove(destination);
    }
    this->adjacencyMatrix[originPosition][originPosition] = 0;
    return true;
  }

  const Valuetype& getEdge(
    const DataType& origin, const DataType& destination) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition == 0 || destinPosition == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to get the edge");
    }

    if (this->adjacencyMatrix[--originPosition][--destinPosition]) {
      throw std::runtime_error("Graph: Could not find edge to get it");
    }

    return this->adjacencyList[originPosition].getEdgeValue(destination);
  }

  void setEdge(const DataType& origin, const DataType& destination,
  const Valuetype& value) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition == 0 || destinPosition == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to set the edge");
    }

    if (this->adjacencyMatrix[--originPosition][--destinPosition]) {
      throw std::runtime_error("Graph: Could not find edge to set it");
    }

    this->adjacencyList[originPosition].setEdgeValue(destination, value);
  }

 private:
  void increaseCapacity(size_t newCapacity = 0) {
    if (newCapacity == 0) {
      newCapacity = INCREASE_FACTOR * this->capacity;
    }
    this->adjacencyMatrix.resize(
      newCapacity, std::vector<__int16_t>(newCapacity, 0));
    for (size_t row = 0; row < this->vertexCount; row++) {
      this->adjacencyMatrix[row].resize(newCapacity, 0);
    }

    this->adjacencyList.resize(
      newCapacity);

    if (!this->couldIncreaseCapacity(newCapacity)) {
      throw std::runtime_error(
        "Graph: No enough memory to increase capacity");
    }
    this->capacity = newCapacity;
  }

 private:
  bool couldIncreaseCapacity(size_t newCapacity) const {
    if (this->adjacencyList.size() != newCapacity ||
    this->adjacencyMatrix.size() != newCapacity) {
      return false;
    }
    for (size_t row = 0; row < newCapacity; row++) {
      if (this->adjacencyMatrix[row].size() != newCapacity) {
        return false;
      }
    }

    return true;
  }
};

}  // namespace grph

#endif  // GRAPH_HPP