// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

namespace grph {

template<typename DataType, typename WeightType>
class Vertex{
  private:
    struct Link{
      public:
        Vertex<DataType, WeightType>*         origin;
        WeightType                            weight;
        Vertex<DataType, WeightType>*         connection;

      public:
        Link(Vertex<DataType, WeightType>* origin = nullptr,
        Vertex<DataType, WeightType>* connection = nullptr)
        :origin(origin),
        weight(),
        connection(connection) {
        }

        Link(Vertex<DataType, WeightType>* origin,
        const WeightType& weight,
        Vertex<DataType, WeightType>* connection)
        :origin(origin),
        weight(weight),
        connection(connection) {
        }
    };
    
   private:
    DataType             data;
    size_t               linkCount;
    std::vector<Link>    linkVector;

   public:
    Vertex(const Datatype& data, size_t linkCount = 0)
    :data(data),
    linkCount(linkCount),
    linkVector(linkCount, Link(*this, *this)) {
    }

   public:
    inline size_t& getLinkCount() {
      return this->linkCount;
    }

    inline const size_t& getLinkCount() const {
      return this->linkCount;
    }

    inline const WeightType& getLinkWeight(size_t linkPosition) const {
      return this->linkVector[linkPosition].weight;
    }

    inline Vertex<DataType, WeightType>* getLinkConnection(
      size_t linkPosition) const {
      return this->linkVector[linkPosition].connection;
    }
  };

} // namespace grph


#endif  // VERTEX_HPP