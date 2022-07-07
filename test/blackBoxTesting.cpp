/// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "../src/Graph.hpp"

int main(void) {
  try {
    grph::Graph<std::string, int> graph(3, false);
    grph::Vertex<std::string> cities[7] = {
      grph::Vertex<std::string>(std::string("Boston")),
      grph::Vertex<std::string>(std::string("New York")),
      grph::Vertex<std::string>(std::string("Las Vegas")),
      grph::Vertex<std::string>(std::string("Chicago")),
      grph::Vertex<std::string>(std::string("Los Angeles")),
      grph::Vertex<std::string>(std::string("San Francisco")),
      grph::Vertex<std::string>(std::string("Perez Zeledon"))
    };

    int weights[7] = {80, 3, 26, 18, 43, 786345, 69420};

    graph.addVertex(cities[0]);
    graph.addVertex(cities[1]);
    graph.addVertex(cities[2]);
    graph.addVertex(cities[3]);
    graph.addVertex(cities[4]);
    graph.addVertex(cities[5]);
    graph.addVertex(cities[6]);

    grph::Vertex<std::string>& boston = *graph.getVertexes()[0];
    grph::Vertex<std::string>& york = *graph.getVertexes()[0];
    grph::Vertex<std::string>& vegas = *graph.getVertexes()[0];
    grph::Vertex<std::string>& chicago = *graph.getVertexes()[0];
    grph::Vertex<std::string>& angeles = *graph.getVertexes()[0];
    grph::Vertex<std::string>& francisco = *graph.getVertexes()[0];
    grph::Vertex<std::string>& perez = *graph.getVertexes()[0];

    graph.addLink(boston, york, weights[0]);
    graph.addLink(boston, vegas, weights[1]);
    graph.addLink(boston, chicago, weights[2]);
    graph.addLink(boston, angeles, weights[3]);
    graph.addLink(boston, francisco, weights[4]);
    graph.addLink(boston, perez, weights[5]);
    graph.setLink(perez, boston, weights[6]);

    graph.removeVertex(vegas);

    grph::Vertex<std::string>** bostonNeighbors =
    graph.getNeighbors(boston);
    std::cout << "\nLas ciudades vecinas de Boston son: \n";
    for (size_t city = 0; city < boston.getLinkCount(); ++city) {
      std::cout << bostonNeighbors[city]->getData()
      << " con una distacia de : " << graph(boston, *bostonNeighbors[city])
      << std::endl;;
    }
    delete [] bostonNeighbors;

    grph::Graph<std::string, int> graph2(graph);

    std::cout << "\nLa distancia entre Boston y New York es: "
    << graph2.getLink(boston, york) << std::endl;
    std::cout << "\nLa distancia entre Boston y Las Vegas es: "
    << graph2.getLink(boston, vegas) << std::endl;
    std::cout << "\nLa distancia entre Boston y Chicago es: "
    << graph2.getLink(boston, chicago) << std::endl;
    std::cout << "\nLa distancia entre Boston y Los Angeles es: "
    << graph2.getLink(boston, angeles) << std::endl;
    std::cout << "\nLa distancia entre Boston y Sam Francisco es: "
    << graph2.getLink(boston, francisco) << std::endl;
    std::cout << "\nLa distancia entre Boston y Perez Zeledón es: "
    << graph2.getLink(boston, perez) << std::endl;
    std::cout << "\nLa distancia entre Perez Zeledón y Boston es: "
    << graph2.getLink(perez, boston) << std::endl;

    grph::Vertex<std::string>** bNeighboors =
    graph.getNeighbors(boston);
    std::cout << "\nLas ciudades vecinas de Boston son: \n";
    for (size_t city = 0; city < boston.getLinkCount(); ++city) {
      std::cout << bNeighboors[city]->getData()
      << " con una distacia de : " << graph(boston, *bNeighboors[city])
      << std::endl;;
    }
    delete [] bNeighboors;
    graph.clear();

  } catch (const std::runtime_error& error) {
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}
