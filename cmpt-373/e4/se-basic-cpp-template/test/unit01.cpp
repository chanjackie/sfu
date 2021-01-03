#include "doctest.h"
#include "task01.h"

#include <array>
#include <string>
#include <sstream>


namespace doctest {

// When we can depend on C++20 support, this should use a span.
template<class Sequence>
String
printContiguous(const Sequence& in) {
  std::ostringstream oss;
  oss << "[ ";
  for (const auto& token : in) {
    oss << token << " ";
  }
  oss << "]";
  return oss.str().c_str();  
}

template <>
struct StringMaker<std::vector<std::string_view>> {
  static String convert(const std::vector<std::string_view>& in) {
    return printContiguous(in);
  }
};


}


TEST_CASE("tokens of an empty std::string") {
  const std::string data{""};

  auto result = task01(data);

  const decltype(result) expected = {};

  CHECK(expected == result);
}


TEST_CASE("tokens of a simple std::string") {
  const std::string data{"a bb cccc dddd"};

  auto result = task01(data);

  const decltype(result) expected = {
    "a", "bb", "cccc", "dddd"
  };

  CHECK(expected == result);
}


TEST_CASE("tokens of a simple C string") {
  const char* data = "aaaa bbb cc d";

  auto result = task01(data);

  const decltype(result) expected = {
    "aaaa", "bbb", "cc", "d"
  };

  CHECK(expected == result);
}


TEST_CASE("tokens of a simple C array") {
  const char data[] = "a bbbb cccc d";

  auto result = task01(data);

  const decltype(result) expected = {
    "a", "bbbb", "cccc", "d"
  };

  CHECK(expected == result);
}


TEST_CASE("tokens with mixed letters and punctuation") {
  const std::string data{"This is... maybe... a 1str1ng1."};

  auto result = task01(data);

  const decltype(result) expected = {
    "This", "is", "...", "maybe", "...", "a", "1str1ng1", "."
  };

  CHECK(expected == result);
}


TEST_CASE("string and tokens large enough to force allocation if done poorly") {
  const std::string data{
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA "
  };

  auto result = task01(data);

  const decltype(result) expected = {
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
    "ABABABAXYZABCHIGAAAABBBBABABABABABABABABABABA",
  };

  CHECK(expected == result);
}


