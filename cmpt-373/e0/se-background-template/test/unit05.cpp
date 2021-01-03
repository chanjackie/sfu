#include "doctest.h"
#include "Support.h"
#include "task05.h"


TEST_CASE("butters from positive") {
  ex0::HotPotato tater{ex0::ButterPats{3}};
  Task05 task05{tater};
  task05.butterExcessively();
  CHECK(8 == tater.getButterCount().count);
}


TEST_CASE("butters from negative") {
  // Sweet relief from our butter shortage.
  ex0::HotPotato tater{ex0::ButterPats{-3}};
  Task05 task05{tater};
  task05.butterExcessively();
  CHECK(2 == tater.getButterCount().count);
}


