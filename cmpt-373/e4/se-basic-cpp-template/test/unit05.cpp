#include "doctest.h"
#include "task05.h"


TEST_CASE("No planters") {
  const std::vector<ex4::Planter> planters;

  std::vector<ex4::Plant> results = task05(planters);

  CHECK(results.empty());
}


TEST_CASE("Empty planters") {
  const std::vector<ex4::Planter> planters {
    {}, {}, {}, {}
  };

  std::vector<ex4::Plant> results = task05(planters);

  CHECK(results.empty());
}


TEST_CASE("One plant") {
  const std::vector<ex4::Planter> planters {
    {1}, {}, {}, {}
  };

  std::vector<ex4::Plant> results = task05(planters);

  const std::vector<ex4::Plant> expected {
    1
  };

  CHECK(expected == results);
}


TEST_CASE("Two plants in one planter") {
  const std::vector<ex4::Planter> planters {
    {1, 2}, {}, {}, {}
  };

  std::vector<ex4::Plant> results = task05(planters);

  const std::vector<ex4::Plant> expected {
    1, 2
  };

  CHECK(expected == results);
}


TEST_CASE("Two plants in two planters") {
  const std::vector<ex4::Planter> planters {
    {1}, {}, {2}, {}
  };

  std::vector<ex4::Plant> results = task05(planters);

  const std::vector<ex4::Plant> expected {
    1, 2
  };

  CHECK(expected == results);
}


TEST_CASE("Many plants in many planters") {
  const std::vector<ex4::Planter> planters {
    {1, 2, 3, 4}, {5, 6, 7, 8, 9, 10}, {}, {11, 12, 13, 14, 15, 16, 17}
  };

  std::vector<ex4::Plant> results = task05(planters);

  const std::vector<ex4::Plant> expected {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17
  };

  CHECK(expected == results);
}

