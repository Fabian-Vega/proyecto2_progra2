// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <new>
#include <stdexcept>
#include <utility>
#include <vector>
#include "vertex.hpp"


const size_t INITIAL_CAPACITY = 10;
const size_t INCREASE_FACTOR = 3;

/*!
 *  \addtogroup grph
 *  @{
 */

//! Generic record interfaces and implementations
namespace grph {

/**
 * @brief Template for a default graph
 * @tparam DataType Specific type of data the vertex are going to use
 * @tparam WeightType Specific type of data the links of the graphs are going to use 
 */
template<typename DataType, typename WeightType, bool matrix = true>


/**
 * @brief class for the graph type of object
 * 
 */
class Graph {
 private:
  // VertexCount that stores the amount of vertex the graph contains
  size_t vertexCount;
  // Capacity is a variable that stores the capacity the graph contains
  size_t capacity;
  // AdjacencyMatrix is a matrix that represents the adjancency of the vertex
  std::vector<std::vector<int>> adjacencyMatrix;
  // AdjacencyList is a list of Vertex that represents the adjancency of the vertexes
  std::vector<list<nodeList<DataType, WeightType>>*> adjacencyList;
  // Vertexes is a vector with all the vertex
  std::vector<Vertex<DataType, WeightType>*> vertexes;
  // IsDirected is a bool that identifies if the links are directed or not
  bool isDirected;


