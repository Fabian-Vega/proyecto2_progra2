// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef LINK_HPP
#define LINK_HPP

#include "vertex.hpp"

/*!
 *  \addtogroup grph
 *  @{
 */

//! Generic graph types and operations
namespace grph {

template<typename DataType, typename WeightType>
class Link {
 private:
  Vertex<DataType>* connection;
  WeightType weigth;

 public:
  /**
   * @brief Default constructor
   * 
   * @param weigth 
   */
  Link(WeightType& weigth = WeightType())
  :connection(nullptr),
  weigth(weigth) {
  }
  /**
   * @brief Default Constructor
   * 
   * @param connection 
   * @param weigth 
   */
  Link(const Vertex<DataType>* connection,
  WeightType& weigth)
  :connection(connection),
  weigth(weigth) {
  }

  /**
   * @brief Copy Constructor
   * 
   * @param other 
   */
  Link(const Link<DataType, WeightType>& other)
  :connection(other.connection),
  weigth(other.weigth) {
  }
  
  /**
   * @brief Move Constructor
   * 
   * @param other 
   */
  Link(Link<DataType, WeightType>&& other)
  :connection(std::move(other.connection)),
  weigth(std::move(other.weigth)) {
    other.connection = nullptr;
  }

  inline const WeightType& getWeigth() const {
    return this->weigth;
  }

  inline const Vertex<DataType>* getConnection() const {
    return this->connection;
  }

};

}  // namespace grph

#endif  // LINK_HPP