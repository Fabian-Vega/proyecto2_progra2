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
    Node(const Datatype& data, Valuetype& value,
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

 public:
  void append(const Datatype& data) {
    if ( this->isEmpty() ) {
      this->head = this->tail = new Node(data);
    } else {
      this->tail = this->tail->next = new Node(data, this->tail);
    }
    if (tail == nullptr) {
      throw std::runtime_error("List: No memory to append node");
    }
    ++this->count;
  }
};

}  // namespace grph
#endif  // LIST_HPP
