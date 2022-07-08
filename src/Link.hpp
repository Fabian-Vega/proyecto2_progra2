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
  * @brief Construct a new Link object
  * 
  * @param weigth 
  */
  Link(WeightType& weigth = WeightType())
  :connection(nullptr),
  weigth(weigth) {
  }
  
  Link(const Vertex<DataType>* connection,
  WeightType& weigth)
  :connection(connection),
  weigth(weigth) {
  }

  Link(const Link<DataType, WeightType>& other)
  :connection(other.connection),
  weigth(other.weigth) {
  }

  Link(const Link<DataType, WeightType>&& other)
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