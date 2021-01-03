#include "doctest.h"

#include "task02.h"

#include <numeric>
#include <sstream>
#include <unordered_map>

using ex5::task2::Node;


// The purpose of TestNode is to extend the Node interface with an additional
// method that can be used for getting a printable representation of a Node.
// It is used exclusively for debugging. There are other ways of achieving this
// objective, but this approach seems relevant to the exercise.
class TestNode : public Node {
public:
  TestNode() = default;
  TestNode(const TestNode&) = delete;
  TestNode(TestNode&&) = delete;

  TestNode& operator=(const TestNode&) = delete;
  TestNode& operator=(TestNode&&) = delete;

  [[nodiscard]] std::string getRepr() const noexcept { return getReprImpl(); }
private:
  [[nodiscard]] virtual std::string getReprImpl() const noexcept = 0;
};


// We can specialize the StringMaker template for types that appear on
// both sides of an `==` in a doctest check. This allows us to get better
// printed messages for the data used within the assertions.
namespace doctest {

template <>
struct StringMaker<std::vector<const ex5::task2::Node*>> {
  static String convert(const std::vector<const ex5::task2::Node*>& in) {
    std::ostringstream oss;
    oss << "[ ";
    for (const auto* node : in) {
      oss << static_cast<const TestNode*>(node)->getRepr() << " ";
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


class BasicNode final : public TestNode {
public:
  explicit BasicNode(int value)
    : value{value}
      { }

  void
  addEdge(const BasicNode& node, size_t weight) noexcept {
    edges.push_back(ex5::task2::Node::Edge{weight, &node});
  }

private:
  [[nodiscard]] std::vector<Edge>
  getSuccessorsImpl() const noexcept override {
    return edges;
  }

  [[nodiscard]] std::string
  getReprImpl() const noexcept override {
    return std::to_string(value);
  }

  int value;
  std::vector<ex5::task2::Node::Edge> edges;
};


TEST_CASE("Disconnected") {
  BasicNode source{1};
  BasicNode target{2};

  auto result = shortestPath(source, target);

  CHECK(result.empty());
}


TEST_CASE("Path to self") {
  BasicNode source{1};

  auto result = shortestPath(source, source);
  const std::vector<const ex5::task2::Node*> expected = {
    &source
  };

  CHECK(expected == result);
}


TEST_CASE("Unique path to neighbor") {
  BasicNode source{1};
  BasicNode target{2};
  source.addEdge(target, 3);

  auto result = shortestPath(source, target);
  const std::vector<const ex5::task2::Node*> expected = {
    &source,
    &target
  };

  CHECK(expected == result);
}


TEST_CASE("Shortest of two") {
  BasicNode source{1};
  BasicNode middle{2};
  BasicNode target{3};
  source.addEdge(target, 3);
  source.addEdge(middle, 1);
  middle.addEdge(target, 1);

  auto result = shortestPath(source, target);
  const std::vector<const ex5::task2::Node*> expected = {
    &source,
    &middle,
    &target
  };

  CHECK(expected == result);
}


TEST_CASE("Tolerates cycles") {
  BasicNode source{1};
  BasicNode middle{2};
  BasicNode target{3};
  source.addEdge(target, 4);
  source.addEdge(middle, 1);
  middle.addEdge(middle, 0);
  middle.addEdge(target, 2);

  auto result = shortestPath(source, target);
  const std::vector<const ex5::task2::Node*> expected = {
    &source,
    &middle,
    &target
  };

  CHECK(expected == result);
}


////////////////////////////////////////////////////////////////////////////////
//  The second set of tests explore the paths found using a graphs where the
//  node labels are strings and the weights of the edges are the squares of the
//  letter frequency similarity between two different words.
//
//  The turns the shortest path problem into a solution for finding the smallest
//  changes necessary to turn one word into an anagram of another and linking
//  these into a path of anagram transformations.
//
//  In addition, the string labels can change, which means that the edge weights
//  are not necessarily known a priori and are computed (either with each
//  label change or upon requesting the edges).
////////////////////////////////////////////////////////////////////////////////


static std::unordered_map<char, size_t>
getFrequencies(const std::string& str) noexcept {
  std::unordered_map<char, size_t> frequencies;
  for (auto c : str) {
    frequencies[c] += 1;
  }
  return frequencies;
}


static size_t
similarity(const std::string& first, const std::string& second) noexcept {
  std::unordered_map<char, size_t> frequencies1 = getFrequencies(first);
  std::unordered_map<char, size_t> frequencies2 = getFrequencies(second);
  size_t difference = 0;
  // NOTE: This is not the most efficient way to do this.
  // unordered_map is inefficient anyway, so we are asserting that we do not
  // really care about the performance of this code.
  for (const auto& [c, count] : frequencies1) {
    difference += abs(count - frequencies2[c]);
    frequencies2.erase(c);
  }
  return std::accumulate(frequencies2.begin(), frequencies2.end(), difference,
    [] (size_t sofar, auto kvPair) { return sofar + kvPair.second; });
}


class StringNode final : public TestNode {
public:
  explicit StringNode(std::string value)
    : value{std::move(value)}
      { }
  
  StringNode(const StringNode& other)
    : StringNode{other.value}
      { }

  void
  addNeighbor(const StringNode& node) noexcept {
    neighbors.push_back(&node);
  }

  void
  setString(std::string_view newValue) noexcept {
    value = newValue;
  }

private:
  // NOTE: In this kind of graph node, the edge weights are computed on the fly
  // instead of being statically determined. This is because the actual strings
  // contained within the neighbors may change. In spite of this, the algorithm
  // should just work because the interface for the graph nodes is still
  // respected.
  [[nodiscard]] std::vector<Edge>
  getSuccessorsImpl() const noexcept override {
    std::vector<ex5::task2::Node::Edge> edges;
    edges.reserve(neighbors.size());
    std::transform(neighbors.begin(), neighbors.end(), std::back_inserter(edges),
      [this] (auto* neighbor) {
        size_t distance = similarity(value, neighbor->value);
        // Using the square of the frequency distance will encourage using
        // longer paths of smaller changes.
        return Edge{distance * distance, neighbor};
      });
    return edges;
  }

  [[nodiscard]] std::string
  getReprImpl() const noexcept override {
    return value;
  }

  std::string value;
  std::vector<const StringNode*> neighbors;
};


static void
makeClique(std::vector<StringNode>& nodes) {
  for (auto& source : nodes) {
    for (const auto& target : nodes) {
      source.addNeighbor(target);
    }
  }
}


TEST_CASE("Can find path of string transformations") {
  std::vector<StringNode> nodes {
    StringNode{"bat"},
    StringNode{"car"},
  };
  makeClique(nodes);

  auto result = shortestPath(nodes[0], nodes[1]);
  const std::vector<const ex5::task2::Node*> expected = {
    &nodes[0],
    &nodes[1],
  };

  CHECK(expected == result);
}


TEST_CASE("Can find a longer path of smaller transformations") {
  std::vector<StringNode> nodes {
    StringNode{"bat"},
    StringNode{"car"},
    StringNode{"cat"},
  };
  makeClique(nodes);

  auto result = shortestPath(nodes[0], nodes[1]);
  const std::vector<const ex5::task2::Node*> expected = {
    &nodes[0],
    &nodes[2],
    &nodes[1],
  };

  CHECK(expected == result);
}


TEST_CASE("Can adapt to changes in the values of strings") {
  std::vector<StringNode> nodes {
    StringNode{"bat"},
    StringNode{"car"},
    StringNode{"cat"},
    StringNode{"cabb"},
  };
  makeClique(nodes);
  nodes[1].setString("cabbage");

  auto result = shortestPath(nodes[0], nodes[1]);
  const std::vector<const ex5::task2::Node*> expected = {
    &nodes[0],
    &nodes[3],
    &nodes[1],
  };

  CHECK(expected == result);
}


