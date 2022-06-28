// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef LINK_HPP
#define LINK_HPP

#include "vertex.hpp"

namespace grph {

template<typename Datatype, typename WeightType>
class Link{
  public:
  Vertex<Datatype, WeightType>*         origin;
  WeightType                            weight;
  Vertex<Datatype, WeightType>*         connection;

  Link(Vertex<Datatype, WeightType>* origin = nullptr, 
  Vertex<Datatype, WeightType>* connection = nullptr)
  :origin(origin),
  weight(),
  connection(connection) {
  }

  Link(Vertex<Datatype, WeightType>* origin,
  const WeightType& weight,
  Vertex<Datatype, WeightType>* connection)
  :origin(origin),
  weight(weight),
  connection(connection) {
  }
};
  
}  // namespace grph

#endif  // LINK_HPP