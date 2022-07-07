// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <new>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Link.hpp"

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
  std::vector<std::vector<WeightType*>> adjacencyMatrix;
  // AdjacencyList is a list of Vertex that represents the adjancency of the vertexes
  /*std::vector<std::list<Link<DataType, WeightType>>*> adjacencyList;*/
  // Vertexes is a vector with all the vertex
  std::vector<Vertex<DataType>*> vertexes;
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
  adjacencyMatrix(capacity, std::vector<WeightType*>(capacity, nullptr)),
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
  adjacencyMatrix(other.adjacencyMatrix.size(),
  std::vector<WeightType*>(other.adjacencyMatrix.size(), nullptr)),
  vertexes(other.vertexes.size(), nullptr),
  isDirected(other.isDirected) {
    this->copyMatrixAndVertexes(other);
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
    other.adjacencyMatrix.clear();
    other.vertexes.clear();
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
    this->clear();
  }
  
 public:
  void clear() {
    this->deleteMatrix();
    this->deleteVertexes();
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
      // Delete this matrix
      this->deleteMatrix();
      // Delete this vertexes
      this->deleteVertexes();
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
      this->copyMatrixAndVertexes(other);
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
   * @return const size_t&
   */
  inline const size_t& getVertexCount() const {
    return this->vertexCount;
  }
  /**
   * @brief Get the Vertexes object
   * 
   * @return std::vector<Vertex<DataType>*>& 
   */
  inline std::vector<Vertex<DataType>*>&
  getVertexes() {
    return this->vertexes;
  }
  /**
   * @brief Get the Vertexes object
   * 
   * @return const std::vector<Vertex<DataType>*>& 
   */
  inline const std::vector<Vertex<DataType>*>&
  getVertexes() const {
    return this->vertexes;
  }

  /**
   * @brief operator() overload with constants
   * @param origin Vertex type of object that is the parting point of a link
   * @param connection Vertex type of object that is the destiny of the link
   *  
   * @return const WeightType& 
   */
  const WeightType& operator()(
    const Vertex<DataType>& origin,
    const Vertex<DataType>& connection) const {
      return *this->adjacencyMatrix[--this->whereIsVertex(origin)][
      --this->whereIsVertex(connection)];
  }

  /**
   * @brief operator() overload
   * @details see @a operator() for the origin and connection param
   * @see operator()
   * 
   * @return WeightType& 
   */
  WeightType& operator() (
    Vertex<DataType>& origin,
    Vertex<DataType>& connection) {
      return *this->adjacencyMatrix[this->whereIsVertex(origin)-1][
        this->whereIsVertex(connection)-1];
  }

  /**
   * @brief Tells if twp vertex are adjacent
   * @details see @a operator() for the origin and connection param
   * @see operator()
   * 
   * @return true 
   * @return false 
   */
  bool isAdjacent(
  Vertex<DataType>& origin,
  Vertex<DataType>& connection) {
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
    return this->adjacencyMatrix[originPosition][destinPosition] != nullptr;


    /*
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
    */
  }

  /**
   * @brief Get the Neighbors object
   * @details see @a operator() for the origin param
   * @see operator()
   * 
   * @return Vertex<DataType>** neighbors
   */
  Vertex<DataType>** getNeighbors(
  Vertex<DataType>& origin) {
    // Create a neighbors variable and assign a
    // new Vertex<DataType, WeightType>*[origin->getLinkCount()] to it
    Vertex<DataType>** neighbors =
    new Vertex<DataType>*[origin.getLinkCount()];
    // Variable to know when all the neighboors have been found
    // Counter to move throug vertex
    size_t neighborsFound = 0, vertex = 0,
    // variable to know the position of origin
    originPosition = this->whereIsVertex(origin);
    --originPosition;
    // Cycle that stores the neighboors from origin
    while (neighborsFound < origin.getLinkCount()
    && vertex < this->vertexCount) {
      if (this->adjacencyMatrix[originPosition][vertex]
      != nullptr) {
        neighbors[neighborsFound++] = this->vertexes[vertex];
      }
      ++vertex;
    }
    return neighbors;
  }

 private:
  /**
   * @brief Finds the position of the vertex 
   * @param vertex Vertex type of data which is the vertex which position we wanna know
   * 
   * @return size_t ++position
   */
  size_t whereIsVertex(const Vertex<DataType>& vertex) const {
    // Cycle that goes from 0 till the amount of vertex there are
    for (size_t position = 0; position < this->vertexCount; ++position) {
        // Condition in case the position is the same as the vertex param
        if (this->vertexes[position] == &vertex) {
          // Returns the position
          return position+1;
        }
    }
    return 0;
  }

 public:
  /**
   * @brief Adds a vertex to the graph
   * @details see @a whereIsVertex() for the param vertex
   * @see whereIsVertex()
   * 
   * @return true 
   * @return false 
   */
  bool addVertex(Vertex<DataType>& vertex) {
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
    this->vertexes[this->vertexCount++] =
    new Vertex<DataType>(vertex);

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
  bool removeVertex(Vertex<DataType>& vertex) {
    // Creates a variable and assigns the return value of whereIsVertex()
    size_t position = this->whereIsVertex(vertex);
    // Conditions if the vertex is not found
    if (position-- == 0) {
      return false;
    }
    // Remove any link from other vertex to this one
    findRemove(position);
    // Free the memory allocated for the vertex
    delete this->vertexes[position];
    // Erase the vertex from the vertexes vector
    this->vertexes.erase(this->vertexes.begin()+position);
    
    // Cycle that goes from 0 until the capacity is reached
    for (size_t row = 0; row < this->capacity; row++) {
      // Condition in case the row is different from the position
      if (row != position) {
        // Free the memory allocated for the links to the vertex (columns)
        delete this->adjacencyMatrix[row][position];
        // Erase the column on the current row and adjust the adjacency matrix
        this->adjacencyMatrix[row].erase(
          this->adjacencyMatrix[row].begin()+position);
      } else {
        for (size_t column = 0; column < this->capacity; column++) {
          // Free the memory allocated for the links from the vertex (row)
          delete this->adjacencyMatrix[row][column];
        }
      }
    }
    // Erase the position row and adjust the adjacency matrix
    this->adjacencyMatrix.erase(
     this->adjacencyMatrix.begin()+position);
    
    // Cycle that goes from 0 until the capacity is reached
    for (size_t row = 0; row < this->capacity; row++) {
      // Adds an element at the end of every row to mantain capacity
      this->adjacencyMatrix[row].push_back(nullptr);
    }
    // Adds a row at the end to mantain capacity
    this->adjacencyMatrix.push_back(
      std::vector<WeightType*> (this->capacity, nullptr));
    
    --this->vertexCount;
    // Deletes the links of the vertex
    vertex.getLinkCount() = 0;
    return true;

    /*// METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
        for (size_t i = 0; i < adjacencyList.size()+1; i++){
          nodeList node =  std::advance(listOfStrs.begin(), i);
          if (node.contents == vertex){
            adjacencyList.erase(node);
          }
        }
        return true;
      
    }
    // METHOD ADJACENCY LIST*/
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
  bool addLink(Vertex<DataType>& origin,
  Vertex<DataType>& connection,
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
    this->adjacencyMatrix[originPosition][destinPosition] =
    new WeightType;
    *this->adjacencyMatrix[originPosition][destinPosition] =
    weight;
    // Increases the link count
    ++origin.getLinkCount();
    // In case it is not directed
    if (!this->isDirected && &origin != &connection) {
      // Adds link
      this->adjacencyMatrix[destinPosition][originPosition] =
      new WeightType;
      *this->adjacencyMatrix[destinPosition][originPosition] =
      weight;
      // Increases the link count
      ++connection.getLinkCount();
    }
    return true;

    /*// METHOD ADJACENCY LIST
    for (size_t i = 0; i < this->vertexCount; i++){
      if (adjacencyList.begin().contents == origin){
        nodeList node<DataType, WeightType>(connection&,weight );
        adjacencyList.push_back(node);
        return true;
      }
    }
    // METHOD ADJACENCY LIST*/
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
  bool removeLink(Vertex<DataType>& origin,
  Vertex<DataType>& connection) {
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
    if (this->adjacencyMatrix[originPosition][destinPosition] == nullptr) {
      return true;
    }
    // Erase the link
    delete this->adjacencyMatrix[originPosition][destinPosition];
    this->adjacencyMatrix[originPosition][destinPosition] = nullptr;
    // Decreases the link count
    --origin.getLinkCount();
    
    // Condition if it is not directed
    if (!this->isDirected && &origin != &connection) {
      // Erase the link
      delete this->adjacencyMatrix[destinPosition][originPosition];
      this->adjacencyMatrix[destinPosition][originPosition] = nullptr;
      // Decreases the link count
      --connection.getLinkCount();
    }
    return false;

    /*// METHOD ADJACENCY LIST
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
    // METHOD ADJACENCY LIST*/
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
    Vertex<DataType>& origin,
    Vertex<DataType>& connection) {
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to get the Link");
    }

    if (this->adjacencyMatrix[originPosition][destinPosition] == nullptr) {
      throw std::runtime_error("Graph: Could not find Link to get it");
    }

    return *this->adjacencyMatrix[originPosition][destinPosition];

    /*// METHOD ADJACENCY LIST
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
    // METHOD ADJACENCY LIST*/
  }

  /**
   * @brief Set the Link object
   * 
   * @param origin 
   * @param connection 
   * @param weight 
   */
  void setLink(Vertex<DataType>& origin,
  Vertex<DataType>& connection,
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
    if (this->adjacencyMatrix[originPosition][destinPosition] == nullptr) {
      throw std::runtime_error("Graph: Could not find Link to set it");
    }

    // Assigns the weight to the link
    *this->adjacencyMatrix[originPosition][destinPosition] = weight;
    // Condition if it is not directed, then assigns the weight to the link
    if (!this->isDirected && &origin != &connection) {
      *this->adjacencyMatrix[destinPosition][originPosition] = weight;
    }

    /*// METHOD ADJACENCY LIST
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
    // METHOD ADJACENCY LIST*/
  }

 private:
  void copyMatrixAndVertexes(const Graph<DataType, WeightType>& other) {
    for (size_t row = 0; row < other.vertexCount;
    ++row) {
      for (size_t column = 0; column < other.vertexCount;
      ++column) {
        if (other.adjacencyMatrix[row][column]) {
          this->adjacencyMatrix[row][column] = new WeightType;
          *this->adjacencyMatrix[row][column] =
          *other.adjacencyMatrix[row][column];
        }
      }
      this->vertexes[row] =
      new Vertex<DataType>(*other.vertexes[row]);
    }
  }

 private:
  void deleteMatrix() {
    for (size_t row = 0; row < this->vertexCount;
    ++row) {
      for (size_t column = 0; column < this->vertexCount;
      ++column) {
        delete this->adjacencyMatrix[row][column];
        this->adjacencyMatrix[row][column] = nullptr;
      }
    }
  }

  void deleteVertexes() {
    for (size_t current = 0; current < this->vertexCount;
      ++current) {
        delete this->vertexes[current];
        this->vertexes[current] = nullptr;
    }
  }

 private:
  /**
   * @brief Increases the capacity of the graph
   * 
   * @param newCapacity is a size_t variable that will replace the value of the actual capacity of the graph
   */
  void increaseCapacity(size_t increaseFactor = 0) {
    // Conditions if the new capacity is 0, then the new capacity will
    // be the increase factor times the actual capacity
    if (increaseFactor == 0) {
      increaseFactor = INCREASE_FACTOR;
    }
     const size_t newCapacity = increaseFactor*this->capacity;
    
    // Cycle that goes from 0 until it reaches the max,
    // resizing the row of the adjacency matrix
    for (size_t row = 0; row < this->capacity; ++row) {
      this->adjacencyMatrix[row].resize(newCapacity, nullptr);
    }
    // Calls the resize() method
    this->adjacencyMatrix.resize(
      newCapacity, std::vector<WeightType*>(newCapacity, nullptr));

    // Resizes the vertexes
    this->vertexes.resize(newCapacity, nullptr);
    // Condition in case we could bot increase the capacity,
    // and then throws an exception

    if (!this->couldIncreaseCapacity(newCapacity)) {
      throw std::runtime_error(
        "Graph: No enough memory to increase capacity");
    }

    /*// METHOD ADJACENCY LIST
    adjacencyList.resize(newCapacity, std::vector<int>(newCapacity, 0));
    // METHOD ADJACENCY LIST*/

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

    /*// METHOD ADJACENCY LIST
    if (this->adjacencyList.size() != newCapacity) {
      return false;
    }
    // METHOD ADJACENCY LIST*/
  }

  /**
   * @brief Finds and removes the desired vertex
   * @details see @a whereIsVertex() for the param vertex
   * @see whereIsVertex()
   */
  void findRemove(size_t vertexPosition) {
    // Cycle that goes from 0 until it reaches the vertex count
    for (size_t current = 0; current < this->vertexCount; ++current) {
      // Conditions if the current vertex is the same as the param vertex
      if (current != vertexPosition) {
        if (this->adjacencyMatrix[current][vertexPosition]) {
          delete this->adjacencyMatrix[current][vertexPosition];
          this->adjacencyMatrix[current][vertexPosition] = nullptr;
          --this->vertexes[current]->getLinkCount();
        }
      }
    }
  }
  
};

}  // namespace grph

/*! @} End of Doxygen Groups*/
#endif  // GRAPH_HPP
