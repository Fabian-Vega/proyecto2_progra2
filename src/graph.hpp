// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

#include "vertex.hpp"

const size_t INITIAL_CAPACITY = 10;
const size_t INCREASE_FACTOR = 3;

namespace grph {

template<typename DataType, typename WeightType>
class Graph {
 private:
  size_t vertexCount;
  size_t capacity;
  std::vector<std::vector<__int16_t>> adjacencyMatrix;
  std::vector<Vertex<DataType, WeightType>*> vecters;
  bool isDirected;


 public:
  explicit Graph(size_t capacity = INITIAL_CAPACITY, bool directed = false)
  :vertexCount(0),
  capacity(capacity),
  adjacencyMatrix(capacity, std::vector<__int16_t>(capacity, 0)),
  vecters(capacity, nullptr),
  isDirected(directed) {
  }

 public:
  inline bool isEmpty() const {
    return this->vertexCount == 0;
  }

  /*friend const WeightType& operator()(
    const DataType& origin, const DataType& destination) const {
    return 
  }
  friend WeightType& operator()() {
  }*/

 private:
  size_t whereIsVertex(const Vertex& vertex) const {
    for (size_t position = 0; position < this->vertexCount; ++position) {
        if (this->vecters[position] != nullptr &&
          this->vecters[position] == &vertex) {
        return ++position;
      }
    }
    return 0;
  }

  size_t whereIsLink(const Vertex& origin, const Vertex& connection,) const {
    for (size_t position = 0; position < this->vecters[position]->linkCount; ++position) {
        if (this->vecters[position] != nullptr &&
          this->vecters[position] == &vertex) {
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
    if (this->whereIsVertex() != 0) {
      return false;
    }

    if (this->vertexCount >= this->capacity) {
      this->increaseCapacity();
    }

    this->Vecters[vertexCount++] = &vertex;
    return true;
  }

  bool removeVertex(const Vertex& vertex) const {
    size_t position = this->whereIsVertex(vertex);
    if (position-- == 0) {  
      return false;
    }

    findRemove(vertex);
    this->vecters.erase(this->vecters.begin()+position);
    --this->vertexCount;
    return true;
  }

  bool addLink(const Vertex& origin, const Vertex& connection,
  const WeightType& weight) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to add the link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition]) {
      return false;
    }

    Link<DataType, WeightType> link(&origin, weight, &connection);
    origin.linkVector.push_back(link);
    ++origin.linkCount;
    return true;
  }

  bool removeLink(const DataType& origin, const DataType& destination) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to remove the link");
    }

    if (!this->adjacencyMatrix[originPosition][destinPosition]) {
      return true;
    }

    
    return false;
  }

  const WeightType& getLink(
    const DataType& origin, const DataType& destination) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition == 0 || destinPosition == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to get the Link");
    }

    if (this->adjacencyMatrix[--originPosition][--destinPosition]) {
      throw std::runtime_error("Graph: Could not find Link to get it");
    }

    return this->adjacencyList[originPosition].getLinkValue(destination);
  }

  void setLink(const DataType& origin, const DataType& destination,
  const WeightType& value) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(destination);
    if (originPosition == 0 || destinPosition == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to set the Link");
    }

    if (this->adjacencyMatrix[--originPosition][--destinPosition]) {
      throw std::runtime_error("Graph: Could not find Link to set it");
    }

    this->adjacencyList[originPosition].setLinkValue(destination, value);
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

  void findRemove(Vertex& vertex) const {
    for (size_t current = 0; current < this->vertexCount; ++current) {
      if (this->vecters[current] != &vertex) {
        for (size_t connection = 0; 
        connection < this->vecters[current]->linkCount; ++connection) {
          if (this->vecters[current]->linkVector[connection]->connection == &vertex) {
            this->vecters[current]->linkVector.erase(
              this->vecters[current]->linkVector.begin()+connection);
          }
        }
      }
    }
  }

};

}  // namespace grph

#endif  // GRAPH_HPP