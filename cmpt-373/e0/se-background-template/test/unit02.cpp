#include "doctest.h"
#include "Support.h"
#include "task02.h"


TEST_CASE("increments positive") {
  int original = 3;
  const int result = task02(original);
  CHECK(4 == result);
}


TEST_CASE("increments negative") {
  int original = -3;
  const int result = task02(original);
  CHECK(-2 == result);
}


TEST_CASE("mutates") {
  int original = 1024;
  const int result = task02(original);
  CHECK(1025 == original);
  CHECK(1025 == result);
}

