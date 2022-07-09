// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <new>
#include <stdexcept>
#include <utility>
#include <vector>

#include "link.hpp"

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
  typedef std::vector<std::vector<WeightType*>> matrixType;
  typedef std::list<Link<DataType, WeightType>> listType;
  typedef std::vector<Vertex<DataType>*> vertexesType;

 private:
  // VertexCount that stores the amount of vertex the graph contains
  size_t vertexCount;
  // Capacity is a variable that stores the capacity the graph contains
  size_t capacity;
  // AdjacencyMatrix is a matrix that represents the adjancency of the vertex
  matrixType adjacencyMatrix;
  // AdjacencyList is a list of Vertex
  // that represents the adjancency of the vertexes
  std::vector<listType*> adjacencyList;
  // Vertexes is a vector with all the vertex
  vertexesType vertexes;
  // IsDirected is a bool that identifies if the links are directed or not
  bool isDirected;


 public:
  /**
   * @brief Default constructor
   * 
   * @param capacity size_t type of data that represents the capacity of the graph for nodes
   * @param directed bool type of data that represents if the links of the graphs will be directed or not
   */
  explicit Graph(size_t capacity = INITIAL_CAPACITY, bool directed = false)
  :vertexCount(0),
  capacity(capacity),
  adjacencyMatrix(0),
  adjacencyList(0),
  vertexes(capacity, nullptr),
  isDirected(directed) {
    if (matrix) {
      this->adjacencyMatrix.resize(
      capacity, std::vector<WeightType*>(capacity, nullptr));
    } else {
      this->adjacencyList.resize(capacity, nullptr);
    }
  }
  /**
   * @brief Copy constructor
   * 
   * @param other 
   */
  Graph(const Graph<DataType, WeightType, matrix>& other)
  :vertexCount(other.vertexCount),
  capacity(other.capacity),
  adjacencyMatrix(0),
  adjacencyList(0),
  vertexes(other.vertexes.size(), nullptr),
  isDirected(other.isDirected) {
    if (matrix) {
      this->adjacencyMatrix.resize(
      other.capacity, std::vector<WeightType*>(other.capacity, nullptr));
      this->copyMatrix(other);
    } else {
      this->adjacencyList.resize(other.capacity, nullptr);
      this->copyList(other);
    }
    this->copyVertexes(other);
  }
  /**
   * @brief Move constructor
   * 
   * @param other 
   */
  Graph(Graph<DataType, WeightType, matrix>&& other)
  :vertexCount(std::move(other.vertexCount)),
  capacity(std::move(other.capacity)),
  adjacencyMatrix(std::move(other.adjacencyMatrix)),
  adjacencyList(std::move(other.adjacencyList)),
  vertexes(std::move(other.vertexes)),
  isDirected(std::move(other.isDirected)) {
    other.vertexCount = 0;
    other.capacity = 0;
    other.adjacencyMatrix.clear();
    other.adjacencyList.clear();
    other.vertexes.clear();
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
    if (matrix) {
      this->deleteMatrix();
    } else {
      this->deleteList();
    }
    this->deleteVertexes();
  }

 public:
  /**
   * @brief Operator= overload with constants
   * @param other A reference to a graph type of object 
   * 
   * @return Graph<DataType, WeightType>& 
   */
  Graph<DataType, WeightType, matrix>& operator=(const
  Graph<DataType, WeightType, matrix>& other) {
    // Conditions in case this is diferent from the other reference
    if (this != &other) {
      // Delete this vertexes
      this->deleteVertexes();

      if (matrix) {
        // Delete this matrix
        this->deleteMatrix();
        if (this->capacity != other.capacity) {
          // Cycle that goes from 0 until it reaches
          // the size of the adjacency matrix and resizes it
          for (size_t column = 0; column < this->adjacencyMatrix.size();
          ++column) {
            this->adjacencyMatrix[column].resize(other.capacity);
          }
          // Resizing the adjacency Matrix
          this->adjacencyMatrix.resize(other.capacity);
          // Resizing Vertexes
          this->vertexes.resize(other.capacity);
          // Assign the new capacity
          this->capacity = other.capacity;
        }
        // Assigns the matrix
        this->copyMatrix(other);

      } else {
        // delete List
        this->deleteList();
        // Conditional in case the capacities are different
        if (this->capacity != other.capacity) {
          // Resizing the adjacency List
          this->adjacencyList.resize(other.capacity);
          // Resizing Vertexes
          this->vertexes.resize(other.capacity);
          // Assign the new capacity
          this->capacity = other.capacity;
        }
        // Assigns the list
        this->copyList(other);
      }

      // Assigns vertexes and vertex count
      // and the fact that if its directed or not
      this->copyVertexes(other);
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
  Graph<DataType, WeightType, matrix>& operator=(
    Graph<DataType, WeightType, matrix>&& other) {
    if (this != &other) {
      // Swaps the vertex count, capacity, adjacency matrix, vertexes
      // and if it is directed or not from this to other
      std::swap(this->vertexCount, other.vertexCount);
      std::swap(this->capacity, other.capacity);
      std::swap(this->adjacencyMatrix, other.adjacencyMatrix);
      std::swap(this->adjacencyList, other.adjacencyList);
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
   * @brief Get the memory size of the graph
   * 
   * @return const size_t
   */
  size_t getSize() const {
    // Get the sizeof of the attributes + padding
    size_t size = sizeof(*this);

    // Add the memory from the elements of vertexes
    // and the allocated memory
    size += 8*this->vertexes.size();
    size += this->vertexCount*sizeof(Vertex<DataType>);

    // Add the memory from the matrix, if any
    size += (sizeof(std::vector<Vertex<DataType>*>) +
    8*this->capacity)*this->adjacencyMatrix.size();

    // Add the memory from the list, if any
    size += 8*this->adjacencyList.size();

    // Add the dinamically allocated memory
    if (matrix) {
      size += this->vertexCount*sizeof(WeightType);
    } else {
      for (size_t list = 0; list < this->vertexCount; ++list) {
        size += sizeof(*this->adjacencyList[list]) +
        sizeof(Link<DataType, WeightType>)*
        this->adjacencyList[list]->size();
      }
    }

    return size;
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
      if (matrix) {
        return *this->adjacencyMatrix[this->whereIsVertex(origin)-1][
        --this->whereIsVertex(connection)];
      } else {
        return (*whereIsLink(
        this->whereIsVertex(origin)-1, connection)).getWeigth();
      }
  }

  /**
   * @brief operator() overload
   * @details see @a operator() for the origin and connection param
   * @see operator()
   * 
   * @return WeightType& 
   */
  WeightType& operator()(
    Vertex<DataType>& origin,
    Vertex<DataType>& connection) {
      if (matrix) {
        return *this->adjacencyMatrix[this->whereIsVertex(origin)-1][
        this->whereIsVertex(connection)-1];
      } else {
        return (*whereIsLink(
        this->whereIsVertex(origin)-1, connection)).getWeigth();
      }
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
    if (matrix) {
      // Returns the value of the following propositions
      return this->adjacencyMatrix[originPosition][destinPosition] != nullptr;
    } else {
      return whereIsLink(originPosition, connection) !=
      this->adjacencyList[originPosition]->end();
    }
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
    size_t neighborsFound = 0;
    // variable to know the position of origin
    size_t originPosition = this->whereIsVertex(origin) -1;

    if (matrix) {
      size_t vertex = 0;
      // Cycle that stores the neighboors from origin
      while (neighborsFound < origin.getLinkCount()
      && vertex < this->vertexCount) {
        if (this->adjacencyMatrix[originPosition][vertex]
        != nullptr) {
          neighbors[neighborsFound++] = this->vertexes[vertex];
        }
        ++vertex;
      }
    } else {
      for (typename listType::iterator itr =
      this->adjacencyList[originPosition]->begin();
      itr != this->adjacencyList[originPosition]->end(); ++itr) {
        neighbors[neighborsFound++] = (*itr).getConnection();
      }
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

  /**
   * @brief Returns the itr of the Link
   * 
   * @param originPosition position of the adjacencyList the origin of the link is
   * @param connection a reference to the vertex the link is attached to
   * @return Link<DataType, WeightType> itr->weight()
   */
  typename listType::iterator whereIsLink(
    const size_t originPosition, Vertex<DataType>& connection) {
    typename listType::iterator itr =
    this->adjacencyList[originPosition]->begin();
    for (typename listType::iterator end =
    this->adjacencyList[originPosition]->end();
    itr != end; ++itr) {
      if ((*itr).getConnection() == &connection) {
        return itr;
      }
    }
    return itr;
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

    if (!matrix) {
      listType* newLinks = new listType;
      this->adjacencyList[this->vertexCount] = newLinks;
    }
    // Adds the vertex to the vertex list
    this->vertexes[this->vertexCount] =
    new Vertex<DataType>(vertex);
    this->vertexes[this->vertexCount++]->getLinkCount() = 0;
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
    this->vertexes.push_back(nullptr);
    updateAdjacency('v', position);
    --this->vertexCount;
    // Deletes the links of the vertex
    vertex.getLinkCount() = 0;
    return true;
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
    if (this->isAdjacent(origin, connection)) {
      return false;
    }
    // Adds link
    if (matrix) {
      this->adjacencyMatrix[originPosition][destinPosition] =
      new WeightType;
      *this->adjacencyMatrix[originPosition][destinPosition] =
      weight;
    } else {
      this->adjacencyList[originPosition]->push_back(
      Link<DataType, WeightType>(&connection, weight));
    }
    // Increases the link count
    ++origin.getLinkCount();
    // In case it is not directed
    if (!this->isDirected && &origin != &connection) {
      // Adds link
      if (matrix) {
        this->adjacencyMatrix[destinPosition][originPosition] =
        new WeightType;
        *this->adjacencyMatrix[destinPosition][originPosition] =
        weight;
      } else {
        this->adjacencyList[destinPosition]->push_back(
        Link<DataType, WeightType>(&origin, weight));
      }
      // Increases the link count
      ++connection.getLinkCount();
    }
    return true;
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
    if (!this->isAdjacent(origin, connection)) {
      return true;
    }
    // Erase the link
    this->updateAdjacency('l', originPosition, destinPosition);
    // Decreases the link count
    --origin.getLinkCount();

    // Condition if it is not directed
    if (!this->isDirected && &origin != &connection) {
      // Erase the link
      this->updateAdjacency('l', destinPosition, originPosition);
      // Decreases the link count
      --connection.getLinkCount();
    }
    return false;
  }

   /**
    * @brief Get the Link object
    * @details see @a operator() for the origin and connection param
    * @details both param are pointers
    * @see operator()
    * 
    * @return WeightType& origin->getLinkWeight(this->whereIsLink(origin, connection)-1)
    */
  const WeightType& getLink(
    Vertex<DataType>& origin,
    Vertex<DataType>& connection) {
      // Create and assign two size_t variables with the
    // return value of whereIsVertex()
    size_t originPosition = this->whereIsVertex(origin);
    size_t destinPosition = this->whereIsVertex(connection);
     // Condition if any of the positions are 0 if so, it throws an exception
    if (originPosition-- == 0 || destinPosition-- == 0) {
      throw std::runtime_error(
        "Graph: Could not find vertex(es) to get the Link");
    }
    // Condition if there is no adjacency, then throws an error
    if (!this->isAdjacent(origin, connection)) {
      throw std::runtime_error("Graph: Could not find Link to get it");
    }
    // return the weight
    return (*this)(origin, connection);
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
    if (!this->isAdjacent(origin, connection)) {
      throw std::runtime_error("Graph: Could not find Link to set it");
    }

    // Assigns the weight to the link
    (*this)(origin, connection) = weight;

    // Condition if it is not directed, then assigns the weight to the link
    if (!this->isDirected && &origin != &connection) {
      (*this)(connection, origin) = weight;
    }
  }

 private:
  void copyMatrix(const Graph<DataType, WeightType, matrix>& other) {
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
    }
  }

  void copyList(const Graph<DataType, WeightType, matrix>& other) {
    for (size_t list = 0; list < other.vertexCount;
    ++list) {
      this->adjacencyList[list] =
      new listType(*other.adjacencyList[list]);
    }
  }

  void copyVertexes(const Graph<DataType, WeightType, matrix>& other) {
    for (size_t vertex = 0; vertex < other.vertexCount;
    ++vertex) {
      this->vertexes[vertex] =
      new Vertex<DataType>(*other.vertexes[vertex]);
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

  void deleteList() {
    for (size_t list = 0; list < this->vertexCount;
      ++list) {
        delete this->adjacencyList[list];
        this->adjacencyList[list] = nullptr;
    }
  }

  void deleteVertexes() {
    for (size_t vertex = 0; vertex < this->vertexCount;
      ++vertex) {
        delete this->vertexes[vertex];
        this->vertexes[vertex] = nullptr;
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

    updateAdjacency('i', newCapacity);

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
    if (matrix) {
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
    } else {
      if (this->adjacencyList.size() != newCapacity) {
        return false;
      }
    }
    if (this->vertexes.size() != newCapacity) {
      return false;
    }

    return true;
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
        if (this->isAdjacent(*this->vertexes[current],
        *this->vertexes[vertexPosition])) {
          this->updateAdjacency('l', current, vertexPosition);
          --this->vertexes[current]->getLinkCount();
        }
      }
    }
  }

  /**
   * @brief 
   * 
   * @param action 
   */
  void updateAdjacency(const char action,
  const size_t firstNumber = 0, const size_t secondNumber = 0) {
    switch (action) {
      case 'v':
        if (matrix) {
          removeVertexMatrix(firstNumber);
        } else {
          removeVertexList(firstNumber);
        }
      break;

      case 'l':
        if (matrix) {
          removeLinkMatrix(firstNumber, secondNumber);
        } else {
          removeLinkList(firstNumber, secondNumber);
        }
      break;

      case 'i':
        if (matrix) {
          increaseMatrix(firstNumber);
        } else {
          increaseList(firstNumber);
        }
      break;

      default:
      break;
    }
  }

  void removeVertexMatrix(size_t position) {
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
  }

  void removeVertexList(size_t position) {
    delete this->adjacencyList[position];
    // Erase the position row and adjust the adjacency list
    this->adjacencyList.erase(
    this->adjacencyList.begin()+position);
    this->adjacencyList.push_back(nullptr);
  }

  void removeLinkMatrix(const size_t originPosition,
  const size_t destinPosition) {
    delete this->adjacencyMatrix[originPosition][destinPosition];
    this->adjacencyMatrix[originPosition][destinPosition] = nullptr;
  }

  void removeLinkList(const size_t originPosition,
  const size_t destinPosition) {
    (*this->adjacencyList[originPosition]).erase(
    this->whereIsLink(originPosition,
    *this->vertexes[destinPosition]));
  }

  void increaseMatrix(const size_t newCapacity) {
    // Cycle that goes from 0 until it reaches the max,
    // resizing the row of the adjacency matrix
    for (size_t row = 0; row < this->capacity; ++row) {
      this->adjacencyMatrix[row].resize(newCapacity, nullptr);
    }
    // Calls the resize() method
    this->adjacencyMatrix.resize(
    newCapacity, std::vector<WeightType*>(newCapacity, nullptr));
  }

  inline void increaseList(const size_t newCapacity){
    // Resizes the adjacency list
    adjacencyList.resize(newCapacity, nullptr);
  }
};

}  // namespace grph

/*! @} End of Doxygen Groups*/
#endif  // GRAPH_HPP
