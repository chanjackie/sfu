// ------------------------------ ShuntingYard.cpp --------------------------------------------//
// you can change the output precedence to have a different output of the algorithm
int ShuntingYard::getPrecedence(std::shared_ptr<Token> tok){
    switch(tok->getType()){
        case Token::Type::equals:
            return 1;
        case Token::Type::dot:
            return 3;
        case Token::Type::less_than:
            return 2;
        case Token::Type::less_equal:
            return 2;
        case Token::Type::greater_equal:
            return 2;
        case Token::Type::greater_than:
            return 2;
        case Token::Type::negation:
            return 2;
    }
}

bool ShuntingYard::isOperator(std::shared_ptr<Token> tok){
    switch(tok->getType()){
        case Token::Type::identifier: 
            return false;
        case Token::Type::integer:
            return false;
        case Token::Type::error:
            return false;
        case Token::Type::open_parenthesis:
            return false;
        case Token::Type::close_parenthesis:
            return false;
        default:
            return true;
    }
}
std::vector<std::shared_ptr<Token>> ShuntingYard::translate( std::vector<std::shared_ptr<Token>> input ){
    std::vector<std::shared_ptr<Token>> outputStack;    // this will be the vecotr returned
    std::vector<std::shared_ptr<Token>> opStack;        // temporary stack to store operaters
    for(auto it = input.begin(); it != input.end(); it++){
        // get front token
        auto token = *it;
        if( !isOperator(token) ){
            outputStack.push_back(token);
        }
        else if(isOperator(token)){
            auto precedence = getPrecedence(token);
            // check the output stack to find if the operator has a greater precedence
            while( !opStack.empty() && precedence < getPrecedence( opStack.back() )){
                // will add the opertator to the output stack  
                outputStack.push_back( opStack.back() );
                opStack.pop_back();
            }
            // add token to operator stack
            opStack.push_back(token);
        }
        else if( token->getType() == Token::Type::open_parenthesis){
            opStack.push_back(token);
        }
        else if( token->getType() == Token::Type::close_parenthesis){
            // will add all operators until the open open parenthesis operator is found
            while(true){
                if(opStack.empty()){
                    throw "Bad Parenthesis!";
                }
                auto back_op = opStack.back();
                opStack.pop_back();

                if( back_op->getType() == Token::Type::close_parenthesis){
                    break;
                }else{
                    outputStack.push_back( back_op );
                }
                
            }
        }
    }
    // add all the operator stack to the output stack
    while(!opStack.empty()){
        outputStack.push_back( opStack.back() );
        opStack.pop_back();
    }
    return outputStack;
}
//---------------------------------
// RuleType type for all the uses below (lives in the Scope class)
//---------------------------------
class Scope {
public:
    struct Blocking {};

    // I don't know what to call this
    // A basic wrapper around a variant to expose special member functions
    class RuleType {
    public:
        using variant_type = std::variant<
            std::monostate,
            Blocking,
            std::reference_wrapper<const Rule>
        >; 

        variant_type& get() noexcept { return internal; }
        const variant_type& get() const noexcept { return internal; }
        //... bunch of helper functions and constructors I have to cut out or this review is too long
    }
}

//---------------------------------
// ParallelScope.cpp
//---------------------------------
// In the middle of implementing blocking, so I haven't changed ParallelScope to handle it haha

ParallelScope::ParallelScope() :
    curr{0}, threads{}
{}

// vector<scope> constructor - can't figure out how to get it to compile
// ParallelScope(std::shared_ptr<ScopedGameState> state, std::vector<std::unique_ptr<Scope>> scopes) :
//     state{state}, curr{0}, threads{std::move(scopes)}
// {}

void ParallelScope::addThread(std::unique_ptr<Scope> toadd) {
    threads.push_back(std::move(toadd));
}

