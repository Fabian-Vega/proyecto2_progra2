// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "link.hpp"

namespace grph {

template<typename DataType, typename WeigthType>
class Vertex{
   public:
    Datatype             data;
    size_t               linkCount;
    std::vector<Link<Datatype, WeigthType>>   linkVector;

   public:
    Vertex(const Datatype& data, size_t linkCount = 0)
    :data(data),
    linkCount(linkCount),
    linkVector(linkCount, Link<Datatype, WeigthType>(*this, *this)) {
    }
  };

} // namespace grph


#endif  // VERTEX_HPP