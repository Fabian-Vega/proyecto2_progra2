// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

typedef grph::Graph<std::string, std::string, false> graphType;

/**
 * @brief Prints header and options to choose
 * @tparam const char* header message to be printed
 * @tparam const char* text of options to be chosen from. 
 * @tparam const size_t the minimun number that can be chosen as option
 * @tparam const size_t the maximun number that can be chosen as option
 * @return size_t the index of the option chosen
 */
size_t showOptions(const char* initialMessage, const char* options,
const size_t optionMin, const size_t optionMax);

/**
 * @brief Adds a a profile to the graph
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * profile will be made. 
 */
void addProfile(graphType& graph);

/**
 * @brief Deletes a Profile from a graph.
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * profile will be deleted from.
 */
void deleteProfile(graphType& graph);

/**
 * @brief Adds a friendship link between two profiles.
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * Friendship will be made.
 */
void addFriendship(graphType& graph);

/**
 * @brief Will delete or chage the destination of a friendship link.
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * Friendship will be updated from.
 */
void updateFriendship(graphType& graph);

/**
 * @brief Will delete a friendship link between two profiles.
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * Friendship will be deleted from.
 */
void deleteFriendship(graphType& graph);

/**
 * @brief Will chage the destination of a friendship link.
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * Friendship will be updated from.
 */
void modifyFriendship(graphType& graph);

/**
 * @brief Prints the data from a profile
 * @tparam grph::Graph<std::string, std::string>& reference to the graph, in which the 
 * Friendship will be printed from.
 */
void printProfile(graphType& graph);


