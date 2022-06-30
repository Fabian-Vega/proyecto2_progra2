// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef VERTEX_HPP

#define VERTEX_HPP

#include <cstddef>
#include <vector>

namespace grph {

/**
 * @brief Template for a default vertex
 * @tparam DataType Specific type of data the vertex are going to use
 * @tparam WeightType Specific type of data the links of the graphs are going to use
 */
template<typename DataType, typename WeightType>

/**
 * @brief class for the vertex type of object
 * 
 */
class Vertex {
 public:
  /**
   * @brief class for the link type of object
   * 
   */
  class Link {
   private:
    // Origin is the parting point of a link
    Vertex<DataType, WeightType>*         origin;
    // Weight is the data that the link carries 
    WeightType                            weight;
    // Connection is the destiny of the link
    Vertex<DataType, WeightType>*         connection;

   public:
    /**
     * @brief Construct a new Link object
     * @param origin Pointer to a vertex type of object that is the parting point of a link
     * @param connection Pointer to a vertex type of object that is the destiny of the link
     * @remark in case any or both of the parameters is missing, the values of this will be assumed as nullptr
     */
    Link(Vertex<DataType, WeightType>* origin = nullptr,
    Vertex<DataType, WeightType>* connection = nullptr)
    :origin(origin),
    weight(),
    connection(connection) {
    }

    /**
     * @brief Construct a new Link object
     * @param weight Reference to a Weightype type of data which is the data that the link carries
     * @details see @a Link() for the origin and connection param
     * @see Link()
     */
    Link(Vertex<DataType, WeightType>* origin,
    WeightType& weight,
    Vertex<DataType, WeightType>* connection)
    :origin(origin),
    weight(weight),
    connection(connection) {
    }

   public:
    /**
     * @brief Get the Weight object reference
     * 
     * @return WeightType& weight
     */
    inline WeightType& getWeight() {
      return this->weight;
    }

    /**
     * @brief Get the Weight object const reference
     * 
     * @return const WeightType& weight
     */
    inline const WeightType& getWeight() const {
      return this->weight;
    }

    /**
     * @brief Get the Connection object pointer
     * 
     * @return Vertex<DataType, WeightType>* connection 
     */
    inline Vertex<DataType, WeightType>* getConnection() {
      return this->connection;
    }

    /**
     * @brief Get the Connection object const pointer
     * 
     * @return const Vertex<DataType, WeightType>* connection
     */
    inline const Vertex<DataType, WeightType>* getConnection() const {
      return this->connection;
    }
  };

 private:
  // Data is the data that the vertex contains
  DataType             data;
  // LinkCount is the amount of links the vertex have
  size_t               linkCount;
  // LinkVector is a vector with the specific links it has
  std::vector<Link>    linkVector;

 public:
  /**
   * @brief Construct a new Vertex object
   * @param data is a DataType type of data that the vertex contains
   * @param linkCount is a size_t variable that counts the amount of links the vertex have
   */
  explicit Vertex(const DataType& data, size_t linkCount = 0)
  :data(data),
  linkCount(linkCount),
  linkVector(linkCount) {
  }

 public:
  /**
   * @brief Get the Data object reference
   * 
   * @return const DataType& data
   */
  inline const DataType& getData() const {
    return this->data;
  }

  /**
   * @brief Get the Link Count object reference
   * 
   * @return size_t& linkCount
   */
  inline size_t& getLinkCount() {
    return this->linkCount;
  }

  /**
   * @brief Get the Link Count object
   * 
   * @return size_t linkCount
   */
  inline size_t getLinkCount() const {
    return this->linkCount;
  }

  /**
   * @brief Get the Link Vector object reference
   * 
   * @return std::vector<Link>& linkVector
   */
  inline std::vector<Link>& getLinkVector() {
    return this->linkVector;
  }

  /**
   * @brief Get the Link Weight object reference
   * @param linkPosition Size_t that works as an index
   * 
   * @return WeightType& this->linkVector[linkPosition].getWeight()
   */
  inline WeightType& getLinkWeight(size_t linkPosition) {
    return this->linkVector[linkPosition].getWeight();
  }

  /**
   * @brief Get the Link Weight object const reference
   * @details see @a getLinkWeight() for the linkPosition param
   * @see getlinkWeight()
   * 
   * @return const WeightType& this->linkVector[linkPosition].getWeight()
   */

  inline const WeightType& getLinkWeight(size_t linkPosition) const {
    return this->linkVector[linkPosition].getWeight();
  }

  /**
   * @brief Get the Link Connection object pointer
   * @details see @a getLinkWeight() for the linkPosition param
   * @see getlinkWeight()
   * 
   * @return Vertex<DataType, WeightType>* this->linkVector[linkPosition].getConnection()
   */
  inline Vertex<DataType, WeightType>* getLinkConnection(
    size_t linkPosition) {
    return this->linkVector[linkPosition].getConnection();
  }

  /**
   * @brief Get the Link Connection object const pointer
   * @details see @a getLinkWeight() for the linkPosition param
   * @see getlinkWeight()
   * 
   * @return const Vertex<DataType, WeightType>* this->linkVector[linkPosition].getConnection()
   */
  inline const Vertex<DataType, WeightType>* getLinkConnection(
    size_t linkPosition) const {
    return this->linkVector[linkPosition].getConnection();
  }

 public:
  /**
   * @brief Create a Link object pointer
   * @details see @a Link() for the weight and connection param
   * @see Link()
   * 
   * @return Vertex<DataType, WeightType>::Link(this, weight, connection)
   */
  Vertex<DataType, WeightType>::Link createLink(WeightType weight,
  Vertex<DataType, WeightType>* connection) {
    return Vertex<DataType, WeightType>::Link(this, weight, connection);
  }
};

}  // namespace grph

#endif  // VERTEX_HPP
