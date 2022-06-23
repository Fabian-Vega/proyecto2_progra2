//Copyright [2022] <Alejandro B, Fabian V, Kenneth V>
#ifndef LIST_HPP
#define LIST_HPP
#include <string>

namespace grph {

template<typename Datatype, typename Valuetype>
class List{
 private:
  class Node{
   public:
    Datatype       data;
    Valuetype      value;
    Node*          next;

   public:
    explicit Node(const Datatype& data, Node* next = nullptr)
    :data(data),
     value(),
     next(next) {
    }
    
    Node(const Datatype& data, Valuetype& value, Node* next = nullptr)
    :data(data),
     value(value),
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
  ~List() {
    for( Node node = this->first; node; node = node.next ) {
      delete node;
    }
  }

 public:
  inline bool isEmpty()const {
    return this->first == nullptr;
  }

 public:
  void append( const Datatype& data ) {
    if( this->isEmpty() ) {
      this->first = this->last = new Node(data);
    } else {
      this->last = this->last->next = new Node(data);
    }
    ++this->count;
  }
};

}//namespace grph
#endif  // LIST_HPP
