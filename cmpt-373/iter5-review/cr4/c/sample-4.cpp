/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LogicNode.cpp

bool WhileNode::Execute(Game* game_instance){
    // SEEKING ADVICE
    // Considering the possibility of an infinite loop deadlock the server, what would be recommended to avoid it?
    // I am considering a counter that will allow a certain number of iterations before returning false and can be
    // continued on the next call of Execute, but am wondering of any better solutions

    // Check game_instance
    if(game_instance == nullptr) {
        abort();
        return false;
    }

    bool waiting = false;

    while (true) {

        // Check Condition
        if(index == -1) {

            // Temporary Condition Check if not equal
            // TODO 
            // Replace condition with interpreter execution of condition

            EqualOp equals;
            auto first = game_instance->GetVariableValue(firstVar);
            auto second = game_instance->GetVariableValue(secondVar); 
            if(first == nullptr || second == nullptr) {
                // Flag error in game
                std::cout << "Could not Find Variables '" << firstVar << "' and '" << secondVar << "' in Game\n";
                return false;
            }
            std::visit(equals, first->Get(), second->Get());

            if(!equals.success) {
                // Flag error in game
                std::cout << "Equal Operation Failed\n";
                return false;
            }

            // Condition true, Step to execute rules
            if(!equals.result) {

                // Flag Error to game if empty rule list and condition true
                if( Step() ){
                    std::cout << "No Rules In While Loop\n";
                    return false;
                }
            }
            // Condition false, end of while
            else {
                return true;
            }

        }

        // Used to flag a rule waiting for input to pause execution
        waiting = true;

        // Execute Rules
        // While Rules executing successfully
        while( rules.at(index)->Execute(game_instance) ){

            // If all rules executed check condition again
            if( Step() ) {
                waiting = false;
                break;
            }

        }

        // End execution while successor nodes await input
        if(waiting) {
            return false;
        }

    }
}

