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
  Vertex<DataType>& contents;
  WeightType& weigth;

 public:
  Link(const Vertex<DataType>& contents,
  WeightType& weigth)
  :contents(contents),
  weigth(weigth) {
  }

  inline const WeightType& getWeigth() const {
    return this->weigth;
  }

  inline const Vertex<DataType>& getVertex() const {
    return this->contents;
  }
};

}  // namespace grph

#endif  // LINK_HPP