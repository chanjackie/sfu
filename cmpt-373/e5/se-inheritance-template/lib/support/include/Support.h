
#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

namespace ex5 {

namespace task1 {

////////////////////////////////////////////////////////////////////////////////
// Part 1: To interpret the open and closedness of things.
////////////////////////////////////////////////////////////////////////////////

enum class Outcome {
  FAILURE,
  SUCCESS
};


// The argument count is the number of stack elements popped
// by an operation in order to perform evaluation. For example, `X + Y` has
// an argument count of 2 for the two arguments X and Y.
struct ArgumentCount {
  int value = 0;
};


// The stack difference is the overall impact of an operation on the stack size.
// For example, `X + Y` has a stack difference of -1 because it pops two
// values off of the stack, `X` and `Y`, but it then pushes a single value
// onto the stack, the value of `(X + Y)`.
struct StackDifference {
  int value = 0;
};


// The OperationSpecification for an operation contains both the
// argument count and the stack difference. Note that all valid evaluations of
// an operation must strictly adhere to the specification returned.
// For a given operation type, the same values for the specification must
// always be returned.
struct OperationSpecification {
  ArgumentCount argumentCount;
  StackDifference difference;
};


// A stack based machine maintains state as a simple stack of values that
// can be popped, pushed, and used by operations.
// We could also hide the implementation details of the values behind an
// additional interface, but we have not done so.
struct InterpreterState {
  std::stack<int> values;
  std::optional<int> result;

  int
  take() {
    auto value = values.top();
    values.pop();
    return value;
  }
};


// An Operation performs stack operations in order to achieve an objective.
// Different Operations may have different semantics and achieve different
// goals.
class Operation {
public:
  Operation() = default;
  Operation(const Operation&) = delete;
  Operation(Operation&&) = delete;
  virtual ~Operation() = default;

  Operation& operator=(const Operation&) = delete;
  Operation& operator=(Operation&&) = delete;

  [[nodiscard]] Outcome
  evaluate(InterpreterState& state) {
    auto [argCount, difference] = getSpecification();
    (void)difference; // Ignore the difference
    if (static_cast<int>(state.values.size()) < argCount.value) {
      return Outcome::FAILURE;
    }

    return evaluateImpl(state);
  }

  [[nodiscard]] OperationSpecification
  getSpecification() const {
    return getSpecificationImpl();
  }

private:
  // Overriding both the private implementation methods enables the
  // creation of new instructions with new meanings.
  [[nodiscard]] virtual Outcome evaluateImpl(InterpreterState& state) = 0;
  [[nodiscard]] virtual OperationSpecification getSpecificationImpl() const noexcept = 0;
};


// An OperationFactory creates instances of an instruction 
class OperationFactory {
public:
  OperationFactory() = default;
  OperationFactory(const OperationFactory&) = delete;
  OperationFactory(OperationFactory&&) = delete;
  virtual ~OperationFactory() = default;

  OperationFactory& operator=(const OperationFactory&) = delete;
  OperationFactory& operator=(OperationFactory&&) = delete;

  [[nodiscard]] std::unique_ptr<Operation>
  create() {
    return createImpl();
  }

private:
  [[nodiscard]] virtual std::unique_ptr<Operation> createImpl() = 0;
};


// A Program is just a list of operations
class Program {
private:
  // NOTE: This private section must be first in order to support decltype
  // based delegation of iteration.
  std::vector<std::unique_ptr<Operation>> operations;

public:
  [[nodiscard]] decltype(operations.cbegin()) begin() const noexcept { return operations.cbegin(); }
  [[nodiscard]] decltype(operations.cbegin()) end()   const noexcept { return operations.cend(); }

  void
  appendOperation(std::unique_ptr<Operation> newOperation) {
    operations.push_back(std::move(newOperation));
  }
};


// A Translator translates a string of source code into a Program.
class Translator {
public:
  using FactoryPointer = std::unique_ptr<OperationFactory>;
  using OperationPointer = std::unique_ptr<Operation>;

  // NOTE: the string is passed by value because a mutable defensive copy is
  // desired.
  void registerFactory(std::string spelling, FactoryPointer factory) noexcept;

  Program translate(const std::string& source) const noexcept;

private:
  OperationPointer createOperation(const std::string& spelling) const noexcept;

  std::unordered_map<std::string, FactoryPointer> factories;
};


// An Interpreter evaluates a program.
class Interpreter {
public:
  std::optional<int> evaluate(const Program& program);
  [[nodiscard]] bool isValid(const Program& program) const noexcept;
};


Translator buildDefaultTranslator() noexcept;

}


namespace task2 {
////////////////////////////////////////////////////////////////////////////////
// Part 2: The space between the gaps OR Making use of negative space
////////////////////////////////////////////////////////////////////////////////

class Node {
public:
  Node() = default;
  Node(const Node&) = delete;
  Node(Node&&) = delete;
  virtual ~Node() = default;

  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) = delete;

  struct Edge {
    size_t weight = 0;
    const Node* node = nullptr;
  };

  [[nodiscard]] std::vector<Edge>
  getSuccessors() const noexcept {
    return getSuccessorsImpl();
  }

private:
  [[nodiscard]] virtual std::vector<Edge> getSuccessorsImpl() const noexcept = 0;
};


}


namespace task3 {
////////////////////////////////////////////////////////////////////////////////
// Part 3: Keeping your composure and tidying up the garden
////////////////////////////////////////////////////////////////////////////////

class Location {
public:
  Location(size_t row, size_t column)
    : locationPair{row, column}
      { }

  [[nodiscard]] size_t getRow()    const noexcept { return locationPair.first; }
  [[nodiscard]] size_t getColumn() const noexcept { return locationPair.second; }

  // Translation to a pair makes management inside data structures simpler.
  [[nodiscard]] std::pair<size_t, size_t>
  getAsPair() const noexcept {
    return locationPair;
  }

  operator std::pair<size_t, size_t>() const noexcept { return getAsPair(); }

  [[nodiscard]] bool
  operator==(const Location& other) const noexcept {
    return locationPair == other.locationPair;
  }

private:
  std::pair<size_t, size_t> locationPair;
};


enum class Color {
  WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, BLACK
};


template <typename Base, typename Tag>
struct StrongAlias {
  explicit StrongAlias(Base value) : value{std::move(value)} { }

  [[nodiscard]] bool
  operator==(const StrongAlias<Base,Tag>& other) const noexcept {
    return value == other.value;
  }

  Base value;
};

using RootGrowth = StrongAlias<size_t, struct RootGrowthTag>;
using Height     = StrongAlias<size_t, struct HeightTag>;
using Bloom      = StrongAlias<size_t, struct BloomTag>;

// Using these, you can access the value of a specific `Bloom` using
// e.g. `bloom.value`

}



}



