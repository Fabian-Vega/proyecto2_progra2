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
        } else{
            std::cout << "Invalid number, please try again\n\n";
        }
        
        
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
        addFriendship(grafo);
        break;
    case 3:
        printProfile(grafo);
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

void addFriendship(grph::Graph<std::string, std::string>& graph){
    std::cout << "What profiles do you want to link?\n";
    for (size_t i = 0; i < graph.getVertexCount(); i++){
        std::cout << graph.getVertexes()[i].data ;
        std::cout <<" [" << i+1 << "]";
        std::cout << (i !=graph.getVertexCount())?  " ": "";
        
    }
    bool validOption = false;
    int inputOption = -1;
    size_t first = 0;
    size_t second = 0;
    while (validOption == false) {
        std::cout << "Please choose the first profile to be linked :\n";
        std::cin  >> inputOption;
        if(inputOption >0 && inputOption< graph.getVertexCount()+1){
            validOption = true;
            first = i;
        } else{
           std::cout << "Invalid number, please try again\n\n";
        }   
    }
    validOption = false;
    while (validOption == false) {
        std::cout << "Please choose the second profile to be linked :\n";
        std::cin  >> inputOption;
        if(inputOption >0 && inputOption< graph.getVertexCount()+1){
            validOption = true;
            second = i;
        } else{
           std::cout << "Invalid number, please try again\n\n";
        }
    }
    validOption = false;
    bool succes = false;
    while (validOption == false) {
        std::cout << "Please choose the type of relationship that they have :\n";
        std::cout << "[1]Friendship\n[2]Romantic Relationship\n[3]Family Member\n[4]Coworker\n";
        std::cin  >> inputOption;
        if(inputOption >0 && inputOption< 5){
            validOption = true;
            succes = graph.addLink(graph.getVertexes()[first], graph.getVertexes()[second], inputOption);
        } else{
           std::cout << "Invalid number, please try again\n\n";
        }
    }
    std::cout << (succes)?  "The relationship was added succesfully": "The relationship wasnt able to be added.";
}

void printProfile(grph::Graph<std::string, std::string>& graph){
    std::cout << "What profile do you want to see?\n";
    for (size_t i = 0; i < graph.getVertexCount(); i++){
        std::cout << graph.getVertexes()[i].data ;
        std::cout <<" [" << i+1 << "]";
        std::cout << (i !=graph.getVertexCount())?  " ": "";
        
    }
    bool validOption = false;
    size_t vertexIndex = 0;
    while (validOption == false) {
        std::cout << "Please choose the profile to be seen :\n";
        std::cin  >> inputOption;
        if(inputOption >0 && inputOption< graph.getVertexCount()+1){
            validOption = true;
            vertexIndex = inputOption;
        } else{
           std::cout << "Invalid number, please try again\n\n";
        }   
    }
    std::cout <<"Name: " << graph.getVertexes()[vertexIndex].data<< "\n" << "Relationships:\n";
    grph::Vertex<std::string, std::string>** vertexNeighbors =
    graph.getNeighbors(graph.getVertexes()[vertexIndex]);
    for (size_t  i = 0; i < graph.getVertexes()[vertexIndex].getLinkCount; i++){
       std::cout << graph.getVertexes()[i].data << " " << vertex.getLinkWeight(graph.whereIsLink(graph.getVertexes()[vertexIndex],graph.getVertexes()[i])) <<"\n";
    }
    
}


