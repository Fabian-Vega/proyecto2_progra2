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
  Node*  first;
  Node*  last;

 public:
  List()
  :count(0),
   first(nullptr),
   last(nullptr) {
  }
  explicit List(const Datatype& data)
  :count(1),
   first(new Node(data)),
   last(first) {
    if (last == nullptr) {
      throw std::runtime_error("List: No memory to initialize list");
    }
  }
  ~List() {
    for ( Node node = this->first; node; node = node.next ) {
      delete node;
    }
  }

 public:
  inline bool isEmpty()const {
    return this->first == nullptr;
  }

 public:
  void append(const Datatype& data) {
    if ( this->isEmpty() ) {
      this->first = this->last = new Node(data);
    } else {
      this->last = this->last->next = new Node(data, this->last);
    }
    if (last == nullptr) {
      throw std::runtime_error("List: No memory to append node");
    }
    ++this->count;
  }
};

}  // namespace grph
#endif  // LIST_HPP
