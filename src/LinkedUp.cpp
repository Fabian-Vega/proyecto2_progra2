// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

size_t showOptions (const char* initialMessage, const char* options,
const size_t optionMin, const size_t optionMax);
void addProfile(grph::Graph<std::string, std::string>& graph);
void addFriendship(grph::Graph<std::string, std::string>& graph);
void printProfile(grph::Graph<std::string, std::string>& graph);


int main(void) {
  size_t inputOption = 4;
  std::cout << "Welcome to LinkedUp, your place for linking up with your friends." 
  << std::endl;

  const char* initialMessage =
  "Please choose what you wnat to do by writing the number indicated below:";
  
  const char* initialOptions =
  "[1]Add User\n[2]Add Friendship\n[3]See Profile\n[0]Quit";
  

  grph::Graph<std::string, std::string> graph(3, false);

  while (inputOption) {
    inputOption = showOptions(initialMessage, initialOptions, 0, 3);
    
    switch (inputOption) {
    case 0:
        std::cout << "Thanks for using LinkedUp." << std::endl;
    break;
    
    case 1:
        addProfile(graph);
    break;

    case 2:
        addFriendship(graph);
    break;

    case 3:
        printProfile(graph);
    break;
    
    default:
      std::cout << "Am unexpected error has ocurred\n" << std::endl;
    break;
    }

    if (inputOption) {
      std::cout << "Desea hacer algo más? " << std::endl;
    }
  }
    
  return 0;
}

size_t showOptions (const char* initialMessage, const char* options,
const size_t optionMin, const size_t optionMax) {
  size_t inputOption = 5; bool validOption = false;
  while (!validOption) {
    std::cout << initialMessage << '\n'
    << options << std::endl;
    std::cin >> inputOption;

    for (size_t option = optionMin; option <= optionMax; ++option) {
      if (inputOption == option) {
        validOption = true;
        break;
      }
    }
    if (!validOption) {
      std::cout << "Invalid number, please try again\n" << std::endl;
    }
  }
  return inputOption;
}

void addProfile(grph::Graph<std::string, std::string>& graph) {
  std::cout << "What is the name of the person to be added?" << std::endl;
  std::string input = "\0";

  std::getline(std::cin, input);
  grph::Vertex<std::string, std::string>* vecter = new grph::Vertex<std::string, std::string>((std::string(input)));
  if (vecter == nullptr) {
    std::cout << "The profile wasnt able to be added." << std::endl;
  } 
  bool success = graph.addVertex(vecter);
  if (success) {
    std::cout << "The profile was able to be added succesfully." << std::endl;
  }
}

void addFriendship(grph::Graph<std::string, std::string>& graph) {
  std::cout << "What profiles do you want to link?" << std::endl;
  for (size_t profile = 0; profile < graph.getVertexCount(); profile++) {
    std::cout <<"[" << profile+1 << "]"
    << graph.getVertexes()[profile]->getData() << "/n";
  }

  char inputOption = 'n';
  size_t first = 0, second = 0;
  while (inputOption == 'n' || inputOption == 'N') {
    first = showOptions(
      "Please choose the first profile to be linked", 
      "", 1, graph.getVertexCount());
    second = showOptions(
      "Please choose the second profile to be linked",
      "", 1, graph.getVertexCount());

    if (first == second) {
      std::cout 
      << "You have chosen the same profile two times" 
      << "are you sure about this desicion? (y/n)" 
      << std::endl;
      std::cin >> inputOption;
    } else {
      inputOption = 'y';
    }
  }
  
  std::string relationships[4] = {"Friendship", "Romantic Relationship", "Family Member", "Coworker"};
  size_t desition = showOptions(
    "Please choose the type of relationship that they have:",
    "[1]Friendship\n[2]Romantic Relationship\n[3]Family Member\n[4]Coworker", 
    1, 4);

  bool success = graph.addLink(graph.getVertexes()[first],
  graph.getVertexes()[second], relationships[desition-1]);
  std::cout 
  << (success? 
  "The relationship was added succesfully":
  "There was already a relationship relation between these profiles");
}

void printProfile(grph::Graph<std::string, std::string>& graph) {
  std::cout << "What profile do you want to see?\n";
  for (size_t i = 0; i < graph.getVertexCount(); i++){
      std::cout <<"[" << i+1 << "]"
      << graph.getVertexes()[i]->getData() << "/n";
  }
  size_t inputOption = showOptions(
    "Please choose the profile to be seen", "",
    1, graph.getVertexCount());

    grph::Vertex<std::string, std::string>* profile = 
    graph.getVertexes()[inputOption-1];

    std::cout <<"Name: " 
    << profile->getData() 
    << "\nRelationships:\n";

    grph::Vertex<std::string, std::string>** relationships =
    graph.getNeighbors(profile);

    for (size_t  relationship = 0;
    relationship < profile->getLinkCount(); ++relationship) {
       std::cout 
       << relationships[relationship]->getData() << " " 
       << relationships[relationship]->getLinkWeight(relationship) <<"\n";
    }
    
}