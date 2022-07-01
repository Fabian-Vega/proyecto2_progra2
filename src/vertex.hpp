// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef VERTEX_HPP

#define VERTEX_HPP

#include <cstddef>
#include <vector>

/*!
 *  \addtogroup grph
 *  @{
 */

//! Generic graph types and operations
namespace grph {

/**
 * @brief Template for a default vertex
 * @tparam DataType Specific type of data the vertex are going to store
 * @tparam WeightType Specific type of data of the links between the vertex 
 */
template<typename DataType, typename WeightType>

/**
 * @brief class for the vertex type of object
 * 
 */
class Vertex {
 public:
  /**
   * @brief subclass for the links between the vertex type of object
   * 
   */
  class Link {
   private:
    // origin is a pointer to the vertex from which the link comes out
    Vertex<DataType, WeightType>*         origin;
    // weight is a value that stores the significance of the link
    WeightType                            weight;
    // connection is a pointer to the vertex to which the link goes to
    Vertex<DataType, WeightType>*         connection;

   public:
    /**
     * @brief Construct a new link object
     * 
     * @param orgin vertex pointer to the vertex from which the link comes out
     * @param connection vertex pointer to the vertex to which the link goes to
     */
    Link(Vertex<DataType, WeightType>* origin = nullptr,
    Vertex<DataType, WeightType>* connection = nullptr)
    :origin(origin),
    weight(),
    connection(connection) {
    }

    /**
     * @brief Construct a new link object
     * 
     * @param orgin vertex pointer to the vertex from which the link comes out
     * @param weight value that stores the significance of that link
     * @param connection vertex pointer to the vertex to which the link goes to
     */
    Link(Vertex<DataType, WeightType>* origin,
    WeightType& weight,
    Vertex<DataType, WeightType>* connection)
    :origin(origin),
    weight(weight),
    connection(connection) {
    }

   public:
    /**
     * @brief Get the weight from the link
     * 
     * @return WeightType&
     */
    inline WeightType& getWeight() {
      return this->weight;
    }
    /**
     * @brief Get the const weight from the link
     * 
     * @return const WeightType&
     */
    inline const WeightType& getWeight() const {
      return this->weight;
    }
    /**
     * @brief Get the pointer to the vertex to which the link goes to
     * 
     * @return Vertex<DataType, WeightType>*
     */
    inline Vertex<DataType, WeightType>* getConnection() {
      return this->connection;
    }
    /**
     * @brief Get the const pointer to the vertex to which the link goes to
     * 
     * @return const Vertex<DataType, WeightType>*
     */
    inline const Vertex<DataType, WeightType>* getConnection() const {
      return this->connection;
    }
  };

 private:
  // data is a DataType stored on the vertex
  DataType             data;
  // linkCount size_t with the number of link that the vertex has
  size_t               linkCount;
  // linkVector std::vector<Link> vector links of the vertex
  std::vector<Link>    linkVector;

 public:
  /**
   * @brief Construct a new Vertex object
   * 
   * @param data vertex pointer to the vertex from which the link comes out
   */
  explicit Vertex(const DataType& data)
  :data(data),
  linkCount(0),
  linkVector(0) {
  }

 public:
  /**
   * @brief Get the const data from the vertex
   * 
   * @return const DataType&
   */
  inline const DataType& getData() const {
    return this->data;
  }
  /**
   * @brief Get the linkCount from the vertex
   * 
   * @return size_t&
   */
  inline size_t& getLinkCount() {
    return this->linkCount;
  }

  /**
   * @brief Get the linkCount from a const vertex
   * 
   * @return size_t
   */
  inline size_t getLinkCount() const {
    return this->linkCount;
  }

  /**
   * @brief Get the linkCount from the vertex
   * 
   * @return size_t&
   */
  inline std::vector<Link>& getLinkVector() {
    return this->linkVector;
  }

  /**
   * @brief Get the weight of the link on position linkPosition from this vertex
   * 
   * @param linkPosition size_t with position of the link from which
   * the weight is desired
   * @return WeightType&
   */
  inline WeightType& getLinkWeight(size_t linkPosition) {
    return this->linkVector[linkPosition].getWeight();
  }

  /**
   * @brief Get the const weight of the link on position linkPosition from this vertex
   * 
   * @param linkPosition size_t with position of the link from which
   * the weight is desired
   * @return const WeightType&
   */
  inline const WeightType& getLinkWeight(size_t linkPosition) const {
    return this->linkVector[linkPosition].getWeight();
  }

  /**
   * @brief Get the connection of the link on position linkPosition from this vertex
   * 
   * @param linkPosition size_t with position of the link from which
   * the connection is desired
   * @return Vertex<DataType, WeightType>*
   */
  inline Vertex<DataType, WeightType>* getLinkConnection(
    size_t linkPosition) {
    return this->linkVector[linkPosition].getConnection();
  }

  /**
   * @brief Get the const connection of the link on position linkPosition from this vertex
   * 
   * @param linkPosition size_t with position of the link from which
   * the connection is desired
   * @return const Vertex<DataType, WeightType>*
   */
  inline const Vertex<DataType, WeightType>* getLinkConnection(
    size_t linkPosition) const {
    return this->linkVector[linkPosition].getConnection();
  }

  /**
   * @brief Uses the link constructor to create a from this vertex to connection
   * 
   * @param weightvalue that stores the significance of the link
   * @param connection vertex pointer to the vertex to which the link goes to
   * @return Vertex<DataType, WeightType>::Link 
   */
 public:
  Vertex<DataType, WeightType>::Link createLink(WeightType weight,
  Vertex<DataType, WeightType>* connection) {
    return Vertex<DataType, WeightType>::Link(this, weight, connection);
  }
};

}  // namespace grph

/*! @} End of Doxygen Groups*/

#endif  // VERTEX_HPP
