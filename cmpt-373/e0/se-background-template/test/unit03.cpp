#include "doctest.h"
#include "Support.h"
#include "task03.h"


TEST_CASE("increments positive") {
  const ex0::HotPotato tater{ex0::ButterPats{3}};
  const ex0::ButterPats result = task03(tater);
  CHECK(4 == result.count);
}


TEST_CASE("increments negative") {
  // There's a butter deficit on my potato!
  const ex0::HotPotato tater{ex0::ButterPats{-3}};
  const ex0::ButterPats result = task03(tater);
  CHECK(-2 == result.count);
}