 public:
  /**
   * @brief Construct a new Graph object
   * 
   * @param capacity size_t type of data that represents the capacity of the graph for nodes
   * @param directed bool type of data that represents if the links of the graphs will be directed or not
   */
  explicit Graph(size_t capacity = INITIAL_CAPACITY, bool directed = false)
  :vertexCount(0),
  capacity(capacity),
  adjacencyMatrix(capacity, std::vector<int>(capacity, 0)),
  vertexes(capacity, nullptr),
  isDirected(directed) {

  }
  /**
   * @brief Construct a new Graph object
   * 
   * @param other 
   */
  Graph(const Graph<DataType, WeightType>& other)
  :vertexCount(other.vertexCount),
  capacity(other.capacity),
  adjacencyMatrix(other.adjacencyMatrix),
  vertexes(other.vertexes),
  isDirected(other.isDirected) {
  }
  /**
   * @brief Construct a new Graph object
   * 
   * @param other 
   */
  Graph(Graph<DataType, WeightType>&& other)
  :vertexCount(other.vertexCount),
  capacity(other.capacity),
  adjacencyMatrix(std::move(other.adjacencyMatrix)),
  vertexes(std::move(other.vertexes)),
  isDirected(other.isDirected) {
    other.vertexCount = 0;
    other.capacity = 0;
    other.isDirected = false;
  }
  /**
   * @brief Destroy the Graph object
   * 
   */
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
  /**
   * @brief Operator= overload with constants
   * @param other A reference to a graph type of object 
   * 
   * @return Graph<DataType, WeightType>& 
   */
  Graph<DataType, WeightType>& operator=(const
  Graph<DataType, WeightType>& other) {
    // Conditions in case this is diferent from the other reference
    if (this != &other) {
      // Conditional in case the capacities are different
      if (this->capacity != other.capacity) {
        // Cycle that goes from 0 until it reaches
        // the size of the adjacency matrix and resizes it
        for (size_t column = 0; column < this->adjacencyMatrix.size();
        ++column) {
          this->adjacencyMatrix[column].resize(other.capacity);
        }
        // Resizing the adjacency Matrix and the vertexes
        this->adjacencyMatrix.resize(other.capacity);
        this->vertexes.resize(other.capacity);
        // Assign the new capacty
        this->capacity = other.capacity;
      }
      // Assigns new adjacency matrix, vertexes, vertex count
      // and the fact that if its directed or not
      this->adjacencyMatrix = other.adjacencyMatrix;
      this->vertexes = other.vertexes;
      this->vertexCount = other.vertexCount;
      this->isDirected = other.isDirected;
    }
    return *this;
  }
  /**
   * @brief Operator= overload
   * @details see @a operator= for the other param
   * 
   * @return Graph<DataType, WeightType>& 
   */
  Graph<DataType, WeightType>& operator=(Graph<DataType, WeightType>&& other) {
    if (this != &other) {
      // Swaps the vertex count, capacity, adjacency matrix, vertexes
      // and if it is directed or not from this to other
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
   * @brief returns true or false if the graph is empty or not
   * 
   * @return true 
   * @return false 
   */
  inline bool isEmpty() const {
    return this->vertexCount == 0;
  }
  /**
   * @brief Get the const Vertex Count object
   * 
   * @return size_t 
   */
  inline size_t getVertexCount() const {
    return this->vertexCount;
  }
  /**
   * @brief Get the Vertexes object
   * 
   * @return std::vector<Vertex<DataType, WeightType>*>& 
   */
  inline std::vector<Vertex<DataType, WeightType>*>&
  getVertexes() {
    return this->vertexes;
  }
  /**
   * @brief Get the Vertexes object
   * 
   * @return const std::vector<Vertex<DataType, WeightType>*>& 
   */
  inline const std::vector<Vertex<DataType, WeightType>*>&
  getVertexes() const {
    return this->vertexes;
  }

  /**
   * @brief operator() overload with constants
   * @param origin Pointer to a vertex type of object that is the parting point of a link
   * @param connection Pointer to a vertex type of object that is the destiny of the link
   *  
   * @return const WeightType& 
   */
  const WeightType& operator() (
    const Vertex<DataType, WeightType>* origin,
    const Vertex<DataType, WeightType>* connection) const {
      return origin->getLinkWeight(this->whereIsLink(origin, connection)-1);
  }

  /**
   * @brief operator() overload
   * @details see @a operator() for the origin and connection param
   * @details both params are pointers
   * @see operator()
   * 
   * @return WeightType& 
   */
  WeightType& operator()(
    Vertex<DataType, WeightType>* origin,
    Vertex<DataType, WeightType>* connection) {
      return origin->getLinkWeight(this->whereIsLink(origin, connection)-1);
  }

 private:
  /**
   * @brief Finds the position of the vertex 
   * @param vertex Vertex type of data which is the vertex which position we wanna know
   * 
   * @return size_t ++position
   */
  size_t whereIsVertex(const Vertex<DataType, WeightType>* vertex) const {
    // Cycle that goes from 0 till the amount of vertex there are
    for (size_t position = 0; position < this->vertexCount; ++position) {
        // Condition in case the position is the same as the vertex param
        if (this->vertexes[position] == vertex) {
          // Returns the position
          return ++position;
        }
    }
    return 0;
  }

  /**
   * @brief Finds the position of the link
   * @details see @a operator() for the origin and connection param
   * @details both param are const pointers
   * @see operator()
   * 
   * @return size_t 
   */
  size_t whereIsLink(const Vertex<DataType, WeightType>* origin,
  const Vertex<DataType, WeightType>* connection) const {
    // Cycle that goes from 0 till the amount of links there are
    for (size_t position = 0;
    position < origin->getLinkCount(); ++position) {
        // Condition in case the position is the same as the connection param
        if (origin->getLinkConnection(position) == connection) {
        // Returns the position
        return ++position;
      }
    }
    return 0;
  }

 public:
  /**
   * @brief Tells if twp vertex are adjacent
   * @details see @a operator() for the origin and connection param
   * @details both param are pointers
   * @see operator()
   * 
   * @return true 
   * @return false 
   */
  bool isAdjacent(
  Vertex<DataType, WeightType>* origin,
  Vertex<DataType, WeightType>* connection) {
    // Create and assign two size_t variables with the return value of
    // the whereIsvertex()
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    // Condition in case any of the position are equal to 0
    if (originPosition-- == 0 || destinPosition-- == 0) {
      // Return false in case the condition above is true
      return false;
    }
    // Returns the value of the following propositions
    return this->adjacencyMatrix[originPosition][destinPosition] != 0
    || this->adjacencyMatrix[destinPosition][originPosition] != 0;



    // METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
      if (adjacencyList.begin().contents == origin){
        for (size_t i = 0; i < adjacencyList.size()+1; i++){
          nodeList node =  std::advance(listOfStrs.begin(), i);
          if (node.contents == connection){
            return true
          }
        }
        return false;
      }
    }
    // METHOD ADJACENCY LIST
  }

  /**
   * @brief Get the Neighbors object
   * @details see @a operator() for the origin param
   * @details param is a pointer
   * @see operator()
   * 
   * @return Vertex<DataType, WeightType>** neighbors
   */
  Vertex<DataType, WeightType>** getNeighbors(
    Vertex<DataType, WeightType>* origin) {
      // Create a neighbors variable and assign a
      // new Vertex<DataType, WeightType>*[origin->getLinkCount()] to it
      Vertex<DataType, WeightType>** neighbors =
      new Vertex<DataType, WeightType>*[origin->getLinkCount()];
      // Cycle that goes from 0 until it reaches the amount of links
      for (size_t neighbor = 0; neighbor < origin->getLinkCount();
      ++neighbor) {
        neighbors[neighbor] = origin->getLinkConnection(neighbor);
      }

      return neighbors;
  }

  /**
   * @brief Adds a vertex to the graph
   * @details see @a whereIsVertex() for the param vertex
   * @see whereIsVertex()
   * 
   * @return true 
   * @return false 
   */
  bool addVertex(Vertex<DataType, WeightType>* vertex) {
    // Condition in case the vertex is not found
    if (this->whereIsVertex(vertex) != 0) {
      return false;
    }
    // Condition in case the amount of vertex is bigger than
    // the capacity, if so, increase the capacity
    if (this->vertexCount >= this->capacity) {
      this->increaseCapacity();
    }
    // Adds the vertex to the vertex list
    this->vertexes[this->vertexCount++] = vertex;
    return true;
  }

  /**
   * @brief Remove a vertex from the graph
   * @details see @a whereIsVertex() for the param vertex
   * @see whereIsVertex()
   *
   * @return true 
   * @return false 
   */
  bool removeVertex(Vertex<DataType, WeightType>* vertex) {
    // Creates a variable and assigns the return value of whereIsVertex()
    size_t position = this->whereIsVertex(vertex);
    // Conditions if the vertex is not found
    if (position-- == 0) {
      return false;
    }
    // Removes the vertex with the findRemove()
    findRemove(vertex);
    this->vertexes.erase(this->vertexes.begin()+position);
    --this->vertexCount;

    for (size_t row = 0; row < this->capacity; row++) {
      if (row != position) {
        this->adjacencyMatrix[row].erase(
          this->adjacencyMatrix[row].begin()+position);
      }
    }
    this->adjacencyMatrix.erase(
     this->adjacencyMatrix.begin()+position);
    
    for (size_t row = 0; row < this->capacity; row++) {
      this->adjacencyMatrix[row].push_back(0);
    }
    this->adjacencyMatrix.push_back(
      std::vector<int> (this->capacity));
    vertex->getLinkCount() = 0;
    vertex->getLinkVector().clear();
    return true;

    // METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
        for (size_t i = 0; i < adjacencyList.size()+1; i++){
          nodeList node =  std::advance(listOfStrs.begin(), i);
          if (node.contents == vertex){
            adjacencyList.erase(node);
          }
        }
        return true;
      
    }
    // METHOD ADJACENCY LIST
  }

