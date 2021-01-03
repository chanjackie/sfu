#include <iostream>

#include "doctest.h"

// By declaring the functions before the definition of `Structure`, we enable
// the symbols to be resolved without the use of more advanced features like
// ADL. Namespaces and ADL could, however, make such interfaces more ergonomic.

void printElement(std::ostream& out, int value);
void printElement(std::ostream& out, std::string_view value);

#include "task01.h"

using namespace std::string_literals;


void
printElement(std::ostream& out, int value) {
  out << value;
}


void
printElement(std::ostream& out, std::string_view value) {
  out << value;
}


TEST_CASE("Empty Structure construction") {
  Structure s;
  CHECK(true);
}


TEST_CASE("Adding integers") {
  Structure s;
  s.add(5);
  s.add(6);
  s.print(std::cout);
  CHECK(true);
}


TEST_CASE("Adding strings") {
  Structure s;
  s.add("Hi there!"s);
  s.add("Friend!"s);
  s.print(std::cout);
  CHECK(true);
}


TEST_CASE("Adding strings and integers") {
  Structure s;
  s.add("Hi there, friend number"s);
  s.add(7);
  s.print(std::cout);
  CHECK(true);
}


TEST_CASE("Syntax for copy construction") {
  Structure s;
  s.add("Hi there, friend number"s);
  s.add(7);
  Structure t(s);
  t.print(std::cout);
  CHECK(true);
}


TEST_CASE("Syntax for copy assignment") {
  Structure s;
  s.add("Hi there, friend number"s);
  s.add(7);
  Structure t;
  t = s;
  t.print(std::cout);
  CHECK(true);
}


TEST_CASE("Nested Structures") {
  Structure s;
  s.add("Hi there, friend number"s);
  s.add(7);
  Structure t;
  t.add(5);
  t.add(s);
  t.print(std::cout);
  CHECK(true);
}


TEST_CASE("Self Nested Structures") {
  Structure s;
  s.add("Hi there, friend number"s);
  s.add(7);
  s.add(s);
  s.add(13);
  s.print(std::cout);
  CHECK(true);
}

