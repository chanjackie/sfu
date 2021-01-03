#include <iostream>
#include <sstream>

#include "doctest.h"

// By declaring the functions before the definition of `Structure`, we enable
// the symbols to be resolved without the use of more advanced features like
// ADL. Namespaces and ADL could, however, make such interfaces more ergonomic.

void printElement(std::ostream& out, int value);
void printElement(std::ostream& out, std::string_view value);

#include "task01.h"

using namespace std::string_literals;


// The printing functions are abused to instead log the contents of a structure
// in order to make sure that the correct constituents occur in the correct
// order.

struct IntCount {
  int value;
  size_t count;

  [[nodiscard]] bool
  operator==(const IntCount& other) const noexcept {
    return value == other.value && count == other.count;
  }
};

struct StringCount {
  std::string value;
  size_t count;

  [[nodiscard]] bool
  operator==(const StringCount& other) const noexcept {
    return value == other.value && count == other.count;
  }
};

std::vector<IntCount> seenInts;
std::vector<StringCount> seenStrings;
size_t count = 0;

void
printElement(std::ostream& out, int value) {
  seenInts.push_back({value, count});
  ++count;
}


void
printElement(std::ostream& out, std::string_view value) {
  seenStrings.push_back({std::string{value}, count});
  ++count;
}


template<typename ToCheck>
std::pair<std::vector<IntCount>, std::vector<StringCount>>
run(const ToCheck& toCheck) {
  count = 0;
  seenInts.clear();
  seenStrings.clear();

  toCheck();

  return {seenInts, seenStrings};
}


// We can specialize the StringMaker template for types that appear on
// both sides of an `==` in a doctest check. This allows us to get better
// printed messages for the data used within the assertions.
namespace doctest {

template <>
struct StringMaker<std::vector<IntCount>> {
  static String convert(const std::vector<IntCount>& in) {
    std::ostringstream oss;
    oss << "[ ";
    for (const auto& [value, count] : in) {
      oss << "(value:" << value << ", id:"  << count << ')' << " ";
    }
    oss << "]";
    return oss.str().c_str();
  }
};

template <>
struct StringMaker<std::vector<StringCount>> {
  static String convert(const std::vector<StringCount>& in) {
    std::ostringstream oss;
    oss << "[ ";
    for (const auto& [value, count] : in) {
      oss << "(value:" << value << ", id:"  << count << ')' << " ";
    }
    oss << "]";
    return oss.str().c_str();
  }
};

}


TEST_CASE("Empty Structure construction") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.print(std::cout);
  });
  CHECK(ints.empty());
  CHECK(strings.empty());
}


TEST_CASE("Adding integers") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add(5);
    s.add(6);
    s.print(std::cout);
  });

  const std::vector<IntCount> expectedInts = { {5,0}, {6,1} };

  CHECK(ints == expectedInts);
  CHECK(strings.empty());
}


TEST_CASE("Adding strings") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add("Hi there!"s);
    s.add("Friend!"s);
    s.print(std::cout);
  });

  const std::vector<StringCount> expectedStrings = {
    {"Hi there!"s, 0}, {"Friend!"s, 1}
  };

  CHECK(ints.empty());
  CHECK(strings == expectedStrings);
}


TEST_CASE("Adding strings and integers") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add("Hi there, friend number"s);
    s.add(7);
    s.print(std::cout);
  });

  const std::vector<IntCount> expectedInts = { {7,1} };
  const std::vector<StringCount> expectedStrings = {
    {"Hi there, friend number"s, 0}
  };

  CHECK(ints == expectedInts);
  CHECK(strings == expectedStrings);
}


TEST_CASE("Syntax for copy construction") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add("Hi there, friend number"s);
    s.add(7);
    Structure t(s);
    t.print(std::cout);
  });

  const std::vector<IntCount> expectedInts = { {7,1} };
  const std::vector<StringCount> expectedStrings = {
    {"Hi there, friend number"s, 0}
  };

  CHECK(ints == expectedInts);
  CHECK(strings == expectedStrings);
}


TEST_CASE("Syntax for copy assignment") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add("Hi there, friend number"s);
    s.add(7);
    Structure t;
    t = s;
    t.print(std::cout);
  });

  const std::vector<IntCount> expectedInts = { {7,1} };
  const std::vector<StringCount> expectedStrings = {
    {"Hi there, friend number"s, 0}
  };

  CHECK(ints == expectedInts);
  CHECK(strings == expectedStrings);
}


TEST_CASE("Nested Structures") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add("Hi there, friend number"s);
    s.add(7);
    Structure t;
    t.add(5);
    t.add(s);
    t.add(13);
    t.print(std::cout);
  });

  const std::vector<IntCount> expectedInts = { {5,0}, {7, 2}, {13, 3} };
  const std::vector<StringCount> expectedStrings = {
    {"Hi there, friend number"s, 1}
  };

  CHECK(ints == expectedInts);
  CHECK(strings == expectedStrings);
}


TEST_CASE("Self Nested Structures") {
  auto [ints, strings] = run([] () {
    Structure s;
    s.add("Hi there, friend number"s);
    s.add(7);
    s.add(s);
    s.add(13);
    s.print(std::cout);
  });

  const std::vector<IntCount> expectedInts = {
    {7, 1},
    {7, 3},
    {13, 4}
  };
  const std::vector<StringCount> expectedStrings = {
    {"Hi there, friend number"s, 0},
    {"Hi there, friend number"s, 2}
  };

  CHECK(ints == expectedInts);
  CHECK(strings == expectedStrings);
}

