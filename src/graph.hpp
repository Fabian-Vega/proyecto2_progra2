// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdexcept>
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
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<Vertex<DataType, WeightType>*> vecters;
  bool isDirected;


 public:
  explicit Graph(size_t capacity = INITIAL_CAPACITY, bool directed = false)
  :vertexCount(0),
  capacity(capacity),
  adjacencyMatrix(capacity, std::vector<int>(capacity, 0)),
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
  size_t whereIsVertex(const Vertex<DataType, WeightType>& vertex) const {
    for (size_t position = 0; position < this->vertexCount; ++position) {
        if (this->vecters[position] != nullptr &&
          this->vecters[position] == &vertex) {
        return ++position;
      }
    }
    return 0;
  }

  size_t whereIsLink(const Vertex<DataType, WeightType>& origin,
  const Vertex<DataType, WeightType>& connection) const {
    for (size_t position = 0;
    position < origin.getLinkCount(); ++position) {
        if (origin.getLinkConnection(position) == &connection) {
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

  bool addVertex(Vertex<DataType, WeightType>& vertex) {
    if (this->whereIsVertex(vertex) != 0) {
      return false;
    }

    if (this->vertexCount >= this->capacity) {
      this->increaseCapacity();
    }

    this->vecters[vertexCount++] = &vertex;
    return true;
  }

  bool removeVertex(const Vertex<DataType, WeightType>& vertex) {
    size_t position = this->whereIsVertex(vertex);
    if (position-- == 0) {
      return false;
    }

    findRemove(vertex);
    this->vecters.erase(this->vecters.begin()+position);
    --this->vertexCount;
    return true;
  }

  bool addLink(Vertex<DataType, WeightType>& origin,
  Vertex<DataType, WeightType>& connection,
  WeightType& weight) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to add the link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition]) {
      return false;
    }

    origin.getLinkVector().push_back(origin.createLink(weight, &connection));
    ++origin.getLinkCount();
    this->adjacencyMatrix[originPosition][destinPosition] = 1;
    return true;
  }

  bool removeLink(Vertex<DataType, WeightType>& origin,
  const Vertex<DataType, WeightType>& connection) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to remove the link");
    }

    if (!this->adjacencyMatrix[originPosition][destinPosition]) {
      return true;
    }

    origin.linkVector.erase(
      origin.linkVector.begin()+(this->whereIsLink(origin, connection)-1));
    --origin.linkCount;
    this->adjacencyMatrix[originPosition][destinPosition] = 0;
    return false;
  }

  const WeightType& getLink(
    const Vertex<DataType, WeightType>& origin,
    const Vertex<DataType, WeightType>& connection) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to get the Link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition] == 0) {
      throw std::runtime_error("Graph: Could not find Link to get it");
    }

    // Esto falla
    return origin.getLinkWeight(this->whereIsLink(origin, connection)-1);
  }

  void setLink(Vertex<DataType, WeightType>& origin,
  const Vertex<DataType, WeightType>& connection,
  const WeightType& weight) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to set the Link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition]) {
      throw std::runtime_error("Graph: Could not find Link to set it");
    }

    origin.getLinkWeight(this->whereIsLink(origin, connection)-1) = weight;
  }

 private:
  void increaseCapacity(size_t newCapacity = 0) {
    if (newCapacity == 0) {
      newCapacity = INCREASE_FACTOR * this->capacity;
    }
    this->adjacencyMatrix.resize(
      newCapacity, std::vector<int>(newCapacity, 0));
    for (size_t row = 0; row < this->vertexCount; row++) {
      this->adjacencyMatrix[row].resize(newCapacity, 0);
    }

    if (!this->couldIncreaseCapacity(newCapacity)) {
      throw std::runtime_error(
        "Graph: No enough memory to increase capacity");
    }
    this->capacity = newCapacity;
  }

 private:
  bool couldIncreaseCapacity(size_t newCapacity) const {
    if (this->adjacencyMatrix.size() != newCapacity) {
      return false;
    }
    for (size_t row = 0; row < newCapacity; row++) {
      if (this->adjacencyMatrix[row].size() != newCapacity) {
        return false;
      }
    }

    return true;
  }

  void findRemove(Vertex<DataType, WeightType>& vertex) const {
    for (size_t current = 0; current < this->vertexCount; ++current) {
      if (this->vecters[current] != &vertex) {
        for (size_t connection = 0;
        connection < this->vecters[current]->linkCount; ++connection) {
          if (
    this->vecters[current]->linkVector[connection]->connection == &vertex) {
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
