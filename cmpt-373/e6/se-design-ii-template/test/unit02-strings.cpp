#include "doctest.h"

#include "Support.h"
#include "task02.h"

#include <numeric>
#include <sstream>
#include <unordered_map>

using ex6::task2::WordEditGraph;
using ex6::task2::Spelling;


// We can specialize the StringMaker template for types that appear on
// both sides of an `==` in a doctest check. This allows us to get better
// printed messages for the data used within the assertions.
namespace doctest {

template <>
struct StringMaker<std::vector<const Spelling*>> {
  static String convert(const std::vector<const Spelling*>& in) {
    std::ostringstream oss;
    oss << "[ ";
    for (const auto* spelling : in) {
      oss << spelling->word << " ";
    }
    oss << "]";
    return oss.str().c_str();
  }
};

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


TEST_CASE("Can find path of string transformations") {
  WordEditGraph nodes {
    Spelling{"bat"},
    Spelling{"car"},
  };

  auto result = shortestPath(nodes, &nodes[0], &nodes[1]);
  const std::vector<const Spelling*> expected = {
    &nodes[0],
    &nodes[1],
  };

  CHECK(expected == result);
}


TEST_CASE("Can find a longer path of smaller transformations") {
  WordEditGraph nodes {
    Spelling{"bat"},
    Spelling{"car"},
    Spelling{"cat"},
  };

  auto result = shortestPath(nodes, &nodes[0], &nodes[1]);
  const std::vector<const Spelling*> expected = {
    &nodes[0],
    &nodes[2],
    &nodes[1],
  };

  CHECK(expected == result);
}


TEST_CASE("Can adapt to changes in the values of strings") {
  WordEditGraph nodes {
    Spelling{"bat"},
    Spelling{"car"},
    Spelling{"cat"},
    Spelling{"cabb"},
  };
  nodes[1].word = "cabbage";

  auto result = shortestPath(nodes, &nodes[0], &nodes[1]);
  const std::vector<const Spelling*> expected = {
    &nodes[0],
    &nodes[3],
    &nodes[1],
  };

  CHECK(expected == result);
}