bool AddNode::Execute(Game* game_instance){
    
    // Verify game_instance
    if(game_instance == nullptr) {
        // Throw Error, should never be triggered as game_instance should 
        // always be passed down from parent node
        abort();
        return false;
    }

    auto game_var = game_instance->GetVariableValue(addTo);

    if (game_var == nullptr) {
        // Flag error in game
        return false;
    }

    // Perform Calculation
    AddOp addition;

    
    std::visit(addition, game_var->Get(), GameVar{value, 0}.Get());

    if(!addition.success) {
        // Flag error in game
        return false;
    }

    if (!game_var->Set(addition.result)) {
        // Flag error in game
        return false;
    }

    return true;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GameVar.hpp

struct AddOp {
    // Acceptable operation values
    void operator()(int val, int val2) {
        result = val + val2;
        success = true;
    }

    // Parameter error catching
    template <class T1, class T2>
    void operator()(T1 val, T2 val2) {
        success = false;
    }

    int result = 0;
    bool success = false;
};

struct EqualOp {
    // Acceptable operation values
    void operator()(bool val, bool val2){
        result = (val==val2);
        success = true;
    }

    void operator()(int val, int val2){
        result = (val==val2);
        success = true;
    }

    void operator()(std::string val, std::string val2){
        result = (val==val2);
        success = true;
    }

    void operator()(std::vector<GameVar> val, std::vector<GameVar> val2){
        result = (val==val2);
        success = true;
    }

    void operator()(std::map<std::string, GameVar>  val, std::map<std::string, GameVar>  val2){
        result = (val==val2);
        success = true;
    }

    // Parameter error catching
    template<class T1, class T2>
    void operator()(T1 val, T2 val2) {
        success = false;
    }

    bool result = false;
    bool success = false;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ParserInterpreter::evaluate(std::vector<std::string> tokens) {
  int result;
  std::vector<int> rpnStack;   

  std::vector<std::string>::iterator it;
  for(it = tokens.begin(); it != tokens.end(); it++) {
    if((*it == "+")|| (*it == "/") || (*it == "*") || (*it == "-")) {
      int val1 = rpnStack.back();
      rpnStack.pop_back();
      int val2 = rpnStack.back();
      rpnStack.pop_back();

      if ((*it == "+")) {
        result = val2 + val1;
      } else if ((*it == "-")) {
        result = val2 - val1;
      } else if ((*it == "*")) {
        result = val2 * val1;
      } else if ((*it == "/")) {
        result = val2 / val1;
        // TO DO: Divide by zero.
      }

      rpnStack.push_back(result);

    } else {
      std::string temp = *it;
      int number = stoi(temp);
      rpnStack.push_back(number);
    }

  }

  return rpnStack.back();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> JsonParser::shuntingYardAlgo(const std::vector<std::string>& tokens) {
    std::vector<std::string> outputStack;
    std::vector<std::string> operatorStack;
    
    const std::map<std::string_view,std::pair<int, int>> operatorMap {
        {",",   std::make_pair<int,int>(1  ,LEFT_ASSOC)}, // Comma
        {"==",  std::make_pair<int,int>(8  ,LEFT_ASSOC)}, // Relational equal to 
        {"!=",  std::make_pair<int,int>(8  ,LEFT_ASSOC)}, // Relational not-equal to
        {">",   std::make_pair<int,int>(9  ,LEFT_ASSOC)}, // Relational greater than
        {">=",  std::make_pair<int,int>(9  ,LEFT_ASSOC)}, // Relational greater or equal than
        {"<",   std::make_pair<int,int>(9  ,LEFT_ASSOC)}, // Relational lesser than
        {"<=",  std::make_pair<int,int>(9  ,LEFT_ASSOC)}, // Relational lesser or euqal than
        {"+",   std::make_pair<int,int>(12 ,LEFT_ASSOC)}, // Addition
        {"-",   std::make_pair<int,int>(12 ,LEFT_ASSOC)}, // Subtraction
        {"*",   std::make_pair<int,int>(13 ,LEFT_ASSOC)}, // Multiplication
        {"/",   std::make_pair<int,int>(13 ,LEFT_ASSOC)}, // Division
        {"!",   std::make_pair<int,int>(15 ,LEFT_ASSOC)}, // Locigical Not
        {".",   std::make_pair<int,int>(17 ,LEFT_ASSOC)}, // Dot operator
    };

    for(const auto& token : tokens) { 

        if(ispunct(token.front())) { // check if token is operator

            if(token == "(") {
                operatorStack.push_back(token); // Push it onto operator stack
                continue;
            } else if (token == ")") {              
                while (!operatorStack.empty() && operatorStack.back() != "(") {
                    outputStack.push_back(operatorStack.back());
                    operatorStack.pop_back();   
                    if(operatorStack.empty()) {
                        // Throw excpetion: Mismatched brackets
                    }
                }
                if (operatorStack.back() == "(") {
                    operatorStack.pop_back(); // Discard '('
                }
                continue;
            } else if (!operatorStack.empty()) {
                auto lastOperator =  operatorMap.find(operatorStack.back());
                auto currentOperator =  operatorMap.find(token);

                while(!operatorStack.empty()
                        && (comparePrec(lastOperator->second, currentOperator->second) > 0
                            || (comparePrec(lastOperator->second, currentOperator->second) == 0 
                                && isLeftAssoc(currentOperator->second)))
                        && operatorStack.back() != "(") {

                    outputStack.push_back(operatorStack.back());
                    operatorStack.pop_back();

                    if(!operatorStack.empty()) {
                        lastOperator = operatorMap.find(operatorStack.back());
                    }
                }
            }

            operatorStack.push_back(token);

        } else { // else token is operand
            outputStack.push_back(token);
        }
    }

    // push remaining operators onto outputStack in reverse orfer
    std::for_each(operatorStack.rbegin(), operatorStack.rend(), 
        [&outputStack](const auto& op) {
            outputStack.push_back(op);
        });

    return outputStack;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////