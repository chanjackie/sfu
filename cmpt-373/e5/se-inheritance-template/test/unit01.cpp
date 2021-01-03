#include <iostream>
#include <sstream>

#include "doctest.h"

#include "task01.h"

using ex5::task1::Interpreter;
using ex5::task1::Program;
using ex5::task1::Translator;
using ex5::task1::buildDefaultTranslator;


// We can specialize the StringMaker template for types that appear on
// both sides of an `==` in a doctest check. This allows us to get better
// printed messages for the data used within the assertions.
namespace doctest {

template <typename T>
struct StringMaker<std::optional<T>> {
  static String convert(const std::optional<T>& in) {
    std::ostringstream os;
    if (in) {
      os << "NONE";
    } else {
      os << *in;
    }
    return os.str().c_str();
  }
};

}


TEST_CASE("Sanity checking evaluation") {
  std::string source = {
    " PUSH 2 "
    " PUSH 5 "
    " PUSH 7 "
    " ADD "
    " PUSH 3 "
    " SUBTRACT "
    " NEGATE "
    " PRINT "
    " SAVE "
    " POP "
    " PRINT "
  };

  Translator translator = ex5::task1::buildDefaultTranslator();
  Program program = translator.translate(source);
  auto result = Interpreter{}.evaluate(program);

  CHECK(result == -9);
}


TEST_CASE("Multiply can work") {
  std::string source = {
    " PUSH 2 "
    " PUSH 5 "
    " MULTIPLY "
    " SAVE "
  };

  Translator translator = buildEnrichedTranslator();
  Program program = translator.translate(source);
  auto result = Interpreter{}.evaluate(program);

  CHECK(result == 10);
}


TEST_CASE("Multiply can fail") {
  std::string source = {
    " PUSH 2 "
    " MULTIPLY "
  };

  Translator translator = buildEnrichedTranslator();
  Program program = translator.translate(source);
  auto isValid = Interpreter{}.isValid(program);

  CHECK(!isValid);
}


TEST_CASE("Divide can work") {
  std::string source = {
    " PUSH 10 "
    " PUSH 4 "
    " DIVIDE "
    " SAVE "
  };

  Translator translator = buildEnrichedTranslator();
  Program program = translator.translate(source);
  auto result = Interpreter{}.evaluate(program);

  CHECK(result == 2);
}


TEST_CASE("Divide can fail from too few arguments") {
  std::string source = {
    " PUSH 2 "
    " DIVIDE "
  };

  Translator translator = buildEnrichedTranslator();
  Program program = translator.translate(source);
  auto isValid = Interpreter{}.isValid(program);

  CHECK(!isValid);
}


TEST_CASE("Divide can fail from a zero denominator") {
  std::string source = {
    " PUSH 2 "
    " PUSH 0 "
    " DIVIDE "
    " SAVE "
  };

  Translator translator = buildEnrichedTranslator();
  Program program = translator.translate(source);
  auto result = Interpreter{}.evaluate(program);

  CHECK(!result);
}


TEST_CASE("Grow can work") {
  std::string source = {
    " GROW "
    " SAVE "
  };

  Translator translator = buildEnrichedTranslator();
  Program program = translator.translate(source);

  auto result = Interpreter{}.evaluate(program);
  CHECK(result == 1);

  result = Interpreter{}.evaluate(program);
  CHECK(result == 2);

  result = Interpreter{}.evaluate(program);
  CHECK(result == 3);
}


TEST_CASE("Fancy translator running. (test always passes)") {
  std::string source = {
    " PUSH 2 "
    " PUSH 5 "
    " PUSH 7 "
    " ADD "
    " PUSH 3 "
    " SUBTRACT "
    " NEGATE "
    " PRINT "
    " SAVE "
    " POP "
    " PRINT "
  };

  Translator translator = buildFancyTranslator();
  Program program = translator.translate(source);
  auto result = Interpreter{}.evaluate(program);

  CHECK(result == -9);
}


