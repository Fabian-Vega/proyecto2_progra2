#ifndef LIST_HPP
#define LIST_HPP
#include <string>

namespace grph{

class List{
 public:
  class Node{
   private:
    std::string  data;
    double       value;
    Node*        next;

    Node(std::string data, double value = 0, Node* next = nullptr)
    :data(data),
     value(value),
     next(next){
    }
  };
 private:
  size_t         count;
  Node*          first;
  Node*          last;
  List()
  :count(0),
   first(nullptr)
   {
    
  }
  ~List(){

  }
};

}//namespace grph
#endif // LIST_HPP