#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/graph.hpp"

TEST_CASE("tests"){

    grph::Graph<std::string, long long> prueba1(3, false);
    grph::Vertex<std::string> cities[2] = {
      grph::Vertex<std::string>(std::string("Boston")),
      grph::Vertex<std::string>(std::string("New York"))
    };

    long long weights[7] = {80, 3, 26};

    // Should return true because we have not added any vertex or link
    REQUIRE(prueba1.isEmpty() == true);

    // Should return true because the adding of an existing vertex was succesful
    prueba1.addVertex(cities[0]);
    REQUIRE(prueba1.addVertex(cities[0]) == true);

    // Should return false because we added a vertex to the graph
    REQUIRE(prueba1.isEmpty() == false);

    // Should return false because the vertex was already added
    prueba1.addVertex(cities[0]);
    REQUIRE(prueba1.addVertex(cities[0]) == false);

    // Should return 2, because it is the amount of vertex we have added
    REQUIRE(prueba1.getVertexCount() == 1);

    // Should return true beacause we are creating a link between 2 existent and added vertex
    prueba1.addVertex(cities[1]);
    REQUIRE(prueba1.addLink(cities[0], cities[1], weights[0]) == true);

    // Should return false beacause we already created a link between 2 existent and added vertex
    REQUIRE(prueba1.addLink(cities[0], cities[1], weights[0]) == false);

    // Should return 80 because the function returns the weight of the link
    REQUIRE(prueba1.getLink(cities[0], cities[1]) == 80);

    //Should return 1 because we are creating a link between two vertex
    prueba1.addLink(cities[0], cities[1], weights[0]);
    REQUIRE(cities[0].getLinkCount() == 1);

    // Should return 2, because it is the amount of vertex we have added
    REQUIRE(prueba1.getVertexCount() == 2);

    //Should return true because we are removing an already added vertex
    REQUIRE(prueba1.removeVertex(cities[0]) == true);

    //Should return false because we are removing an already removed vertex
    REQUIRE(prueba1.removeVertex(cities[0]) == false);

    // Should return 2, because it is the amount of vertex we have added
    REQUIRE(prueba1.getVertexCount() == 1);

    // Should return 0 because are removing all the vertex that were in the graph
    prueba1.removeVertex(cities[0]);
    prueba1.removeVertex(cities[1]);
    REQUIRE(prueba1.getVertexCount() == 0);

}