int main(void) {
  try {
    // Numeber of input options to be asked
    size_t inputOption = 6;
    std::cout
    << "Welcome to LinkedUp, your place for linking up with your friends.\n"
    << std::endl;

    const char* initialMessage =
    "Please choose what you wnat to do "
    "by writing the number indicated below:\n";
    // Options for the user to choose a function
    const char* initialOptions =
    "[1]Add Profile\n[2]Delete Profile\n"
    "[3]Add Friendship\n[4]Update Friendship\n"
    "[5]See Profile\n[0]Quit\n";
    // Creates the graph
    graphType graph(3, false);

    // Cicle while the user hasnt quitted the program
    while (inputOption) {
      // Prints the question, and options
      inputOption = showOptions(initialMessage, initialOptions, 0, 5);

      switch (inputOption) {
      case 0:
          std::cout << "Thanks for using LinkedUp, Please come back soon."
          << std::endl;
      break;

      case 1:
          // Adds a Profile
          addProfile(graph);
      break;

      case 2:
          // Delete a Profile
          deleteProfile(graph);
      break;

      case 3:
          // Add a Friendship
          addFriendship(graph);
      break;

      case 4:
          // Update a Friendship
          updateFriendship(graph);
      break;

      case 5:
          // Prints profile information
          printProfile(graph);
      break;

      default:
        // Exception
        std::cout << "An unexpected error has ocurred\n" << std::endl;
      break;
      }

      if (inputOption) {
        // Exception
        std::cout << "\nDo you wish to do anything else?" << std::endl;
      } else {
        size_t bytes = graph.getSize();
        std::cout << "In this execution the graph on your program used: "
        << bytes << " bytes." << std::endl;

        if (bytes <= 220) {std::cout << "That is not too much" << std::endl;
        } else if (bytes <= 660) {std::cout << "That is ok" << std::endl;
        } else {std::cout << "That is a lot" << std::endl;}
        graph.clear();
      }
    }
  } catch (const std::runtime_error& error) {
    // Exception
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}

size_t showOptions(const char* initialMessage, const char* options,
const size_t optionMin, const size_t optionMax) {
  size_t inputOption = 5; bool validOption = false;
  // Cicle while the user respoonds in the accepted inputs
  while (!validOption) {
    // Prints message and options
    std::cout << initialMessage << options << std::endl;
    // Receives input of the answear
    std::cin >> inputOption;
    std::cout << std::endl;

    // Checks if the answear is between the established range
    for (size_t option = optionMin; option <= optionMax; ++option) {
      // Conditional in case the input option is the same as the option
      if (inputOption == option) {
        // Option verification
        validOption = true;
        break;
      }
    }
    // Conditional in case the option is invalid
    if (!validOption) {
      // Exception
      std::cout << "Invalid number, please try again\n" << std::endl;
    }
  }
  return inputOption;
}

// Procedure showProfiles()
void showProfiles(const char* initialMessage,
const graphType& graph) {
  // Prints the profile
  std::cout << initialMessage << '\n';
  // Cicle to print each profile
  for (size_t profile = 0; profile < graph.getVertexCount(); ++profile) {
    std::cout <<"[" << profile+1 << "]"
    << graph.getVertexes()[profile]->getData() << std::endl;
  }
}
// End of procedure

// Procedure addProfile()
void addProfile(graphType& graph) {
  std::cout << "What is the name of the person to be added?" << std::endl;
  std::string input = "\0";

  std::cin.ignore(1, '\n');
  // Reads string of the name to be added
  std::getline(std::cin, input);
  // Create the profile
  grph::Vertex<std::string> profile(input);
  // Adds the profile to the graph
  bool success = graph.addVertex(profile);
  // If the profile was able to be added
  if (success) {
    // Exception
    std::cout << "The profile was able to be added succesfully." << std::endl;
  }
}
// End of procedure

// Procedure deleteProfile()
void deleteProfile(graphType& graph) {
  // If the graph has at least one vertex
  if (graph.getVertexCount() > 0) {
    // Prints all the available profiles
    showProfiles("Available profiles:", graph);
    // Shows the options to choose the profile
    size_t inputOption = showOptions(
        "Please choose the profile to be deleted",
        "", 1, graph.getVertexCount());
    // Gets the profile
    grph::Vertex<std::string>& profile =
    *graph.getVertexes()[inputOption-1];
    // Removes the vertex from graph
    bool success = graph.removeVertex(profile);
    if (success) {
      // Exception
      std::cout <<
      "The profile was able to be deleted succesfully." << std::endl;
    } else {
      // Exception
      std::cout <<
      "The profile doesnt exist????....i guess" << std::endl;
    }
  } else {
    // Exception
    std::cout
    << "Currently, there are no profiles to delete on LinkedUp" << std::endl;
  }
}
// Ends of procedure

// Procedure addFriendship()
void addFriendship(graphType& graph) {
  if (graph.getVertexCount() > 0) {
    showProfiles("What profiles do you want to link?", graph);

    char inputOption = 'n';
    // Initializes the variables to hold the indexes, of both vertexes
    size_t first = 0, second = 0;
    while (inputOption == 'n' || inputOption == 'N') {
      // Gets the first index
      first = showOptions(
        "Please choose the first profile to be linked",
        "", 1, graph.getVertexCount());
      // Gets the second index
      second = showOptions(
        "Please choose the second profile to be linked",
        "", 1, graph.getVertexCount());

      // If the two inputs refer to the same profile
      if (first == second) {
        // Exception
        std::cout
        << "You have chosen the same profile two times, "
        << "are you sure about this decision? (y/n)"
        << std::endl;
        std::cin >> inputOption;
      } else {
        inputOption = 'y';
      }
    }

    std::string relationships[4] =
    {"Friendship", "Romantic Relationship", "Family Member", "Coworker"};
    // Prints the type of relationships
    size_t desition = showOptions(
      "Please choose the type of relationship that they have:\n",
      "[1]Friendship\n[2]Romantic Relationship\n[3]Family Member\n[4]Coworker",
      1, 4);
    // Adds the relationship to the profiles
    bool success = graph.addLink(*graph.getVertexes()[first-1],
    *graph.getVertexes()[second-1], relationships[desition-1]);
    std::cout
    << (success?
    "The relationship was added succesfully":
    "There was already a relationship between these profiles")
    << std::endl;

  } else {
    std::cout
    << "Currently, "
    << "there are no enough profiles on LinkedUp to add friendships"
    << std::endl;
  }
}
// End procedure

// Procedure updateFriendship()
void updateFriendship(graphType& graph) {
  // Checks if the graph has 1 or more profiles to update
  if (graph.getVertexCount() > 0) {
    // Prints both the option to update or delete
    size_t inputOption = showOptions(
      "Do you want to delete or modify a friendship?\n",
      "[1]Delete friendship\n[2]Modify friendship", 1, 2);

    if (inputOption == 1) {
      // Deletes the friendship
      deleteFriendship(graph);
    } else {
      // Modifyes the friendship
      modifyFriendship(graph);
    }
  } else {
    // Exception
    std::cout
    << "Currently, "
    << "there are no enough profiles on LinkedUp to modify friendships"
    << std::endl;
  }
}
// End of procedure

// Procedure deleteFriendship()
void deleteFriendship(graphType& graph) {
  // Prints the available profiles to delete
  showProfiles(
    "What friendship between two profiles do you want to delete?", graph);
  size_t first = 0, second = 0;
  // Gets the first index
  first = showOptions(
    "Please choose the first profile",
    "", 1, graph.getVertexCount());
  // Gets the second index
  second = showOptions(
    "Please choose the second profile",
    "", 1, graph.getVertexCount());

  // Removes the friendship link
  bool success = graph.removeLink(*graph.getVertexes()[first-1],
  *graph.getVertexes()[second-1]);
  // Exception
  std::cout
  << (success? "There is not a relationship between those profiles":
  "The friendship was deleted successfully") << std::endl;
}
// End of procedure

// Procedure modifyFriendship()
void modifyFriendship(graphType& graph) {
  // Prints the available profiles to delete
  showProfiles(
    "What friendship between two profiles do you want to modify", graph);

  size_t first = 0, second = 0;
  // Gets the first index
  first = showOptions(
    "Please choose the first profile",
    "", 1, graph.getVertexCount());
  // Gets the second index
  second = showOptions(
    "Please choose the second profile",
    "", 1, graph.getVertexCount());

  std::string relationships[4] =
  {"Friendship", "Romantic Relationship", "Family Member", "Coworker"};
  size_t desition = showOptions(
  "Please choose the type of relationship that they currently have:\n",
  "[1]Friendship\n[2]Romantic Relationship\n[3]Family Member\n[4]Coworker",
  1, 4);

  try {
    // Changes the friendship link
    graph.setLink(*graph.getVertexes()[first-1],
    *graph.getVertexes()[second-1], relationships[desition-1]);
    std::cout
    << "The frienship was modified succesfully"
    << std::endl;
  } catch (const std::runtime_error& error) {
    // Exception
    std::cout
    << "There was not an existing frienship between those profiles"
    << std::endl;
  }
}
// End of procedure

// Procedure printProfile()
void printProfile(graphType& graph) {
  if (graph.getVertexCount() > 0) {
    showProfiles("What profile do you want to see?", graph);
    // Prints the available profiles to print
    size_t inputOption = showOptions(
      "Please choose the profile to be seen", "",
      1, graph.getVertexCount());
    // Gets the profile
    grph::Vertex<std::string>& profile =
    *graph.getVertexes()[inputOption-1];
    // Prints the name of the profile
    std::cout << "Name: "
    << profile.getData()
    << "\nRelationships:\n";
    // Finds the neighbours of the vertex
    grph::Vertex<std::string>** relationships =
    graph.getNeighbors(profile);

    for (size_t friendship = 0;
    friendship < profile.getLinkCount(); ++friendship) {
        // Prints each profile, with a relationship with it
        std::cout
        << relationships[friendship]->getData() << " "
        << graph.getLink(profile, *relationships[friendship]) << std::endl;
    }

    delete[] relationships;
  } else {
    std::cout
    << "Currently, there are no profiles on LinkedUp" << std::endl;
  }
}
// End of procedure
