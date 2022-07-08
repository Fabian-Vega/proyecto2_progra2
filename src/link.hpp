// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef LINK_HPP
#define LINK_HPP

#include <utility>

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
  // Connection is the finishing point where the link is connected to
  Vertex<DataType>* connection;
  // The data that the Link contains
  WeightType weigth;

 public:
  /**
   * @brief Default Constructor
   * 
   * @param connection is the finishing point where the link is connected to
   * @details see @a Link() for the weight param 
   * @see Link()
   */
  Link(Vertex<DataType>* connection = nullptr,
  WeightType& weigth = WeightType())
  :connection(connection),
  weigth(weigth) {
  }

  /**
   * @brief Copy Constructor
   * 
   * @details see @a Link() for the other param
   * @see Link()
   */
  Link(const Link<DataType, WeightType>& other)
  :connection(other.connection),
  weigth(other.weigth) {
  }

  /**
   * @brief Move Constructor
   * 
   * @details see @a Link() for the other param
   * @see Link() 
   */
  Link(Link<DataType, WeightType>&& other)
  :connection(std::move(other.connection)),
  weigth(std::move(other.weigth)) {
    other.connection = nullptr;
  }
  // Weight getter
  inline const WeightType& getWeigth() const {
    return this->weigth;
  }

  inline WeightType& getWeigth() {
    return this->weigth;
  }

  inline const Vertex<DataType>* getConnection() const {
    return this->connection;
  }

  inline Vertex<DataType>* getConnection() {
    return this->connection;
  }

};

}  // namespace grph

#endif  // LINK_HPP
