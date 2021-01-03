#include "doctest.h"
#include "task02.h"

#include <limits>


TEST_CASE("Simple distance") {
  const auto firstResult = distance(Position{0,0}, Position{3,4});
  CHECK(doctest::Approx(5) == firstResult);

  const auto secondResult = distance(Position{3,4}, Position{0,0});
  CHECK(doctest::Approx(5) == secondResult);
}


TEST_CASE("Extreme distance") {
  const int small = std::numeric_limits<int>::min();
  const int big = std::numeric_limits<int>::max();

  const auto firstResult = distance(Position{small,small}, Position{big,big});
  CHECK(doctest::Approx(6074000998.537) == firstResult);

  const auto secondResult = distance(Position{big,big}, Position{small,small});
  CHECK(doctest::Approx(6074000998.537) == secondResult);
}
