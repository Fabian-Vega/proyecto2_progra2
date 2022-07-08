#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/graph.hpp"

TEST_CASE("tests"){
  grph::Graph<std::string, int, true> prueba(3, false);
    grph::Vertex<std::string> cities[3] = {
      grph::Vertex<std::string>(std::string("Boston")),
      grph::Vertex<std::string>(std::string("New York")),
      grph::Vertex<std::string>(std::string("Las Vegas"))
    };
  // Should return true because we haven't added anything yet
  REQUIRE(prueba.isEmpty()==true);
  // Should return true because we are adding a non added before vertex
  REQUIRE(prueba.addVertex(cities[0]) == true);
  // Should return false because we already added a vertex
  REQUIRE(prueba.isEmpty()==false);
  // Should return true because we are adding a non added before vertex
  REQUIRE(prueba.addVertex(cities[1]) == true);
  // Should return true because we are adding a non added before vertex
  grph::Vertex<std::string>& boston = *prueba.getVertexes()[0];
  grph::Vertex<std::string>& york = *prueba.getVertexes()[1];
  REQUIRE(prueba.addVertex(boston) == false);
  // Should return 2 because that is the amount of vertexes that are in the graph
  REQUIRE(prueba.getVertexCount()== 2);
  // Should return true because the non existent link was created succesfully
  int weights[3] = {801, 367, 72345};
  REQUIRE(prueba.addLink(boston, york, weights[0])==true);
  // Should return false because the existent link was already created
  REQUIRE(prueba.addLink(boston, york, weights[0])==false);
  // Should return 2 because of the correct creation of the previous link
  grph::Vertex<std::string>& vegas = *prueba.getVertexes()[2];
  prueba.addVertex(vegas);
  //prueba.addLink(boston, vegas, weights[1]);
  REQUIRE(boston.getLinkCount() == 1);
  // Should return 801 because of the correct creation of the previous link
  REQUIRE(prueba.getLink(boston, york) == 801);
  // Should return true if deleting was  succesful
  REQUIRE(prueba.removeVertex(york)==true);
  // Should return 1 because that is the amount of vertexes that are in the graph
  REQUIRE(prueba.getVertexCount()== 1);

}
