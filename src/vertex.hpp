// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <cstddef>
#include <utility>
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
  // linkCount size_t with the number of link that the vertex has
  size_t               linkCount;
  // data is a DataType stored on the vertex
  DataType             data;

 public:
  /**
   * @brief Construct a new Vertex object
   * 
   * @param data data inside the vertex
   */
  explicit Vertex(const DataType& data = DataType())
  :linkCount(0),
  data(data) {
  }

 public:
  /**
   * @brief Construct a new Vertex object
   * 
   * @param other vertex to the vertex to copy
   */
  Vertex(const Vertex<DataType>& other)
  :linkCount(other.linkCount),
  data(other.data) {
  }

  /**
   * @brief Construct a new Vertex object
   * 
   * @param other vertex to the vertex to copy
   */
  Vertex(Vertex<DataType>& other)
  :linkCount(std::move(linkCount)),
  data(std::move(other.data)) {
  }

  Vertex<DataType>& operator=(const
  Vertex<DataType>& other) {
    // Conditions in case this is diferent from the other reference
    if (this != &other) {
      // Assigns the corresponding data
      this->linkCount = other.linkCount;
      this->data = other.data;
    }
    return *this;
  }
  // Operator= Overload
  Vertex<DataType>& operator=(
  Vertex<DataType>&& other) {
    // Conditions in case this is diferent from the other reference
    if (this != &other) {
      // Swaps the corresponding datas
      std::swap(this->linkCount, other.linkCount);
      std::swap(this->data, other.data);
    }
    return *this;
  }

 public:
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
  /**
   * @brief Get the const data from the vertex
   * 
   * @return const DataType&
   */
  inline const DataType& getData() const {
    return this->data;
  }
};

}  // namespace grph

/*! @} End of Doxygen Groups*/

#endif  // VERTEX_HPP
