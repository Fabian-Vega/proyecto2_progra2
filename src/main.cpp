// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

int main(void) {
  try {
    grph::Graph<std::string, double> grafo(18, true);
    grafo.addVertex(std::string("Boston"));
    grafo.addVertex(std::string("New York"));
    grafo.addVertex(std::string("Las Vegas"));
    grafo.addVertex(std::string("Chicago"));
    grafo.addVertex(std::string("Los Angeles"));
    grafo.addVertex(std::string("San Franciso"));
    grafo.addVertex(std::string("Perez Zeledon"));

    grafo.addEdge(std::string("Boston"),
    std::string("New York"), 80.7);
    grafo.addEdge(std::string("Boston"),
    std::string("Chicago"), 20.7);
    grafo.addEdge(std::string("Boston"),
    std::string("Las Vegas"), 120.4);
    grafo.addEdge(std::string("Boston"),
    std::string("San Francisco"), 10.2);
    grafo.addEdge(std::string("San Francisco"),
    std::string("Perez Zeledon"), 800.9);
    grafo.addEdge(std::string("San Francisco"),
    std::string("Chicago"), 150.9);
    grafo.addEdge(std::string("New York"),
    std::string("Las Vegas"), 50.1);

    std::cout << "\nLa distancia entre Boston y New York es: "
    << grafo.getEdge(std::string("Boston"), std::string("New York"))
    << std::endl;
    std::cout << "\nLa distancia entre Boston y San Francisco es: "
    << grafo.getEdge(std::string("Boston"), std::string("San Francisco"))
    << std::endl;
    std::cout << "\nLa distancia entre Boston y Las Vegas es: "
    << grafo.getEdge(std::string("Boston"), std::string("Las Vegas"))
    << std::endl;
    std::cout << "\nLa distancia entre New York y Las Vegas es: "
    << grafo.getEdge(std::string("New York"), std::string("Las Vegas"))
    << std::endl;
  } catch (const std::runtime_error& error) {
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}
