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
template<typename DataType>

/**
 * @brief class for the vertex type of object
 * 
 */
class Vertex {
 private:
  // data is a DataType stored on the vertex
  DataType             data;
  // linkCount size_t with the number of link that the vertex has
  size_t               linkCount;

 public:
  /**
   * @brief Construct a new Vertex object
   * 
   * @param data data inside the vertex
   */
  explicit Vertex(const DataType& data = DataType())
  :data(data),
  linkCount(0) {
  }

  public:
  /**
   * @brief Construct a new Vertex object
   * 
   * @param other vertex to the vertex to copy
   */
  Vertex(const Vertex<DataType>& other)
  :data(other.data),
  linkCount(other.linkCount) {
  }

  Vertex<DataType>& operator=(const
  Vertex<DataType>& other) {
    // Conditions in case this is diferent from the other reference
    if (this != &other) {
      this->data = other.data;
      this->linkCount = other.linkCount;
    }
    return *this;
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
  inline const size_t& getLinkCount() const {
    return this->linkCount;
  }
};

}  // namespace grph

/*! @} End of Doxygen Groups*/

#endif  // VERTEX_HPP
