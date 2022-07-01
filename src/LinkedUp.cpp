// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

size_t showOptions (const char* initialMessage, const char* options,
const size_t optionMin, const size_t optionMax);
void addProfile(grph::Graph<std::string, std::string>& graph);
void deleteProfile(grph::Graph<std::string, std::string>& graph);
void addFriendship(grph::Graph<std::string, std::string>& graph);
void updateFriendship(grph::Graph<std::string, std::string>& graph);
void deleteFriendship(grph::Graph<std::string, std::string>& graph);
void modifyFriendship(grph::Graph<std::string, std::string>& graph);
void printProfile(grph::Graph<std::string, std::string>& graph);


int main(void) {
  try {
    size_t inputOption = 6;
    std::cout << "Welcome to LinkedUp, your place for linking up with your friends.\n" 
    << std::endl;

    const char* initialMessage =
    "Please choose what you wnat to do by writing the number indicated below:\n";
    
    const char* initialOptions =
    "[1]Add Profile\n[2]Delete Profile\n"
    "[3]Add Friendship\n[4]Update Friendship\n"
    "[5]See Profile\n[0]Quit\n";
    

    grph::Graph<std::string, std::string> graph(3, false);

    while (inputOption) {
      inputOption = showOptions(initialMessage, initialOptions, 0, 5);
      
      switch (inputOption) {
      case 0:
          std::cout << "Thanks for using LinkedUp." << std::endl;
      break;
      
      case 1:
          addProfile(graph);
      break;

      case 2:
          deleteProfile(graph);
      break;

      case 3:
          addFriendship(graph);
      break;

      case 4:
          updateFriendship(graph);
      break;

      case 5:
          printProfile(graph);
      break;
      
      default:
        std::cout << "Am unexpected error has ocurred\n" << std::endl;
      break;
      }

      if (inputOption) {
        std::cout << "\nDesea hacer algo más? " << std::endl;
      }
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}

size_t showOptions (const char* initialMessage, const char* options,
const size_t optionMin, const size_t optionMax) {
  size_t inputOption = 5; bool validOption = false;
  while (!validOption) {
    std::cout << initialMessage << options << std::endl;
    std::cin >> inputOption;
    std::cout << std::endl;

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

void showProfiles(const char* initialMessage,
const grph::Graph<std::string, std::string>& graph) {
  std::cout << initialMessage << '\n';
  for (size_t profile = 0; profile < graph.getVertexCount(); profile++){
      std::cout <<"[" << profile+1 << "]"
      << graph.getVertexes()[profile]->getData() << "\n";
  }
}

void addProfile(grph::Graph<std::string, std::string>& graph) {
  std::cout << "What is the name of the person to be added?" << std::endl;
  std::string input = "\0";

  std::cin.ignore(2, '\n');
  std::getline(std::cin, input);
  grph::Vertex<std::string, std::string>* profile = new grph::Vertex<std::string, std::string>((std::string(input)));
  if (profile == nullptr) {
    std::cout << "The profile wasnt able to be added." << std::endl;
  } 
  bool success = graph.addVertex(profile);
  if (success) {
    std::cout << "The profile was able to be added succesfully." << std::endl;
  }
}

void deleteProfile(grph::Graph<std::string, std::string>& graph) {
  showProfiles( "Available profiles:", graph);
  size_t inputOption = showOptions(
      "Please choose the profile to be deleted", 
      "", 1, graph.getVertexCount());
  grph::Vertex<std::string, std::string>* profile = graph.getVertexes()[inputOption-1];
  bool success = graph.removeVertex(profile);
  if (success) {
    std::cout << "The profile was able to be deleted succesfully." << std::endl;
  }
}

void addFriendship(grph::Graph<std::string, std::string>& graph) {
  showProfiles("What profiles do you want to link?", graph);

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
    "Please choose the type of relationship that they have:\n",
    "[1]Friendship\n[2]Romantic Relationship\n[3]Family Member\n[4]Coworker", 
    1, 4);

  bool success = graph.addLink(graph.getVertexes()[first-1],
  graph.getVertexes()[second-1], relationships[desition-1]);
  std::cout 
  << (success? 
  "The relationship was added succesfully":
  "There was already a relationship relation between these profiles")
  << std::endl;
}

void updateFriendship(grph::Graph<std::string, std::string>& graph) {
  size_t inputOption = showOptions(
    "Do you want to delete or modify a friendship?\n",
    "[1]Delete friendship\n[2]Modify friendship", 1, 2);

  if (inputOption == 1) {
    deleteFriendship(graph);
  } else {
    modifyFriendship(graph);
  }
}

void deleteFriendship(grph::Graph<std::string, std::string>& graph) {
  showProfiles(
    "What friendship between two profiles do you want to delete?", graph);
  size_t first = 0, second = 0;
  first = showOptions(
    "Please choose the first profile", 
    "", 1, graph.getVertexCount());
  second = showOptions(
    "Please choose the second profile",
    "", 1, graph.getVertexCount());

  bool success = graph.removeLink(graph.getVertexes()[first-1], 
  graph.getVertexes()[second-1]);
  
  std::cout 
  << (success? "The friendship was deleted successfully":
  "There is not a relationship between those profiles") << std::endl;
}

void modifyFriendship(grph::Graph<std::string, std::string>& graph) {
  showProfiles(
    "What friendship between two profiles do you want to modify", graph);

  size_t first = 0, second = 0;
  first = showOptions(
    "Please choose the first profile", 
    "", 1, graph.getVertexCount());
  second = showOptions(
    "Please choose the second profile",
    "", 1, graph.getVertexCount());

  std::string relationships[4] = {"Friendship", "Romantic Relationship", "Family Member", "Coworker"};
  size_t desition = showOptions(
  "Please choose the type of relationship that they currently have:\n",
  "[1]Friendship\n[2]Romantic Relationship\n[3]Family Member\n[4]Coworker", 
  1, 4);

  try {
    graph.setLink(graph.getVertexes()[first-1],
    graph.getVertexes()[second-1], relationships[desition-1]);
    std::cout 
    << "The frienship was modified succesfully" 
    << std::endl;
  } catch (const std::runtime_error& error) {
    std::cout 
    << "There was not an existing frienship between those profiles" 
    << std::endl;
  }
}

void printProfile(grph::Graph<std::string, std::string>& graph) {
  showProfiles("What profile do you want to see?", graph);
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

    for (size_t friendship = 0;
    friendship < profile->getLinkCount(); ++friendship) {
       std::cout 
       << relationships[friendship]->getData() << " " 
       << profile->getLinkWeight(friendship) << std::endl;
    }
}