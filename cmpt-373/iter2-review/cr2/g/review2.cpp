// Class that encapsulates the possible types of game variables such that components can
// manipulate game values without being aware of their particular types.
class GameValue {
public:
    GameValue(std::string& str);
    GameValue(int num);
    GameValue(bool truth);

    // TODO: Use std::enable_if to restrict this to operations described below?
    template <typename Operation> 
    void perform(Operation op);

private:
    // TODO: Add lists and maps.
    std::variant<std::string, int, bool> variant;
};

// The definition for the templated method needs to be in the header - not sure how to 
// get around this at the moment.
template <typename Operation> 
void GameValue::perform(Operation op) {
    std::visit(op, variant);
}

struct GameKey {
    std::string key;
};

// Defines operations that can be performed on GameValues
namespace Operation { 

// TODO: Can't use a single typename for both lambdas in template?
template <typename T, typename onTrue, typename onFalse>
struct Compare {
    Compare(T toCompareAgainst, onTrue handleTrue, onFalse handleFalse)
    : toCompareAgainst(toCompareAgainst), handleTrue(handleTrue), handleFalse(handleFalse) {}

    // When comparing type T to a type other than T (call it N), don't do anything.
    template <typename N>
    void operator()(N notComparable) {} 

    // TODO: Handle comparisons of lists and maps.

    // If T is an int, bool, or string, then toCompareAgainst and other can be compared.
    void operator()(T other) {
        toCompareAgainst == other ? onTrue() : onFalse();
    }

    T toCompareAgainst;

    // TODO: Using callbacks feels like the wrong approach. Need some way to express
    //       the notion of evaluating subrules when true and moving to the next (adjacent) 
    //       rule when false.
    onTrue handleTrue;
    onFalse handleFalse;
};

struct Add {
    int toAdd;

    // Do not add if argument to operator() is not an int. 
    template <typename N>
    void operator()(N notAddable) {}

    void operator()(int& num) {
        num += toAdd;
    }
};

template <typename T>
struct Replace {
    Replace(T replacement) : replacement{replacement} {}

    // Do not replace a type T with a different type N.
    template <typename N>
    void operator()(N notReplaceable) {}

    void operator()(T& toReplace) {
        toReplace = replacement;
    }

    T replacement;
};

};

// ================================================================================

// Interface that describes a visitor which visits and processes each node in a rule tree. 
class Visitor {
  public:
    virtual void visit(LoopRule& loop) = 0;
    virtual void visit(AddRule& add) = 0;
};

// Interpreter is a type of visitor which processes the nodes it visits by executing the
// logic of the rule contained within the node.
class Interpreter : Visitor {
  public:
    // TODO: Add other rules.
    void visit(LoopRule& loop) override;
    void visit(AddRule& add) override;
  
  private:
    StateStack states; 
};

void Interpreter::visit(AddRule& rule) {
    std::optional<GameValue> val = states.getValue(rule.key);
    if (val) {
        val->perform(rule.add);
    } 
}

// ================================================================================

// Used to represent variable scope within game logic e.g. subrules under a foreach
// rule with the notion of a local element. 
class StateStack {
  public:
    // Adds a GameState to the top of the stack.
    void push(GameState state);

    // Pops the GameState at the top of the stack.
    GameState pop();

    // Returns the closest (top -> bottom) GameValue with the given key in the stack,
    // if it exists.
    std::optional<GameValue> getValue(GameKey key);

  private:
    std::vector<GameState> vec;
};

void StateStack::push(GameState state) {
    vec.push_back(state);
}

GameState StateStack::pop() {
    GameState top = vec.back();
    vec.pop_back();
    return top;
}

// Suppose the StateStack is a vector<map<string, GameValue>>
std::optional<GameValue> StateStack::getValue(GameKey key) {
    auto foundState = std::find_if(vec.rbegin(), vec.rend(), [key](const GameState& state) {
        return (state.find(key) != state.end());
    });

    // TODO: Awkward, because find_if returns iterator which cannot be dereferenced if 
    //       it hasn't found and the iterator is at the end. 
    return foundState != vec.rend() ? 
        std::optional<GameValue>{(*foundState)[key]} :
        std::optional<GameValue>{};
}

// ================================================================================

// The Rule class represents nodes within a tree structure - they are only used for 
// structure. Executing the logic of the rule is contained within the interpreter visitor.  
class Rule {
 public:
  virtual void accept(Visitor& visitor) = 0;
};

struct AddRule : public Rule {
    AddRule(GameKey key, Operation::Add add) : key{key}, add{add} {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    GameKey key; 
    Operation::Add add;
};