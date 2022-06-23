// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <utility>

namespace grph {

template<typename Datatype, typename Valuetype>
class List{
 private:
  class Edge{
   public:
    Datatype       data;
    Valuetype      value;
    Edge*          previous;
    Edge*          next;

   public:
    explicit Edge(const Datatype& data,
    Edge* previous = nullptr, Edge* next = nullptr)
    :data(data),
     value(),
     previous(previous),
     next(next) {
    }

    Edge(const Datatype& data, const Valuetype& value,
    Edge* previous = nullptr, Edge* next = nullptr)
    :data(data),
     value(value),
     previous(previous),
     next(next) {
    }
  };

 private:
  size_t count;
  Edge*  head;
  Edge*  tail;

 public:
  List()
  :count(0),
   head(nullptr),
   tail(nullptr) {
  }

  explicit List(const Datatype& data)
  :count(1),
   head(new Edge(data)),
   tail(head) {
    if (tail == nullptr) {
      throw std::runtime_error("List: No memory to initialize list");
    }
  }

  ~List() {
    for (Edge* edge = this->head; edge; edge = edge->next) {
      delete edge;
    }
  }

 public:
  List& operator=(const List& other) {
    if (this != &other) {
      if (this->count != other.count) {
        this->copyEdges(other, (this->count < other.count)?
        this->count : other.count);

        if (this->count < other.count) {
          Edge* edge = other.head;
          for (size_t position = 0;
          position < this->count; position++) {
            edge = edge->next;
          }

          for (size_t aditions = other.count-this->count;
          aditions > 0; aditions--) {
            this->append(edge->data, edge->value);
          }

        } else {
          for (size_t deletions = this->count - other.count;
          deletions > 0; deletions--) {
            this->remove(this->tail->data);
          }
        }

      } else {
        this->copyEdges(other, this->count);
      }
    }
    return *this;
  }

 private:
  Edge* findEdge(const Datatype& data) const {
    Edge* edge = this->head;
    while (edge) {
      if (edge->data == data) {
        break;
      } else {
        edge = edge->next;
      }
    }
    return edge;
  }

 public:
  inline bool isEmpty() const {
    return this->head == nullptr;
  }

  inline const Datatype& getHead() const {
    return this->head->data;
  }

  const Valuetype& getEdgeValue(const Datatype& data) const {
    Edge* edge = this->findEdge(data);
    if (edge == nullptr) {
      throw std::runtime_error(
        "List: Tried to get the value of a non existent edge");
    }

    return edge->value;
  }

  void setEdgeValue(const Datatype& data, const Valuetype& value) {
    Edge* edge = this->findEdge(data);
    if (edge == nullptr) {
      throw std::runtime_error(
        "List: Tried to set the value of a non existent edge");
    }

    edge->value = value;
  }

 public:
  void append(const Datatype& data, const Valuetype& value) {
    this->tail->next = new Edge(data, value, this->tail);
    if (tail->next == nullptr) {
      throw std::runtime_error("List: No memory to append edge");
    }
    this->tail = this->tail->next;
    ++this->count;
  }

  void remove(const Datatype& data) {
    Edge* edge = this->findEdge(data);
    if (edge == nullptr) {
      throw std::runtime_error(
        "List: Tried to remove a non existent edge");
    }
    if (edge == head) {
      throw std::runtime_error(
        "List: Tried to remove the original vertex");
    }

    edge->previous->next = edge->next;
    edge->next->previous = edge->previous;
    delete edge;
  }

 private:
  void copyEdges(const List& other, size_t count) {
    Edge* thisEdge = this->head;
    Edge* otherEdge = other.head;
    for (size_t element = 0; element < count; element++) {
      thisEdge->data = otherEdge->data;
      thisEdge->value = otherEdge->value;
      thisEdge = thisEdge->next;
      otherEdge = otherEdge->next;
    }
  }
};

}  // namespace grph
#endif  // LIST_HPP
