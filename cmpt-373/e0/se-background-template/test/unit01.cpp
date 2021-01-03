#include "doctest.h"
#include "Support.h"
#include "task01.h"


TEST_CASE("increments positive") {
  const int original = 3;
  const int result = task01(original);
  CHECK(4 == result);
}


TEST_CASE("increments negative") {
  const int original = -3;
  const int result = task01(original);
  CHECK(-2 == result);
}


TEST_CASE("does not mutate") {
  const int original = 1024;
  const int result = task01(original);
  CHECK(1024 == original);
  CHECK(1025 == result);
}

