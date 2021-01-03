#include "doctest.h"
#include "task06.h"

#include <sstream>

namespace doctest {

template <>
struct StringMaker<std::vector<std::pair<size_t, size_t>>> {
  static String convert(const std::vector<std::pair<size_t, size_t>>& in) {
    std::ostringstream oss;
    oss << "[ ";
    for (const auto& edge : in) {
      ex4::operator<<(oss, edge) << " ";
    }
    oss << "]";
    return oss.str().c_str();
  }
};

}


// These tests are structured to run each interesting sequence of operations
// twice. One observes the allocation behavior and the other extracts the 
// observable tree structure.


TEST_CASE("Empty forest") {
  const auto makeForest = [] () noexcept {
    Forest forest{0};
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  CHECK(edges.empty());
}


TEST_CASE("One node") {
  const auto makeForest = [] () noexcept {
    Forest forest{1};
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  CHECK(edges.empty());
}


TEST_CASE("Two nodes") {
  const auto makeForest = [] () noexcept {
    Forest forest{2};
    forest.grow(From{0}, To{1});
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 1}
  };
  CHECK(expected == edges);
}


TEST_CASE("Chain") {
  const auto makeForest = [] () noexcept {
    Forest forest{5};
    forest.grow(From{0}, To{1});
    forest.grow(From{1}, To{2});
    forest.grow(From{2}, To{3});
    forest.grow(From{3}, To{4});
    return forest;
  };
  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 4}
  };
  CHECK(expected == edges);
}


TEST_CASE("Reverse constructed chain") {
  const auto makeForest = [] () noexcept {
    Forest forest{5};
    forest.grow(From{3}, To{4});
    forest.grow(From{2}, To{3});
    forest.grow(From{1}, To{2});
    forest.grow(From{0}, To{1});
    return forest;
  };
  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 4}
  };
  CHECK(expected == edges);
}


TEST_CASE("Forest") {
  const auto makeForest = [] () noexcept {
    Forest forest{6};
    forest.grow(From{0}, To{1});
    forest.grow(From{0}, To{2});
    forest.grow(From{3}, To{4});
    forest.grow(From{3}, To{5});
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 1},
    {0, 2},
    {3, 4},
    {3, 5}
  };
  CHECK(expected == edges);
}


TEST_CASE("Reparenting") {
  const auto makeForest = [] () noexcept {
    Forest forest{6};
    forest.grow(From{0}, To{1});
    forest.grow(From{0}, To{2});
    forest.grow(From{3}, To{4});
    forest.grow(From{3}, To{5});
    forest.grow(From{0}, To{3});
    forest.grow(From{1}, To{4});
    forest.grow(From{1}, To{5});
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 4},
    {1, 5}
  };
  CHECK(expected == edges);
}


TEST_CASE("Pruning") {
  const auto makeForest = [] () noexcept {
    Forest forest{6};
    forest.grow(From{0}, To{1});
    forest.grow(From{0}, To{2});
    forest.grow(From{3}, To{4});
    forest.grow(From{3}, To{5});
    forest.cut(To{4});
    forest.cut(To{1});
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 2},
    {3, 5}
  };
  CHECK(expected == edges);
}


TEST_CASE("Adding nodes") {
  const auto makeForest = [] () noexcept {
    Forest forest{2};
    forest.grow(From{0}, To{1});
    forest.addNode();
    forest.grow(From{0}, To{2});
    forest.addNode();
    forest.addNode();
    forest.addNode();
    forest.grow(From{3}, To{4});
    forest.grow(From{3}, To{5});
    forest.addNode();
    forest.grow(From{6}, To{0});
    forest.grow(From{6}, To{3});
    forest.grow(From{6}, To{5});
    return forest;
  };

  const auto forest = makeForest();
  const auto edges = forest.getEdges();

  const std::vector<std::pair<size_t, size_t>> expected = {
    {0, 1},
    {0, 2},
    {3, 4},
    {6, 0},
    {6, 3},
    {6, 5}
  };
  CHECK(expected == edges);
}


