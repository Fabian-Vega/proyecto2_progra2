// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <new>
#include <stdexcept>
#include <vector>
#include "vertex.hpp"


const size_t INITIAL_CAPACITY = 10;
const size_t INCREASE_FACTOR = 3;

namespace grph {

/**
 * @brief Template for a default graph
 * @tparam DataType Specific type of data the vertex are going to use
 * @tparam WeightType Specific type of data the links of the graphs are going to use 
 */
template<typename DataType, typename WeightType>

/**
 * @brief 
 * 
 */
class Graph {
 private:
  size_t vertexCount;
  size_t capacity;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<Vertex<DataType, WeightType>*> vertexes;
  bool isDirected;


 public:
  /**
   * @brief Construct a new Graph object
   * 
   * @param capacity size_t type of data
   * @param directed 
   */
  explicit Graph(size_t capacity = INITIAL_CAPACITY, bool directed = false)
  :vertexCount(0),
  capacity(capacity),
  adjacencyMatrix(capacity, std::vector<int>(capacity, 0)),
  vertexes(capacity, nullptr),
  isDirected(directed) {
  }

    Graph(const Graph<DataType, WeightType>& other)
  :vertexCount(other.vertexCount),
  capacity(other.capacity),
  adjacencyMatrix(other.adjacencyMatrix),
  vertexes(other.vertexes),
  isDirected(other.isDirected) {
  }

  Graph(Graph<DataType, WeightType>&& other)
  :vertexCount(other.vertexCount),
  capacity(other.capacity),
  adjacencyMatrix(other.adjacencyMatrix),
  vertexes(other.vertexes),
  isDirected(other.isDirected) {
    other.vertexCount = 0;
    other.capacity = 0;
    other.isDirected = false;
  }

  ~Graph() {
    this->vertexCount = 0;
    this->capacity = 0;
    this->isDirected = false;
    for (size_t column = 0; column < this->adjacencyMatrix.size();
    ++column) {
      this->adjacencyMatrix[column].clear();
    }
    this->adjacencyMatrix.clear();
    this->vertexes.clear();
  }

 public:
  Graph<DataType, WeightType>& operator=(const
  Graph<DataType, WeightType>& other) {
  if (this != &other) {
    if (this->capacity != other.capacity) {
      for (size_t column = 0; column < this->adjacencyMatrix.size();
      ++column) {
      this->adjacencyMatrix[column].resize(other.capacity);
      }
      this->adjacencyMatrix.resize(other.capacity);
      this->vertexes.resize(other.capacity);
      this->capacity = other.capacity;
    }

    this->adjacencyMatrix = other.adjacencyMatrix;
    this->vertexes = other.vertexes;
    this->vertexCount = other.vertexCount;
    this->isDirected = other.isDirected;
  }
  return *this;
}

 Graph<DataType, WeightType>& operator=(Graph<DataType, WeightType>&& other) {
  if (this != &other) {
    std::swap(this->vertexCount, other.vertexCount);
    std::swap(this->capacity, other.capacity);
    std::swap(this->adjacencyMatrix, other.adjacencyMatrix);
    std::swap(this->vertexes, other.vertexes);
    std::swap(this->isDirected, other.isDirected);
  }
  return *this;
 }

 public:
  /**
   * @brief 
   * 
   * @return true 
   * @return false 
   */
  inline bool isEmpty() const {
    return this->vertexCount == 0;
  }

  inline size_t getVertexCount() const {
    return this->vertexCount;
  }

  inline const std::vector<Vertex<DataType, WeightType>*>&
  getVertexes() const {
    return this->vertexes;
  }
  
  /**
   * @brief 
   * 
   * @param origin 
   * @param connection 
   * @return const WeightType& 
   */
  const WeightType& operator() (
    const Vertex<DataType, WeightType>* origin,
    const Vertex<DataType, WeightType>* connection) const {
      return origin->getLinkWeight(this->whereIsLink(origin, connection)-1);
  }

  /**
   * @brief 
   * 
   * @param origin 
   * @param connection 
   * @return WeightType& 
   */
  WeightType& operator()(
    Vertex<DataType, WeightType>* origin,
    Vertex<DataType, WeightType>* connection) {
      return origin->getLinkWeight(this->whereIsLink(origin, connection)-1);
  }

 private:
  /**
   * @brief 
   * 
   * @param vertex 
   * @return size_t 
   */
  size_t whereIsVertex(const Vertex<DataType, WeightType>* vertex) const {
    for (size_t position = 0; position < this->vertexCount; ++position) {
        if (this->vertexes[position] == vertex) {
        return ++position;
      }
    }
    return 0;
  }

  /**
   * @brief 
   * 
   * @param origin 
   * @param connection 
   * @return size_t 
   */
  size_t whereIsLink(const Vertex<DataType, WeightType>* origin,
  const Vertex<DataType, WeightType>* connection) const {
    for (size_t position = 0;
    position < origin->getLinkCount(); ++position) {
        if (origin->getLinkConnection(position) == connection) {
        return ++position;
      }
    }
    return 0;
  }

 public:
  /**
   * @brief 
   * 
   * @param origin 
   * @param connection 
   * @return true 
   * @return false 
   */
  bool isAdjacent(
  Vertex<DataType, WeightType>* origin,
  Vertex<DataType, WeightType>* connection) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      return false;
    }

