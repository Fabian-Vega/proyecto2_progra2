/// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "../src/Graph.hpp"

int main(void) {
  try {
    // Create a graph class object
    grph::Graph<std::string, int, false> graph(3, false);
    // Creates vertexes for furture use
    grph::Vertex<std::string> cities[7] = {
      grph::Vertex<std::string>(std::string("Boston")),
      grph::Vertex<std::string>(std::string("New York")),
      grph::Vertex<std::string>(std::string("Las Vegas")),
      grph::Vertex<std::string>(std::string("Chicago")),
      grph::Vertex<std::string>(std::string("Los Angeles")),
      grph::Vertex<std::string>(std::string("San Francisco")),
      grph::Vertex<std::string>(std::string("Perez Zeledon"))
    };
    // Array that contains the weigths to add to the vertexes
    int weights[7] = {80, 3, 26, 18, 43, 786345, 69420};
    // Adding vertexes to the graph
    graph.addVertex(cities[0]);
    graph.addVertex(cities[1]);
    graph.addVertex(cities[2]);
    graph.addVertex(cities[3]);
    graph.addVertex(cities[4]);
    graph.addVertex(cities[5]);
    graph.addVertex(cities[6]);

    // This proccess makes the vertexes usable via a refrence
    grph::Vertex<std::string>& boston = *graph.getVertexes()[0];
    grph::Vertex<std::string>& york = *graph.getVertexes()[1];
    grph::Vertex<std::string>& vegas = *graph.getVertexes()[2];
    grph::Vertex<std::string>& chicago = *graph.getVertexes()[3];
    grph::Vertex<std::string>& angeles = *graph.getVertexes()[4];
    grph::Vertex<std::string>& francisco = *graph.getVertexes()[5];
    grph::Vertex<std::string>& perez = *graph.getVertexes()[6];
    // Creates Links with weight between vertexes
    graph.addLink(boston, york, weights[0]);
    graph.addLink(boston, vegas, weights[1]);
    graph.addLink(boston, chicago, weights[2]);
    graph.addLink(boston, angeles, weights[3]);
    graph.addLink(boston, francisco, weights[4]);
    graph.addLink(boston, perez, weights[5]);
    graph.setLink(perez, boston, weights[6]);
    // Testing if we remove a vertex with a link
    graph.removeVertex(vegas);
    // Creates a string of vertexes with the neighbors of boston
    grph::Vertex<std::string>** bostonNeighbors =
    graph.getNeighbors(boston);
    // Prints the neighbors of Boston
    std::cout << "\nLas ciudades vecinas de Boston son: \n";
    // Cycle for  printing the distance between cities
    for (size_t city = 0; city < boston.getLinkCount(); ++city) {
      std::cout << bostonNeighbors[city]->getData()
      << " con una distacia de : " << graph(boston, *bostonNeighbors[city])
      << std::endl;;
    }
    // Releases the heap memory that was used during this proccess
    delete [] bostonNeighbors;
    // Creates a graph class object using the move constructor
    grph::Graph<std::string, int, false> graph2(std::move(graph));
    // This proccess makes the vertexes usable via a refrence
    grph::Vertex<std::string>& boston2 = *graph2.getVertexes()[0];
    grph::Vertex<std::string>& york2 = *graph2.getVertexes()[1];
    grph::Vertex<std::string>& chicago2 = *graph2.getVertexes()[2];
    grph::Vertex<std::string>& angeles2 = *graph2.getVertexes()[3];
    grph::Vertex<std::string>& francisco2 = *graph2.getVertexes()[4];
    grph::Vertex<std::string>& perez2 = *graph2.getVertexes()[5];

    // Prints the distance between cities
    std::cout << "\nLa distancia entre Boston y New York es: "
    << graph2.getLink(boston2, york2) << std::endl;
    std::cout << "\nLa distancia entre Boston y Chicago es: "
    << graph2.getLink(boston2, chicago2) << std::endl;
    std::cout << "\nLa distancia entre Boston y Los Angeles es: "
    << graph2.getLink(boston2, angeles2) << std::endl;
    std::cout << "\nLa distancia entre Boston y Sam Francisco es: "
    << graph2.getLink(boston2, francisco2) << std::endl;
    std::cout << "\nLa distancia entre Boston y Perez Zeledón es: "
    << graph2.getLink(boston2, perez2) << std::endl;
    std::cout << "\nLa distancia entre Perez Zeledón y Boston es: "
    << graph2.getLink(perez2, boston2) << std::endl;
    // Creates a string of vertexes with the neighbors of boston2
    grph::Vertex<std::string>** bNeighbors =
    graph2.getNeighbors(boston2);
    // Prints the neighbors of boston2
    std::cout << "\nLas ciudades vecinas de Boston son:" << std::endl;
    // Cycle for  printing the distance between cities
    for (size_t city = 0; city < boston2.getLinkCount(); ++city) {
      std::cout << bNeighbors[city]->getData() 
      << " con una distacia de : " << graph2(boston2, *bNeighbors[city])
      << std::endl;
    }
    // Releases the heap memory that was used during this proccess
    delete [] bNeighbors;
    graph.clear();
    graph2.clear();

  } catch (const std::runtime_error& error) {
    // Exception
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}
