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
  Link(const Vertex<DataType>* connection,
  WeightType& weigth)
  :connection(connection),
  weigth(weigth) {
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