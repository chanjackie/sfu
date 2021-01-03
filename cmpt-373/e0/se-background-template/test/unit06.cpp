#include "doctest.h"
#include "task06.h"

#include <string>


TEST_CASE("checksum of std::string") {
  const std::string data{"123"};

  uint32_t result = task06(data);

  CHECK(('1' + '2' + '3') == result);
}


TEST_CASE("large unsigned checksum") {
  const std::string data(17043522, '~');

  uint32_t result = task06(data);

  CHECK(2147483772ul == result);
}

