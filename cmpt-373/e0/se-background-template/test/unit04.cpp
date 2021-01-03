#include "doctest.h"
#include "Support.h"
#include "task04.h"


TEST_CASE("increments positive") {
  const ex0::HotPotato tater{ex0::ButterPats{3}};
  const ex0::ButterPats result = task04(tater);
  CHECK(4 == result.count);
}


TEST_CASE("increments negative") {
  const ex0::HotPotato tater{ex0::ButterPats{-3}};
  const ex0::ButterPats result = task04(tater);
  CHECK(-2 == result.count);
}


