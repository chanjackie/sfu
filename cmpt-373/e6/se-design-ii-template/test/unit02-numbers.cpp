#include "doctest.h"

#include "Support.h"
#include "task02.h"

#include <numeric>
#include <sstream>
#include <unordered_map>

using ex6::task2::NumberGraph;


// We can specialize the StringMaker template for types that appear on
// both sides of an `==` in a doctest check. This allows us to get better
// printed messages for the data used within the assertions.
namespace doctest {

template <>
struct StringMaker<std::vector<NumberGraph::NodeID>> {
  static String convert(const std::vector<NumberGraph::NodeID>& in) {
    std::ostringstream oss;
    oss << "[ ";
    for (const auto& id : in) {
      oss << id.position << " ";
    }
    oss << "]";
    return oss.str().c_str();
  }
};

}


////////////////////////////////////////////////////////////////////////////////
//  The first set of tests explore the paths found using a simple graph where
//  each node is labeled with a number and each edge has a fixed weight.
////////////////////////////////////////////////////////////////////////////////


TEST_CASE("Disconnected") {
  ex6::task2::NumberGraph graph;
  auto source = graph.createNode(1);
  auto target = graph.createNode(2);

  auto result = shortestPath(graph, source, target);

  CHECK(result.empty());
}


TEST_CASE("Path to self") {
  ex6::task2::NumberGraph graph;
  auto source = graph.createNode(1);

  auto result = shortestPath(graph, source, source);
  const std::vector<ex6::task2::NumberGraph::NodeID> expected = {
    source
  };

  CHECK(expected == result);
}


TEST_CASE("Unique path to neighbor") {
  ex6::task2::NumberGraph graph;
  auto source = graph.createNode(1);
  auto target = graph.createNode(2);
  graph.addEdge(source, target, 3);

  auto result = shortestPath(graph, source, target);
  const std::vector<ex6::task2::NumberGraph::NodeID> expected = {
    source,
    target
  };

  CHECK(expected == result);
}


TEST_CASE("Shortest of two") {
  ex6::task2::NumberGraph graph;
  auto source = graph.createNode(1);
  auto middle = graph.createNode(2);
  auto target = graph.createNode(3);
  graph.addEdge(source, target, 3);
  graph.addEdge(source, middle, 1);
  graph.addEdge(middle, target, 1);

  auto result = shortestPath(graph, source, target);
  const std::vector<ex6::task2::NumberGraph::NodeID> expected = {
    source,
    middle,
    target
  };

  CHECK(expected == result);
}


TEST_CASE("Tolerates cycles") {
  ex6::task2::NumberGraph graph;
  auto source = graph.createNode(1);
  auto middle = graph.createNode(2);
  auto target = graph.createNode(3);
  graph.addEdge(source, target, 4);
  graph.addEdge(source, middle, 1);
  graph.addEdge(middle, middle, 0);
  graph.addEdge(middle, target, 2);

  auto result = shortestPath(graph, source, target);
  const std::vector<ex6::task2::NumberGraph::NodeID> expected = {
    source,
    middle,
    target
  };

  CHECK(expected == result);
}


