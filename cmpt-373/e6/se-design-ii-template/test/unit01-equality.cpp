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


TEST_CASE("Empty Structures") {
  Structure s;
  Structure t;
  CHECK(s == t);
}


TEST_CASE("Adding integers") {
  Structure s;
  Structure t;
  s.add(5);
  s.add(6);
  CHECK(!(s == t));
  t.add(5);
  t.add(6);
  CHECK(s == t);
  s.add(5);
  t.add(6);
  CHECK(!(s == t));
}


TEST_CASE("Adding strings") {
  Structure s;
  Structure t;
  s.add("Hi there!"s);
  s.add("Friend!"s);
  CHECK(!(s == t));
  t.add("Hi there!"s);
  t.add("Friend!"s);
  CHECK(s == t);
  s.add("Hi there!"s);
  t.add("Friend!"s);
  CHECK(!(s == t));
}


TEST_CASE("Adding strings and integers") {
  Structure s;
  Structure t;
  s.add("Hi there, friend number"s);
  s.add(7);
  CHECK(!(s == t));
  t.add("Hi there, friend number"s);
  t.add(7);
  CHECK(s == t);
  s.add("Hi there, friend number"s);
  t.add(7);
  CHECK(!(s == t));
}



TEST_CASE("Nested Structures") {
  Structure s;
  s.add("Hi there, friend number"s);
  s.add(7);
  Structure t;
  t.add(5);
  t.add(s);

  Structure u;
  u.add("Hi there, friend number"s);
  u.add(7);

  Structure v;
  CHECK(!(v == t));
  v.add(5);
  v.add(u);
  CHECK(v == t);
  t.add(5);
  v.add(u);
  CHECK(!(v == t));
}

