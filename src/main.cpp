// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

int main(void) {
  try {
    //xd
    grph::Graph<std::string, long long> grafo(3, true);
    grph::Vertex<std::string, long long> boston((std::string("Boston")));
    grph::Vertex<std::string, long long> york((std::string("New York")));
    grph::Vertex<std::string, long long> vegas((std::string("Las Vegas")));
    grph::Vertex<std::string, long long> chicago((std::string("Chicago")));
    grph::Vertex<std::string, long long> angeles((std::string("Los Angeles")));
    grph::Vertex<std::string, long long> francisco((std::string("San Franciso")));
    grph::Vertex<std::string, long long> perez((std::string("Perez Zeledon")));

    grafo.addVertex(boston);
    grafo.addVertex(york);
    grafo.addVertex(vegas);
    grafo.addVertex(chicago);
    grafo.addVertex(angeles);
    grafo.addVertex(francisco);
    grafo.addVertex(perez);

    long long weights[7] = {80, 3, 26, 18, 43, 786345, 69420};
    //grafo.removeVertex(francisco);
    grafo.addLink(boston, york, weights[0]);
    grafo.addLink(boston, vegas, weights[1]);
    grafo.addLink(boston, chicago, weights[2]);
    grafo.addLink(boston, angeles, weights[3]);
    grafo.addLink(boston, francisco, weights[4]);
    grafo.addLink(boston, perez, weights[5]);
    grafo.addLink(perez, boston, weights[6]);

    std::cout << "\nLa distancia entre Boston y New York es: "
    << grafo.getLink(boston, york) << std::endl;
    std::cout << "\nLa distancia entre Boston y Las Vegas es: "
    << grafo.getLink(boston, vegas) << std::endl;
    std::cout << "\nLa distancia entre Boston y Chicago es: "
    << grafo.getLink(boston, chicago) << std::endl;
    std::cout << "\nLa distancia entre Boston y Los Angeles es: "
    << grafo.getLink(boston, angeles) << std::endl;
    std::cout << "\nLa distancia entre Boston y Sam Francisco es: "
    << grafo.getLink(boston, francisco) << std::endl;
    std::cout << "\nLa distancia entre Boston y Perez Zeledón es: "
    << grafo.getLink(boston, perez) << std::endl;
    std::cout << "\nLa distancia entre Perez Zeledón y Boston es: "
    << grafo.getLink(perez, boston) << std::endl;
    
  } catch (const std::runtime_error& error) {
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}