  /**
   * @brief Adds a link from two vectors in the graph
   * @param weight Reference to a Weightype type of data which is the data that the link carries
   * @details see @a operator() for the origin and connection param
   * @details both param are pointers
   * @see operator()
   * 
   * @return true 
   * @return false 
   */
  bool addLink(Vertex<DataType, WeightType>* origin,
  Vertex<DataType, WeightType>* connection,
  WeightType& weight) {
    // Create and assign two size_t variables with
    // the return value of whereIsVertex()
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    // Condition if any of the positions are 0 if so, it throws an exception
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to add the link");
    }
    // Condition if the vertex are already connected, then returns false
    if (this->adjacencyMatrix[originPosition][destinPosition]) {
      return false;
    }
    // Adds link
    origin->getLinkVector().push_back(origin->createLink(weight, connection));
    // Increases the link count
    ++origin->getLinkCount();
    // Assigns adjacency
    this->adjacencyMatrix[originPosition][destinPosition] = 1;
    // In case it is not directed
    if (!this->isDirected) {
      // Adds link
      connection->getLinkVector().push_back(
      connection->createLink(weight, origin));
      // Increases the link count
      ++connection->getLinkCount();
      // Assigns adjacency
      this->adjacencyMatrix[destinPosition][originPosition] = 1;
    }
    return true;

    // METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
      if (adjacencyList.begin().contents == origin){
        nodeList node<DataType, WeightType>(connection&,weight );
        adjacencyList.push_back(node);
        return true;
      }
    }
    // METHOD ADJACENCY LIST
  }

  /**
   * @brief Removes a link from two vertexes and from the graph
   * @details see @a operator() for the origin and connection param
   * @details both param are pointers
   * @see operator()
   * 
   * @return true 
   * @return false 
   */
  bool removeLink(Vertex<DataType, WeightType>* origin,
  Vertex<DataType, WeightType>* connection) {
    // Create and assign two size_t variables with the
    // return value of whereIsVertex()
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    // Condition if any of the positions are 0 if so, it throws an exception
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to remove the link");
    }
    // Condition if the vertex are not already connected, then returns true
    if (!this->adjacencyMatrix[originPosition][destinPosition]) {
      return true;
    }
    // Erase the link
    origin->getLinkVector().erase(
      origin->getLinkVector().begin()+(
        this->whereIsLink(origin, connection)-1));
    // Decreases the link count
    --origin->getLinkCount();
    // Assigns that there is no adjacency
    this->adjacencyMatrix[originPosition][destinPosition] = 0;
    // Condition if it is not directed
    if (!this->isDirected) {
      // Erase the link
      connection->getLinkVector().erase(
        connection->getLinkVector().begin()+(
          this->whereIsLink(connection, origin)-1));
      // Decreases the link count
      --connection->getLinkCount();
      // Assigns that there is no adjacency
      this->adjacencyMatrix[destinPosition][originPosition] = 0;
    }
    return false;

    // METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
        if (adjacencyList.begin().contents == origin){
          for (size_t i = 0; i < adjacencyList.size()+1; i++){
            nodeList node =  std::advance(listOfStrs.begin(), i);
            if (node.contents == vertex){
              adjacencyList.erase(node);
            }
          }
          return true;
        }
      
    }
    // METHOD ADJACENCY LIST
  }

   /**
    * @brief Get the Link object
    * @details see @a operator() for the origin and connection param
    * @details both param are pointers
    * @see operator()
    * 
    * @return WeightType& origin->getLinkWeight(this->whereIsLink(origin, connection)-1)
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

    // METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
        if (adjacencyList.begin().contents == origin){
          for (size_t i = 0; i < adjacencyList.size()+1; i++){
            nodeList node =  std::advance(listOfStrs.begin(), i);
            if (node.contents == vertex){
              return node.weigth;
            }
          }
          
        }
      
    }
    // METHOD ADJACENCY LIST
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
    // Create and assign two size_t variables with the
    // return value of whereIsVertex()
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    // Condition if any of the positions are 0 if so, it throws an exception
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to set the Link");
    }
    // Condition if there is no adjacency, then throws an error
    if (this->adjacencyMatrix[originPosition][destinPosition] == 0) {
      throw std::runtime_error("Graph: Could not find Link to set it");
    }

    // METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
        bool found = false;
        if (adjacencyList.begin().contents == origin){
          for (size_t i = 0; i < adjacencyList.size()+1; i++){
            nodeList node =  std::advance(listOfStrs.begin(), i);
            if (node.contents == connection){
              found = true;
            }
          }
          if (found == false){
            throw std::runtime_error("Graph: Could not find Link to set it");
          }
        }
    }
    // METHOD ADJACENCY LIST


    // Assigns the weight to the link
    origin->getLinkWeight(this->whereIsLink(origin, connection)-1) = weight;
    // Condition if it is not directed, then assigns the weight to the link
    if (!this->isDirected) {
      connection->getLinkWeight(
        this->whereIsLink(connection, origin)-1) = weight;
    }
  }

 private:
  /**
   * @brief Increases the capacity of the graph
   * 
   * @param newCapacity is a size_t variable that will replace the value of the actual capacity of the graph
   */
  void increaseCapacity(size_t newCapacity = 0) {
    // Conditions if the new capacity is 0, then the new capacity will
    // be the increase factor times the actual capacity
    if (newCapacity == 0) {
      newCapacity = INCREASE_FACTOR * this->capacity;
    }
    // Calls the resize() method
    this->adjacencyMatrix.resize(
      newCapacity, std::vector<int>(newCapacity, 0));
    // Cycle that goes from 0 until it reaches the max,
    // resizing the row of the adjacency matrix
    for (size_t row = 0; row < this->vertexCount; row++) {
      this->adjacencyMatrix[row].resize(newCapacity, 0);
    }

    // METHOD ADJACENCY LIST
    adjacencyList.resize(newCapacity, std::vector<int>(newCapacity, 0));
   
    // METHOD ADJACENCY LIST
    // Resizes the vertexes
    this->vertexes.resize(newCapacity, nullptr);
    // Condition in case we could bot increase the capacity,
    // and then throws an exception

    if (!this->couldIncreaseCapacity(newCapacity)) {
      throw std::runtime_error(
        "Graph: No enough memory to increase capacity");
    }
    // Changes the capacity
    this->capacity = newCapacity;
  }

 private:
  /**
   * @brief Returns true in case the capacity could be increased, otherwise, returns false 
   * @details see @a increaseCapacity() for the newCapacity param
   * 
   * @return true 
   * @return false 
   */
  bool couldIncreaseCapacity(size_t newCapacity) const {
    // Condition if the size of the adjacency matrix is different
    // from new capacity, if so returns false
    if (this->adjacencyMatrix.size() != newCapacity) {
      return false;
    }
    // Cycle that goes from 0 until it reaches the new capacity
    for (size_t row = 0; row < newCapacity; row++) {
      // Condition if the size of the adjacency matrix row is different
      // from new capacity, if so returns false
      if (this->adjacencyMatrix[row].size() != newCapacity) {
        return false;
      }
    }

    return true;

    // METHOD ADJACENCY LIST
    if (this->adjacencyList.size() != newCapacity) {
      return false;
    }
    // METHOD ADJACENCY LIST
  }

  /**
   * @brief Finds and removes the desired vertex
   * @details see @a whereIsVertex() for the param vertex
   * @see whereIsVertex()
   */
  void findRemove(Vertex<DataType, WeightType>* vertex) {
    // Cycle that goes from 0 until it reaches the vertex count
    for (size_t current = 0; current < this->vertexCount; ++current) {
      // Conditions if the current vertex is the same as the param vertex
      if (this->vertexes[current] != vertex) {
        // Looks for a link from current to vertex
        size_t linkPosition = this->whereIsLink(
          this->vertexes[current], vertex);
        // If it finds a link
        if (linkPosition--) {
          // Erases the found link
          this->vertexes[current]->getLinkVector().erase(
            this->vertexes[current]->getLinkVector().begin() + linkPosition);
          --this->vertexes[current]->getLinkCount();
          this->adjacencyMatrix[current][linkPosition] = 0;
        }
      }
    }
  }
  

};

template<typename DataType, typename WeightType>
class nodeList {
  private:
  Vertex& contents;
  WeightType& weigth
public:
  explicit nodeList(const Vertex& contents, WeightType& weigth)
  :contents(contents),
  weigth(weigth) {
  }

  inline const WeightType& getWeigth() const {
    return this->weigth;
  }

  inline const Vertex& getVertex() const {
    return this->contents;
  }

};



}  // namespace grph
/*! @} End of Doxygen Groups*/
#endif  // GRAPH_HPP
