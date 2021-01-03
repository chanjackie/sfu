
#include "task01.h"

using ex5::task1::ArgumentCount;
using ex5::task1::InterpreterState;
using ex5::task1::Operation;
using ex5::task1::OperationFactory;
using ex5::task1::OperationSpecification;
using ex5::task1::Outcome;
using ex5::task1::StackDifference;
using ex5::task1::Translator;

using ex5::task1::buildDefaultTranslator;


template<class OperationKind>
class DefaultFactory final : public OperationFactory {
private:
  [[nodiscard]] std::unique_ptr<Operation>
  createImpl() override {
    return std::make_unique<OperationKind>();
  }
};

class MultiplyOperation : public Operation {
private:
	[[nodiscard]] Outcome
	evaluateImpl(InterpreterState& state) override {
	    auto top = state.take();
	    auto next = state.take();
	    state.values.push(next * top);
	    return Outcome::SUCCESS;
	}

	[[nodiscard]] OperationSpecification
	getSpecificationImpl() const noexcept override {
		return OperationSpecification{ArgumentCount{2}, StackDifference{-1}};
	}
};

class DivideOperation : public Operation {
private:
	[[nodiscard]] Outcome
	evaluateImpl(InterpreterState& state) override {
	    auto top = state.take();
	    if (!top) return Outcome::FAILURE;
	    auto next = state.take();
	    state.values.push(next / top);
	    return Outcome::SUCCESS;
	}

	[[nodiscard]] OperationSpecification
	getSpecificationImpl() const noexcept override {
		return OperationSpecification{ArgumentCount{2}, StackDifference{-1}};
	}	
};

class GrowOperation : public Operation {
private:
	uint64_t growVal = 0;
	[[nodiscard]] Outcome
	evaluateImpl(InterpreterState& state) override {
		growVal++;
	    state.values.push(growVal);
	    return Outcome::SUCCESS;
	}

	[[nodiscard]] OperationSpecification
	getSpecificationImpl() const noexcept override {
		return OperationSpecification{ArgumentCount{0}, StackDifference{1}};
	}	
};

class FancyPrintOperation : public Operation {
private:
	[[nodiscard]] Outcome
	evaluateImpl(InterpreterState& state) override {
		printf(">>>%d<<<\n", state.values.top());
	    return Outcome::SUCCESS;
	}

	[[nodiscard]] OperationSpecification
	getSpecificationImpl() const noexcept override {
		return OperationSpecification{ArgumentCount{1}, StackDifference{0}};
	}	
};

using MultiplyFactory 	= DefaultFactory<MultiplyOperation>;
using DivideFactory 	= DefaultFactory<DivideOperation>;
using GrowFactory 		= DefaultFactory<GrowOperation>;
using FancyPrintFactory 		= DefaultFactory<FancyPrintOperation>;


Translator
buildEnrichedTranslator() noexcept {
	Translator translator = buildDefaultTranslator();
	translator.registerFactory("multiply", 	std::make_unique<MultiplyFactory>());
	translator.registerFactory("divide", 	std::make_unique<DivideFactory>());
	translator.registerFactory("grow", 		std::make_unique<GrowFactory>());
	return translator;
}

Translator
buildFancyTranslator() noexcept {
	Translator translator = buildDefaultTranslator();
	translator.registerFactory("print", 	std::make_unique<FancyPrintFactory>());
	return translator;
}