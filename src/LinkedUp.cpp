// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

int main(void) {
    int inputOption = 4;
    std::cout << "Welcome to LinkedUp, your place for linking up with your friends.\n";
    
     int myNumber = 0;
    bool validOption = false;
    while (validOption == false) {
        std::cout << "Please choose what you wnat to do by writing the number indicated below, :\n";
        std::cout << "[1]Add User\n[2]Add Friendship\n[3]See Profile\n[0]Quit\n";
        std::cin  >> inputOption;
        if(inputOption == 0 || inputOption == 1 || inputOption == 2|| inputOption == 3){
            validOption = true;
        }
        std::cout << "Invalid number, please try again\n\n";
    }

    grph::Graph<std::string, std::string> grafo(3, false);

    switch (inputOption)
    {
    case 0:
        std::cout << "Thanks for using LinkedUp.";
        return 0;
    
    case 1:
        addProfile(grafo);
        break;
    case 2:
        
        break;
    case 3:
        
        break;
    
    default:
        break;
    }
    

  

  return 0;
}

void addProfile(grph::Graph<std::string, std::string>& graph){
    std::cout << "What is the name of the person to be added?\n";
    std::string input = "\0";
    std::getline (std::cin,input);
    grph::Vertex<std::string, std::string>* vecter = new grph::Vertex<std::string, std::string>((std::string(input)));
    if (vecter == nullptr){
        std::cout << "The profile wasnt able to be added.\n";
    } 
    bool succes = graph.addVertex(vecter);
    if (succes){
        std::cout << "The profile was able to be added succesfully.\n";
    }

    
}


