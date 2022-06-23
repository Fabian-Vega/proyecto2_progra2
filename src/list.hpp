// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>

namespace grph {

template<typename Datatype, typename Valuetype>
class List{
 private:
  class Node{
   public:
    Datatype       data;
    Valuetype      value;
    Node*          previous;
    Node*          next;

   public:
    explicit Node(const Datatype& data,
    Node* previous = nullptr, Node* next = nullptr)
    :data(data),
     value(),
     previous(previous),
     next(next) {
    }
    Node(const Datatype& data, const Valuetype& value,
    Node* previous = nullptr, Node* next = nullptr)
    :data(data),
     value(value),
     previous(previous),
     next(next) {
    }
  };

 private:
  size_t count;
  Node*  head;
  Node*  tail;

 public:
  List()
  :count(0),
   head(nullptr),
   tail(nullptr) {
  }
  explicit List(const Datatype& data)
  :count(1),
   head(new Node(data)),
   tail(head) {
    if (tail == nullptr) {
      throw std::runtime_error("List: No memory to initialize list");
    }
  }
  ~List() {
    for ( Node node = this->head; node; node = node.next ) {
      delete node;
    }
  }

 public:
  inline bool isEmpty() const {
    return this->head == nullptr;
  }
  inline const Datatype& getHead() const {
    return this->head->data;
  }
  inline void setHeadsValue(const Valuetype& value) {
    this->head->value = value;
  }

 public:
  void append(const Datatype& data, const Valuetype& value) {
    this->tail->next = new Node(data, value, this->tail);
    if (tail->next == nullptr) {
      throw std::runtime_error("List: No memory to append node");
    }
    this->tail = this->tail->next;
    ++this->count;
  }
  void remove(const Datatype& data) {
    Node node = head->next;
    while (node) {
      if (node.data == data) {
        break;
      } else {
        node = node.next;
      }
    }

    if (node == nullptr) {
      throw std::runtime_error(
        "List: Tried to delete a non existent node");
    }

    node.previous->next = node.next;
    node.next->previous = node.previous;
    delete node;
  }
};

}  // namespace grph
#endif  // LIST_HPP
