#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/graph.hpp"

TEST_CASE("tests"){

    grph::Graph<std::string, long long> prueba1(3, false);

    // Should return true because we have not added any vertex or link
    REQUIRE(prueba1.isEmpty() == true);

    // Should return true because the adding of an existing vertex was succesful
    grph::Vertex<std::string, long long>* boston = new grph::Vertex<std::string, long long>((std::string("Boston")));
    REQUIRE(prueba1.addVertex(boston) == true);

    // Should return false because we added a vertex to the graph
    REQUIRE(prueba1.isEmpty() == false);

    // Should return false because the vertex was already added
    REQUIRE(prueba1.addVertex(boston) == false);

    // Should return 2, because it is the amount of vertex we have added
    REQUIRE(prueba1.getVertexCount() == 1);

    // Should return true beacause we are creating a link between 2 existent and added vertex
    grph::Vertex<std::string, long long>* york = new grph::Vertex<std::string, long long>((std::string("New York")));
    prueba1.addVertex(boston);
    prueba1.addVertex(york);
    long long weights[7] = {80, 3, 26, 18, 43, 786345, 69420};
    REQUIRE(prueba1.addLink(boston, york, weights[0]) == true);

    // Should return false beacause we already created a link between 2 existent and added vertex
    REQUIRE(prueba1.addLink(boston, york, weights[0]) == false);

    // Should return 80 because the function returns the weight of the link
    REQUIRE(prueba1.getLink(boston, york) == 80);

    //Should return 1 because we are creating a link between two vertex
    prueba1.addLink(boston, york, weights[0]);
    REQUIRE(boston->getLinkCount() == 1);

    // Should return 2, because it is the amount of vertex we have added
    REQUIRE(prueba1.getVertexCount() == 2);

    //Should return true because we are removing an already added vertex
    REQUIRE(prueba1.removeVertex(boston) == true);

    //Should return false because we are removing an already removed vertex
    REQUIRE(prueba1.removeVertex(boston) == false);

    // Should return 2, because it is the amount of vertex we have added
    REQUIRE(prueba1.getVertexCount() == 1);

    // Should return 0 because are removing all the vertex that were in the graph
    prueba1.removeVertex(boston);
    prueba1.removeVertex(york);
    REQUIRE(prueba1.getVertexCount() == 0);

}