#ifndef LIST_HPP
#define LIST_HPP
#include <string>

namespace grph{

class List{
 private:
  class Node{
   public:
    std::string data;
    double      value;
    Node*       next;

   public:
    Node(const std::string& data, double value = 0, Node* next = nullptr)
    :data(data),
     value(value),
     next(next){
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
   last(nullptr){  
  }
  ~List(){

  }

 public:
  inline bool isEmpty()const{
    return this->first == nullptr;
  }

 public:
  void append(const std::string& data){
    if(this->isEmpty()){
      this->first = this->last = new Node(data); 
    }else{
      this->last = this->last->next = new Node(data);
    }
  }
};

}//namespace grph
#endif // LIST_HPP