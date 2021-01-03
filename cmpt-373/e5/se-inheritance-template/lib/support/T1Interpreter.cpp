
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <sstream>
#include "Support.h"


using ex5::task1::ArgumentCount;
using ex5::task1::Interpreter;
using ex5::task1::InterpreterState;
using ex5::task1::Operation;
using ex5::task1::OperationFactory;
using ex5::task1::OperationSpecification;
using ex5::task1::Outcome;
using ex5::task1::Program;
using ex5::task1::StackDifference;
using ex5::task1::Translator;


// Default Operations

class PushOperation : public Operation {
public:
  explicit PushOperation(int value)
    : value{value}
      { }

private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    state.values.push(value);
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{0}, StackDifference{1}};
  }

  int value;
};


class PopOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    state.values.pop();
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{1}, StackDifference{-1}};
  }
};


class DuplicateOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    state.values.push(state.values.top());
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{1}, StackDifference{1}};
  }
};


class NegateOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    auto& top = state.values.top();
    top = -top;
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{1}, StackDifference{0}};
  }
};


class AddOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    auto top = state.take();
    auto next = state.take();
    state.values.push(next + top);
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{2}, StackDifference{-1}};
  }
};


class SubtractOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    auto top = state.take();
    auto next = state.take();
    state.values.push(next - top);
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{2}, StackDifference{-1}};
  }
};


class PrintOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    printf("%d\n", state.values.top());
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{1}, StackDifference{0}};
  }
};


class SaveOperation : public Operation {
private:
  [[nodiscard]] Outcome
  evaluateImpl(InterpreterState& state) override {
    state.result = state.values.top();
    return Outcome::SUCCESS;
  }

  [[nodiscard]] OperationSpecification
  getSpecificationImpl() const noexcept override {
    return OperationSpecification{ArgumentCount{1}, StackDifference{0}};
  }
};


// Default Factories

template<class OperationKind>
class DefaultFactory final : public OperationFactory {
private:
  [[nodiscard]] std::unique_ptr<Operation>
  createImpl() override {
    return std::make_unique<OperationKind>();
  }
};

using PopFactory       = DefaultFactory<PopOperation>;
using DuplicateFactory = DefaultFactory<DuplicateOperation>;
using NegateFactory    = DefaultFactory<NegateOperation>;
using AddFactory       = DefaultFactory<AddOperation>;
using SubtractFactory  = DefaultFactory<SubtractOperation>;
using PrintFactory     = DefaultFactory<PrintOperation>;
using SaveFactory      = DefaultFactory<SaveOperation>;


// Translations

static void
canonicalizeSpelling(std::string& spelling) {
  std::transform(spelling.begin(), spelling.end(), spelling.begin(), tolower);
}


void
Translator::registerFactory(std::string spelling, FactoryPointer factory) noexcept {
  // The spelling argument is a mutable copy because we want the freedom to
  // canonicalize as necessary. Small string optimization should kick in
  // anyway.
  canonicalizeSpelling(spelling);
  factories[spelling] = std::move(factory);
}


const std::string PUSH{"push"};


// Create an `Operation` of the requested type is possible. This uses the
// factories registered for each spelling to determine how and therefore which
// `Operations` should be created.
// NOTE: In the even of failure, the resulting `OperationPointer` will be null.
Translator::OperationPointer
Translator::createOperation(const std::string& spelling) const noexcept {
  auto factory = factories.find(spelling);
  if (factory == factories.end()) {
    return {};
  }

  return factory->second->create();
}


Program
Translator::translate(const std::string& source) const noexcept {
  Program program;

  std::istringstream stream{source};
  std::string action;
  int value;

  // Note that because there is potentially some complex strema processing
  // going on that we are using a raw loop for the processing. This is
  // idiomatic, but we can certainly imagine some nicer ways to do this.
  while (stream >> action) {
    canonicalizeSpelling(action);
    OperationPointer operation;

    // PUSH is the only case with special handling.
    if (action != PUSH) {
      operation = createOperation(action);
    } else if (stream >> value) {
      operation = std::make_unique<PushOperation>(value);
    }

    if (operation) {
      program.appendOperation(std::move(operation));
    } else {
      // For now the policy inside the translator is to silently ignore any
      // failure to translate. What potential problems does this create.
      // How severe might the consequences be?
    }
  }

  return program;
}


// Interpreting Programs

// Evaluating a program turns out to be simple in this arrangement.
// We can just run each operation while looking for errors.
// Why don't we want to just run an existing algorithm from the standard library
// instead of a for-each loop? There is actually a reason.
std::optional<int>
Interpreter::evaluate(const Program& program) {
  InterpreterState state;
  assert(isValid(program)
         && "Evaluating program with invalid stack accesses!");
 
  for (auto& operation : program) {
    auto outcome = operation->evaluate(state);
    if (Outcome::FAILURE == outcome) {
      return {};
    }
  }

  return state.result;
}


// We may consider many valdity constraints or invariants within a program.
// Assuming that all specifications for operations are correct, this method
// checks whether the stack will be sufficiently large for the operations
// to complete successfully.
bool
Interpreter::isValid(const Program& program) const noexcept {
  struct Validity {
    int size = 0;
    bool valid = true; 
  };
  auto validity =
    std::accumulate(program.begin(), program.end(), Validity{},
    [] (auto sofar, const auto& operation) {
      auto spec = operation->getSpecification();
      return Validity{ spec.difference.value + sofar.size,
               sofar.valid && spec.argumentCount.value <= sofar.size };
    });
  return validity.valid;
}


namespace ex5::task1 {

Translator
buildDefaultTranslator() noexcept {
  Translator translator;
  translator.registerFactory("pop",       std::make_unique<PopFactory>());
  translator.registerFactory("duplicate", std::make_unique<DuplicateFactory>());
  translator.registerFactory("negate",    std::make_unique<NegateFactory>());
  translator.registerFactory("add",       std::make_unique<AddFactory>());
  translator.registerFactory("subtract",  std::make_unique<SubtractFactory>());
  translator.registerFactory("print",     std::make_unique<PrintFactory>());
  translator.registerFactory("save",      std::make_unique<SaveFactory>());
  return translator;
}

}