RuleType ParallelScope::doGetNextRule() {
    const size_t TOTAL_THREADS = threads.size();
    size_t checkedThreads = 0;
    while (checkedThreads < TOTAL_THREADS) {
        auto [result,mayberule] = getRuleFromCurrentThread();
        switch (result) {
            case Result::SUCCESS:
                return mayberule;
                break;
            case Result::EMPTY:
                removeCurrentThread();
                moveToNextThread();
                break;
            case Result::NORULES:
                goto breakOutOfWhileLoop;
                break;
        }
        checkedThreads++;
    }
    breakOutOfWhileLoop:
    return std::nullopt;
}

std::shared_ptr<ScopedGameState> ParallelScope::doGetGameState() {
    return getCurrentThread()->getGameState();
}

void ParallelScope::doAddScope(std::unique_ptr<Scope> toadd) {
    getCurrentThread()->addScope(std::move(toadd));
}

bool ParallelScope::empty() const {
    return threads.empty();
}

std::unique_ptr<Scope>& ParallelScope::getCurrentThread() {
    if (threads.size() == 0) {
        throw NoMoreThreadsException{};
    }
    return threads.at(curr);
}

std::pair<ParallelScope::Result, RuleType>
ParallelScope::getRuleFromCurrentThread() {
    if (threads.size() == 0) {
        return {Result::NORULES, std::nullopt};
    }
    auto mayberule = getCurrentThread()->getNextRule();
    if (mayberule) {
        return {Result::SUCCESS, mayberule};
    } else {
        return {Result::EMPTY, mayberule};
    }
}

void ParallelScope::moveToNextThread() {
    if (threads.size() == 0) {
        curr = 0;
    } else {
        curr++;
        curr %= threads.size();
    }
}

void ParallelScope::removeCurrentThread() {
    threads.erase(threads.begin() + curr);
}

//---------------------------------
// RuleThread.cpp - execution
//---------------------------------
// RuleThread::step() - execute one rule
RuleThread::ExecutionResult RuleThread::step() {
    if (thrownException) {
        return ExecutionResult::ERROR;
    }

    // We do some return value propagation, since we can't return a value from RuleThread::step() within the std::visit
    // If the std::visit returns ExecutionResult::OK it gets ignored
    // otherwise RuleThread::step() will return that value
    ExecutionResult result = std::visit(overloaded {
        [] (std::monostate) { return ExecutionResult::FINISHED; },
        [] (Scope::Blocking) { return ExecutionResult::OK; },
        [&] (const Rule &rule) {
            try {
                rule.act([this] (const auto &rule) { executeRule(rule); });
            } catch (const RuleException::RuntimeError &ex) {
                thrownException = ex;
                return ExecutionResult::ERROR;
            }
            return ExecutionResult::OK;
        }
    }, nextrule.get());

    if (result != ExecutionResult::OK) {
        return result;
    }
    
    nextrule = state->getNextRule();
    if (!nextrule) {
        return ExecutionResult::FINISHED;
    } else {
        return ExecutionResult::OK;
    }
}

//---------------------------------
// RuleThread.cpp - executeRule for parallel stuff
//---------------------------------
// code review note: "state" is the data structure I'm using to fetch the next rule to execute 
// "state" is basically a tree of "Scopes", and a Scope is basically an object which returns rules to execute one at a time

void RuleThread::executeRule(const Rules::Inparallel &rule) {
    auto parallel = std::make_unique<ParallelScope>();
    auto curstate = state->getGameState();
    for (auto &innerRule : rule.rules) {
        // owning scope here because we have to create a temporary rule list to hold a single rule
        parallel->addThread(std::make_unique<OwningRuleListScope>(curstate, RuleList{innerRule}));
    }
    state->addScope(std::move(parallel));
}

void RuleThread::executeRule(const Rules::Parallelfor &rule) {
    Value list = evaluateListOrExpression(rule.list);
    auto parallel = std::make_unique<ParallelScope>();
    auto curstate = state->getGameState();
    for (Value &val : list.get<Value::Array>()) {
        auto curstateWithForVariable = std::make_shared<ScopedGameState>(curstate.get());
        curstateWithForVariable->setVarHere(rule.element, val);
        parallel->addThread(std::make_unique<RuleListScope>(curstateWithForVariable, rule.rules));
    }
    state->addScope(std::move(parallel));
}