    return this->adjacencyMatrix[originPosition][destinPosition] != 0
    || this->adjacencyMatrix[destinPosition][originPosition] != 0;
 
  }

  /**
   * @brief Get the Neighbors object
   * 
   * @param origin 
   * @return Vertex<DataType, WeightType>** 
   */
  Vertex<DataType, WeightType>** getNeighbors(
    Vertex<DataType, WeightType>* origin) {
      Vertex<DataType, WeightType>** neighbors = 
      new Vertex<DataType, WeightType>*[origin->getLinkCount()];
      for (size_t neighbor = 0; neighbor < origin->getLinkCount();
      ++neighbor) {
        neighbors[neighbor] = origin->getLinkConnection(neighbor);
      }

      return neighbors;
  }

  /**
   * @brief 
   * 
   * @param vertex 
   * @return true 
   * @return false 
   */
  bool addVertex(Vertex<DataType, WeightType>* vertex) {
    if (this->whereIsVertex(vertex) != 0) {
      return false;
    }

    if (this->vertexCount >= this->capacity) {
      this->increaseCapacity();
    }
    
    this->vertexes[this->vertexCount++] = vertex;
    return true;
  }

  /**
   * @brief 
   * 
   * @param vertex 
   * @return true 
   * @return false 
   */
  bool removeVertex(Vertex<DataType, WeightType>* vertex) {
    size_t position = this->whereIsVertex(vertex);
    if (position-- == 0) {
      return false;
    }

    findRemove(vertex);
    this->vertexes.erase(this->vertexes.begin()+position);
    --this->vertexCount;
    return true;
  }

  /**
   * @brief 
   * 
   * @param origin 
   * @param connection 
   * @param weight 
   * @return true 
   * @return false 
   */
  bool addLink(Vertex<DataType, WeightType>* origin,
  Vertex<DataType, WeightType>* connection,
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

    origin->getLinkVector().push_back(origin->createLink(weight, connection));
    ++origin->getLinkCount();
    this->adjacencyMatrix[originPosition][destinPosition] = 1;

    if (!this->isDirected) {
      connection->getLinkVector().push_back(
        connection->createLink(weight, origin));
    ++connection->getLinkCount();
    this->adjacencyMatrix[destinPosition][originPosition] = 1;
    }
    return true;
  }

  /**
   * @brief 
   * 
   * @param origin 
   * @param connection 
   * @return true 
   * @return false 
   */
  bool removeLink(Vertex<DataType, WeightType>* origin,
  const Vertex<DataType, WeightType>* connection) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to remove the link");
    }

    if (!this->adjacencyMatrix[originPosition][destinPosition]) {
      return true;
    }

    origin->getLinkVector().erase(
      origin->getLinkVector().begin()+(this->whereIsLink(origin, connection)-1));
    --origin->getLinkCount();
    this->adjacencyMatrix[originPosition][destinPosition] = 0;

    if (!this->isDirected) {
      connection->getLinkVector().erase(
      connection->getLinkVector().begin()+(this->whereIsLink(connection, origin)-1));
    --connection->getLinkCount();
    this->adjacencyMatrix[destinPosition][originPosition] = 0;
    }
    return false;
  }

   /**
    * @brief Get the Link object
    * 
    * @param origin 
    * @param connection 
    * @return WeightType& 
    */
   WeightType& getLink(
    Vertex<DataType, WeightType>* origin,
    Vertex<DataType, WeightType>* connection) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to get the Link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition] == 0) {
      throw std::runtime_error("Graph: Could not find Link to get it");
    }

    return origin->getLinkWeight(this->whereIsLink(origin, connection)-1);
  }

  /**
   * @brief Set the Link object
   * 
   * @param origin 
   * @param connection 
   * @param weight 
   */
  void setLink(Vertex<DataType, WeightType>* origin,
  Vertex<DataType, WeightType>* connection,
  WeightType& weight) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to set the Link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition] == 0) {
      throw std::runtime_error("Graph: Could not find Link to set it");
    }

    origin->getLinkWeight(this->whereIsLink(origin, connection)-1) = weight;
    if (!this->isDirected) {
      connection->getLinkWeight(this->whereIsLink(connection, origin)-1) = weight;
    }
  }

 private:
  /**
   * @brief 
   * 
   * @param newCapacity 
   */
  void increaseCapacity(size_t newCapacity = 0) {
    if (newCapacity == 0) {
      newCapacity = INCREASE_FACTOR * this->capacity;
    }
    this->adjacencyMatrix.resize(
      newCapacity, std::vector<int>(newCapacity, 0));
    for (size_t row = 0; row < this->vertexCount; row++) {
      this->adjacencyMatrix[row].resize(newCapacity, 0);
    }

    this->vertexes.resize(newCapacity, nullptr);

    if (!this->couldIncreaseCapacity(newCapacity)) {
      throw std::runtime_error(
        "Graph: No enough memory to increase capacity");
    }
    this->capacity = newCapacity;
  }

 private:
  /**
   * @brief 
   * 
   * @param newCapacity 
   * @return true 
   * @return false 
   */
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

  /**
   * @brief 
   * 
   * @param vertex 
   */
  void findRemove(Vertex<DataType, WeightType>* vertex) {
    for (size_t current = 0; current < this->vertexCount; ++current) {
      if (this->vertexes[current] != vertex) {
        for (size_t connection = 0;
        connection < this->vertexes[current]->getLinkCount(); ++connection) {
          if (
    this->vertexes[current]->getLinkConnection(connection) == vertex) {
            this->vertexes[current]->getLinkVector().erase(
              this->vertexes[current]->getLinkVector().begin()+connection);
          }
        }
      }
    }
  }
};

}  // namespace grph

#endif  // GRAPH_HPP
