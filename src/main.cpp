/// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "graph.hpp"

int main(void) {
  try {
    grph::Graph<std::string, long long> grafo(3, false);
    grph::Vertex<std::string, long long>* boston = new grph::Vertex<std::string, long long>((std::string("Boston")));
    grph::Vertex<std::string, long long>* york = new grph::Vertex<std::string, long long>((std::string("New York")));
    grph::Vertex<std::string, long long>* vegas = new grph::Vertex<std::string, long long>((std::string("Las Vegas")));
    grph::Vertex<std::string, long long>* chicago = new grph::Vertex<std::string, long long>((std::string("Chicago")));
    grph::Vertex<std::string, long long>* angeles = new grph::Vertex<std::string, long long>((std::string("Los Angeles")));
    grph::Vertex<std::string, long long>* francisco = new grph::Vertex<std::string, long long>((std::string("San Franciso")));
    grph::Vertex<std::string, long long>* perez = new grph::Vertex<std::string, long long>((std::string("Perez Zeledon")));

    grafo.addVertex(boston);
    grafo.addVertex(york);
    grafo.addVertex(vegas);
    grafo.addVertex(chicago);
    grafo.addVertex(angeles);
    grafo.addVertex(francisco);
    grafo.addVertex(perez);

    long long weights[7] = {80, 3, 26, 18, 43, 786345, 69420};

    grafo.addLink(boston, york, weights[0]);
    grafo.addLink(boston, vegas, weights[1]);
    grafo.addLink(boston, chicago, weights[2]);
    grafo.addLink(boston, angeles, weights[3]);
    grafo.addLink(boston, francisco, weights[4]);
    grafo.addLink(boston, perez, weights[5]);
    grafo.setLink(perez, boston, weights[6]);
    
    grph::Vertex<std::string, long long>** bostonNeighbors =
    grafo.getNeighbors(boston);
    std::cout << "\nLas ciudades vecinas de Boston son: \n";
    for (size_t city = 0; city < 6; ++city) {
      std::cout << bostonNeighbors[city]->getData() 
      << " con una distacia de : " << grafo(boston, bostonNeighbors[city]) 
      << std::endl;;
    }
    delete [] bostonNeighbors;

    grph::Graph<std::string, long long> grafo2(grafo);

    std::cout << "\nLa distancia entre Boston y New York es: "
    << grafo2.getLink(boston, york) << std::endl;
    std::cout << "\nLa distancia entre Boston y Las Vegas es: "
    << grafo2.getLink(boston, vegas) << std::endl;
    std::cout << "\nLa distancia entre Boston y Chicago es: "
    << grafo2.getLink(boston, chicago) << std::endl;
    std::cout << "\nLa distancia entre Boston y Los Angeles es: "
    << grafo2.getLink(boston, angeles) << std::endl;
    std::cout << "\nLa distancia entre Boston y Sam Francisco es: "
    << grafo2.getLink(boston, francisco) << std::endl;
    std::cout << "\nLa distancia entre Boston y Perez Zeledón es: "
    << grafo2.getLink(boston, perez) << std::endl;
    std::cout << "\nLa distancia entre Perez Zeledón y Boston es: "
    << grafo2.getLink(perez, boston) << std::endl;
    
    grph::Vertex<std::string, long long>** bNeighboors =
    grafo.getNeighbors(boston);
    std::cout << "\nLas ciudades vecinas de Boston son: \n";
    for (size_t city = 0; city < 6; ++city) {
      std::cout << bNeighboors[city]->getData() 
      << " con una distacia de : " << grafo(boston, bNeighboors[city]) 
      << std::endl;;
    }
    delete [] bNeighboors;

    delete boston;
    delete york;
    delete vegas;
    delete chicago;
    delete angeles;
    delete francisco;
    delete perez;

  } catch (const std::runtime_error& error) {
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}