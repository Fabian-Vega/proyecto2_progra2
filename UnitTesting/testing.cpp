#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/graph.hpp"

TEST_CASE("Unit Testing") {
    grph::Graph<std::string, long long> prueba1(3, false);

    // It should return false because we haven't added any vertex nor link to the graph
    REQUIRE(prueba1.isEmpty()==true);

    // Adds a vertex, because of the vertex wasn't in the graph before, it returns true
    grph::Vertex<std::string, long long>* boston = new grph::Vertex<std::string, long long>((std::string("Boston")));
    REQUIRE(prueba1.addVertex(boston)==true);
}
