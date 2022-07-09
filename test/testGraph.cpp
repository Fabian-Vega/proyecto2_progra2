#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/graph.hpp"

TEST_CASE("tests"){
  grph::Graph<std::string, int, true> prueba(3, true);
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
  // Should return true because we are adding a non added before vertex
  REQUIRE(prueba.addVertex(cities[2]) == true);
  grph::Vertex<std::string>& vegas = *prueba.getVertexes()[2];
  // Should return false because the link was already created
  REQUIRE(prueba.addVertex(vegas) == false);
  // Should return true because the non existent link was created succesfully
  REQUIRE( prueba.addLink(boston, vegas, weights[1])==true);
  REQUIRE(boston.getLinkCount() == 2);
  // Should return 801 because of the correct creation of the previous link
  REQUIRE(prueba.getLink(boston, york) == 801);
  // Should return true if deleting was  succesful
  REQUIRE(prueba.removeVertex(york)==true);
  // Should return 2 because that is the amount of vertexes that are in the graph
  REQUIRE(prueba.getVertexCount()== 2);


  grph::Graph<std::string, int, false> prueba2(3, false);
    grph::Vertex<std::string> citiesCr[3] = {
      grph::Vertex<std::string>(std::string("Cartago")),
      grph::Vertex<std::string>(std::string("Puntarenas")),
      grph::Vertex<std::string>(std::string("Limon"))
    };
  // Should return true because we haven't added anything yet
  REQUIRE(prueba2.isEmpty()==true);
  // Should return true because we are adding a non added before vertex
  REQUIRE(prueba2.addVertex(citiesCr[0]) == true);
  // Should return false because we already added a vertex
  REQUIRE(prueba2.isEmpty()==false);
  // Should return true because we are adding a non added before vertex
  REQUIRE(prueba2.addVertex(citiesCr[1]) == true);
  // Should return true because we are adding a non added before vertex
  grph::Vertex<std::string>& cartago = *prueba2.getVertexes()[0];
  grph::Vertex<std::string>& puntarenas = *prueba2.getVertexes()[1];
  REQUIRE(prueba2.addVertex(cartago) == false);
  // Should return 2 because that is the amount of vertexes that are in the graph
  REQUIRE(prueba2.getVertexCount()== 2);
  // Should return true because the non existent link was created succesfully
  int weightsCr[3] = {801, 367, 72345};
  REQUIRE(prueba2.addLink(cartago, puntarenas, weightsCr[0])==true);
  // Should return false because the existent link was already created
  REQUIRE(prueba2.addLink(cartago, puntarenas, weightsCr[0])==false);
  // Should return 2 because of the correct creation of the previous link
  // Should return true because we are adding a non added before vertex
  // ***Agregue el vertice al vertex
  REQUIRE(prueba2.addVertex(citiesCr[2]) == true);
  grph::Vertex<std::string>& limon = *prueba2.getVertexes()[2];
  // Should return false because the link was already created
  REQUIRE(prueba2.addVertex(limon) == false);
  // Should return true because the non existent link was created succesfully
  REQUIRE( prueba2.addLink(cartago, limon, weightsCr[1])==true);
  // ***Cambio aqui de 1 a 2
  REQUIRE(cartago.getLinkCount() == 2);
  // Should return 801 because of the correct creation of the previous link
  REQUIRE(prueba2.getLink(cartago, puntarenas) == 801);
  // Should return true if deleting was  succesful
  REQUIRE(prueba2.removeVertex(puntarenas)==true);
  // Should return 1 because that is the amount of vertexes that are in the graph
  // ***Lo cambie a 2 porque deberian haber 2
  REQUIRE(prueba2.getVertexCount()== 2);
}
