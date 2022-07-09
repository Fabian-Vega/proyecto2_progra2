/// Copyright [2022] <Alejandro B, Fabian V, Kenneth V>

#include <iostream>
#include <string>

#include "../src/Graph.hpp"

void testMatrix(const bool directed) {
  // Create a graph class object
    grph::Graph<std::string, int> graph(3, directed);
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
    grph::Graph<std::string, int> graph2(std::move(graph));
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
}

void testList(const bool directed) {
  // Create a graph class object
    grph::Graph<long double, bool> graph(3, directed);
    // Creates vertexes for furture use
    grph::Vertex<long double> numbers[7] = {
      grph::Vertex<long double>(3234567.345678),
      grph::Vertex<long double>(-33321.987654),
      grph::Vertex<long double>(5.98765678),
      grph::Vertex<long double>(-8.0),
      grph::Vertex<long double>(13.00000001),
      grph::Vertex<long double>(-21.3292923),
      grph::Vertex<long double>(420.6923)
    };
    // Array that contains the weigths to add to the vertexes
    bool isMultNegative[2] = {false, true};
    // Adding vertexes to the graph
    graph.addVertex(numbers[0]);
    graph.addVertex(numbers[1]);
    graph.addVertex(numbers[2]);
    graph.addVertex(numbers[3]);
    graph.addVertex(numbers[4]);
    graph.addVertex(numbers[5]);
    graph.addVertex(numbers[6]);

    // This proccess makes the vertexes usable via a refrence
    grph::Vertex<long double>& first = *graph.getVertexes()[0];
    grph::Vertex<long double>& second = *graph.getVertexes()[1];
    grph::Vertex<long double>& third = *graph.getVertexes()[2];
    grph::Vertex<long double>& fourth = *graph.getVertexes()[3];
    grph::Vertex<long double>& fifth = *graph.getVertexes()[4];
    grph::Vertex<long double>& sixth = *graph.getVertexes()[5];
    grph::Vertex<long double>& seventh = *graph.getVertexes()[6];

    // Creates Links with weight between vertexes
    graph.addLink(first, second, isMultNegative[1]);
    graph.addLink(fifth, second, isMultNegative[1]);
    graph.addLink(fourth, fifth, isMultNegative[1]);
    graph.addLink(seventh, seventh, isMultNegative[0]);
    graph.addLink(third, fourth, isMultNegative[1]);
    graph.addLink(second, sixth, isMultNegative[0]);
    graph.addLink(sixth, sixth, isMultNegative[0]);
    // Testing if we remove a vertex with a link
    graph.removeVertex(second);
    // Creates a string of vertexes with the neighbors of fifth
    grph::Vertex<long double>** fifthNeightbors =
    graph.getNeighbors(fifth);
    // Prints the neighbors of fifth
    std::cout << "\nLos números vecinos de 13.00000001 son: \n";
    // Cycle for  printing the if the multiplication of numbers is
    // positive or negative
    for (size_t number = 0; number < fifth.getLinkCount(); ++number) {
      std::cout << fifthNeightbors[number]->getData()
      << " y su multiplicación es " << 
      (graph(fifth, *fifthNeightbors[number])? "positiva!":"negativa!")
      << std::endl;
    }
    // If in the case that fifth doesnt have neighrbors
    // print thats as information
    if (fifth.getLinkCount() == 0) {
      std::cout << "ninguno! ....que triste :( " 
      << std::endl;
    }

    // Releases the heap memory that was used during this proccess
    delete [] fifthNeightbors;

    // Creates a graph class object using the move constructor
    grph::Graph<long double, bool> graph2(std::move(graph));
    // This proccess makes the vertexes usable via a refrence
    grph::Vertex<long double>& third2 = *graph2.getVertexes()[1];
    grph::Vertex<long double>& fourth2 = *graph2.getVertexes()[2];
    grph::Vertex<long double>& fifth2 = *graph2.getVertexes()[3];
    grph::Vertex<long double>& sixth2 = *graph2.getVertexes()[4];
    grph::Vertex<long double>& seventh2 = *graph2.getVertexes()[5];

    // Prints if the multiplication is positive or negative
    std::cout << "\nLa multiplicacion entre -8.0 y 13.00000001 es: "
    << (graph2.getLink(fourth, fifth)? "positiva!":"negativa!")
    << std::endl;
    std::cout << "\nLa multiplicacion entre 420.6923 y 420.6923 es: "
    << (graph2.getLink(seventh2, seventh2)? "positiva!":"negativa!")
    << std::endl;
    std::cout << "\nLa multiplicacion entre 5.98765678 y -8.0 es: "
    << (graph2.getLink(third2, fourth2)? "positiva!":"negativa!")
    << std::endl;
    std::cout << 
    "\nLa multiplicacion entre -21.3292923 y -21.3292923 es: "
    << (graph2.getLink(sixth2, sixth2)? "positiva!":"negativa!")
    << std::endl;
    
    // Creates a string of vertexes with the neighbors of fifth2
    grph::Vertex<long double>** fifth2Neighbors =
    graph2.getNeighbors(fifth2);
    // Prints the neighbors of fifth2
    std::cout << "\nLos numeros vecinos de 13.00000001 son:" << std::endl;
    // Cycle for  printing the if the multiplication of numbers is
    // positive or negative
    for (size_t number = 0; number < fifth2.getLinkCount(); ++number) {
      std::cout << fifth2Neighbors[number]->getData() 
      << " y su multiplicación es " << 
      (graph(fifth2, *fifth2Neighbors[number])? "positiva!":"negativa!")
      << std::endl;;
    }
    // If in the case that fifth2 doesnt have neighrbors
    // print thats as information
    if (fifth2.getLinkCount() == 0) {
      std::cout << "ninguno! ....que triste :( " 
      << std::endl;
    }
    // Releases the heap memory that was used during this proccess
    delete [] fifth2Neighbors;
    graph.clear();
    graph2.clear();
}

int main(void) {
  try {
    // Test the matrix version and the list version
    // of the graph template
    testMatrix(false);
    testList(true);
  } catch (const std::runtime_error& error) {
    // Exception
    std::cerr << "main error: " << error.what() << std::endl;
  }

  return 0;
}
