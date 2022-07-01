// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef VERTEX_HPP

#define VERTEX_HPP

#include <cstddef>
#include <vector>

namespace grph {

template<typename DataType, typename WeightType>
class Vertex {
 public:
  class Link {
   private:
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
    WeightType& weight,
    Vertex<DataType, WeightType>* connection)
    :origin(origin),
    weight(weight),
    connection(connection) {
    }

   public:
    inline WeightType& getWeight() {
      return this->weight;
    }
    inline const WeightType& getWeight() const {
      return this->weight;
    }
    inline Vertex<DataType, WeightType>* getConnection() {
      return this->connection;
    }
    inline const Vertex<DataType, WeightType>* getConnection() const {
      return this->connection;
    }
  };

 private:
  DataType             data;
  size_t               linkCount;
  std::vector<Link>    linkVector;

 public:
  explicit Vertex(const DataType& data, size_t linkCount = 0)
  :data(data),
  linkCount(linkCount),
  linkVector(linkCount) {
  }

 public:
  inline const DataType& getData() const {
    return this->data;
  }

  inline size_t& getLinkCount() {
    return this->linkCount;
  }

  inline size_t getLinkCount() const {
    return this->linkCount;
  }

  inline std::vector<Link>& getLinkVector() {
    return this->linkVector;
  }

  inline WeightType& getLinkWeight(size_t linkPosition) {
    return this->linkVector[linkPosition].getWeight();
  }

  inline const WeightType& getLinkWeight(size_t linkPosition) const {
    return this->linkVector[linkPosition].getWeight();
  }

  inline Vertex<DataType, WeightType>* getLinkConnection(
    size_t linkPosition) {
    return this->linkVector[linkPosition].getConnection();
  }

  inline const Vertex<DataType, WeightType>* getLinkConnection(
    size_t linkPosition) const {
    return this->linkVector[linkPosition].getConnection();
  }

 public:
  Vertex<DataType, WeightType>::Link createLink(WeightType weight,
  Vertex<DataType, WeightType>* connection) {
    return Vertex<DataType, WeightType>::Link(this, weight, connection);
  }
};

}  // namespace grph

#endif  // VERTEX_HPP
