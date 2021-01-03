#include "doctest.h"
#include "task07.h"

#include <unordered_map>
#include <string>


TEST_CASE("NOOP translation") {
  const std::string message{"This is the original message."};
  const std::unordered_map<char, const std::string> transformation = { };

  const std::string result = task07(message, transformation);

  CHECK(result == message);
}

TEST_CASE("Simple Caesar") {
  const std::string message{"maybe this will work, too."};
  const std::unordered_map<char, const std::string> transformation = {
    {'a', "h"},
    {'b', "i"},
    {'c', "j"},
    {'d', "k"},
    {'e', "l"},
    {'g', "n"},
    {'h', "o"},
    {'i', "p"},
    {'k', "r"},
    {'l', "s"},
    {'m', "t"},
    {'o', "v"},
    {'r', "y"},
    {'s', "z"},
    {'t', "a"},
    {'u', "b"},
    {'w', "d"},
    {'y', "f"},
  };

  const std::string result = task07(message, transformation);
  const std::string correct = "thfil aopz dpss dvyr, avv.";

  CHECK(result == correct);
}


TEST_CASE("Word substitution") {
  const std::string message{"a b c d e how f"};
  const std::unordered_map<char, const std::string> transformation = {
    {'a', "anyone"},
    {'b', "lived"},
    {'c', "in"},
    {'d', "a"},
    {'e', "pretty"},
    {'f', "town"},
  };

  const std::string result = task07(message, transformation);
  const std::string correct = "anyone lived in a pretty how town";

  CHECK(result == correct);
}

