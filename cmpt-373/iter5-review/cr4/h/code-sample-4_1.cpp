
//Where we actually execute the Rule
void RuleAstVisitor::visit(ForEachRule &forEachRule, State &gameState)
{
	//TODO: turn the "list" and "element" variables into a actual thing we can use
	// this should be done by calling execute funtion in obj Element and List
	forEachRule.execute(gameState);
	// this should be done by calling execute funtion in obj Element and List
	std::cout << "This is ForEachRule visit function" << std::endl;
	forEachRule.setNumLoop(forEachRule.getList().getList().size());
	vector<AstNode *> ruleList = forEachRule.getRuleList();
	for (int y = 0; y < forEachRule.getNumLoop(); y++)
	{

		RuleAstVisitor visitor;
		for (auto i : ruleList)
		{
			i->accept(visitor, gameState);
		}
		std::cout << std::endl;
		gameState.incrementCurrentRound();
	}
}

void RuleAstVisitor::visit(GlobalMessage &globalMessage, State &gameState)
{
    //TO DO: Push the cout statement to a message Queue to throw to server side
    globalMessage.execute(gameState);
    std::cout << globalMessage.getCompleteMessage() << endl;
}

/////////////////////////////////////////////////////////////////////
//GolabalMessage class. This class is to store the data.
/////////////////////////////////////////////////////////
string GlobalMessage::getMessage(){
  return value;
}

string GlobalMessage::getCompleteMessage(){
  return decipheredMsg;
}

void GlobalMessage::execute(State& gameState) {
  vector<GameVariant> list = gameState.getStateList(value);
  int convert = boost::get<int>(list.at(gameState.getCurrentRound()-1));
  decipheredMsg = Interpreter::InterpretString(value, gameState, to_string(convert));
}

void GlobalMessage::accept(AstVisitor& visitor, State& gameState) {
    visitor.visit(*this, gameState);
}

//////////////////////////////////////////////////////////////////////////
//Interpreter: Get the original string from Json (i.e "Round {round}) and return deciphered string (I.e. "Round 1.Hello")
///////////////////////////////////////////////////////////////
//interpreter.h
namespace INTERPRETER {

	vector<Player> InterpretListOfPlayers(string&, State&);
	vector<unordered_map<string, string>> InterpretList(string&, State&);

	// like rounds.upfrom(1); ??
	// vector<int> InterpretFunction(string&, State&);

	string InterpretString(string&, Element&, State&);
	bool InterpretCondition(string&, Element&, State&);
}

//interpreter.cpp 
// HELPER functions -----------------------------------------------------------
namespace HELPER {

	vector<Player> InterpretPlayers(string& input, State& state) {
		vector<Player> players_list;
		vector<string> tokens = splitString(input, '.');

		if (tokens[0] == "players") {
			players_list = state.getPlayers();
		}
		else if (tokens[0] == "winners") {
			players_list = state.getWinners();
		}
		return players_list;
	}

	// curly brackets
	string InterpretString(string& msg, Element& element, State& state) {
		string result = msg;

		std::size_t start = msg.find('{');
		std::size_t end = msg.find('}');
		bool curly_brackets_exist = (start != std::string::npos)
			&& (end != std::string::npos)
			&& (start < end);

		string stringToExtract = msg.substr(start + 1, end - start - 1);
		vector<string> tokens = splitString(stringToExtract, '.');

		if (curly_brackets_exist) {
			string get_element_as_string = "";

			if (tokens[0] == "player" || tokens[0] == "winner") {
				Player current_player = element.getPlayer();
				get_element_as_string = current_player.getWithKey(tokens[1]);

			}
			else if ((tokens[0] == "players" || tokens[0] == "winners") && tokens.size() > 2) {
				if (tokens[1] == "elements") {
					result = "";
					vector<Player> list = InterpretPlayers(tokens[0], state);
					for (auto player : list) {
						string token_value_at_index = player.getWithKey(tokens[2]);
						token_value_at_index += " ";
						result += token_value_at_index;
					}
				}
			}
			else {
				get_element_as_string = element.getValue();
			}
			string var = "{" + stringToExtract + "}";
			boost::replace_all(result, var, get_element_as_string);
		}
		return result;
	}

	string InterpretString(string& msg, State& state) {
		string result = msg;

		vector<string> tokens = splitString(msg, '.');
		string first_key = tokens[0];

		// players vectors
		if ((tokens[0] == "players" || tokens[0] == "winners")) {

			vector<Player> players = InterpretPlayers(tokens[0], state);
			if (tokens[1] == "size") {
				result = to_string(players.size());
			}

		}
		// other variables
		else {
			GameVariant first_variable_variant = state.getFromState(first_key);

			if (boost::apply_visitor(gameVariant_to_string(), first_variable_variant) != "") {
				result = boost::apply_visitor(gameVariant_to_string(), first_variable_variant);
			}

			if (tokens.size() > 1) {
				// must be vector or a map to have a second key
				string second_key = tokens[1];
				VARIATION variable_type = boost::apply_visitor(check_type(), first_variable_variant);

				if (variable_type == VARIATION::MAP) {
					unordered_map<string, string> map = boost::get<unordered_map<string, string>>(first_variable_variant);
					result = map.at(second_key);
				}
				else if (variable_type == VARIATION::VECTOR) {
					result = "";
					vector<unordered_map<string, string>>
						vec = boost::get<vector<unordered_map<string, string>>>(first_variable_variant);

					for (auto vector_index : vec) {
						string token_value_at_index = vector_index.at(second_key);
						token_value_at_index += " ";
						result += token_value_at_index;
					}

				}
			}
		}
		return result;
	}

	vector<string> SplitOutFunction(string& input) {
		vector<string> split_at_function_param = splitString(input, '(');
		vector<string> tokens = splitString(split_at_function_param[0], '.');

		string function = tokens.back();
		if (split_at_function_param[1].back() == ')') {
			function = function + "(" + split_at_function_param[1];
		}
		tokens.pop_back();

		tokens.push_back(function);
		return tokens;
	}

	bool ApplyFunction(State& state, string function,
		vector<Player> players, vector<string> tokens, string element) {

		string element_key = tokens[2];
		if (function.find("contains") != string::npos) {
			for (auto& player : players) {
				if (player.getWithKey(element_key) == element) {
					return true;
				}
			}
		}
		return false;
	}

}

//use case of the helper function:
// ----------------------------------------------------------------------------
/*
  Ideally, we want one InterpretList to return any type of list,
  but we would need to be able to return either vector<Player>
  or vector<unordered_map<str,str>>.
  Perhaps we can just template<T> for return type and write a length function.
  This might not be clean though.
*/
vector<Player>
INTERPRETER::InterpretListOfPlayers(string& input, State& state) {
	return HELPER::InterpretPlayers(input, state);
}


//InputChoice Rule implementation
string getInputFromUser( atomic_bool &cancelled) 
{
    string input;
    while (!cancelled)
    {
        //ToDo: Get input from user. Do you have any suggestion to get the input?
    }
    return input;
}
void RuleAstVisitor::visit(InputChoiceRule &inputChoice, State &gameState)
{
    std::cout << "This is InputChoiceRule visit function" << std::endl;
    //TODO: : Somehow ask the player for their input


    // TODO: Ask for input from chosen one
    atomic_bool cancellation_token= ATOMIC_VAR_INIT(false);
    int timeout = inputChoice.getTimeOut();
    std::chrono::seconds chronoTimeout(timeout);
    std::future<string> task = std::async(launch::async, getInputFromUser, ref(cancellation_token)); //Should I create a class for this?
    string result;
    cout<<std::chrono::seconds(chronoTimeout).count()<<endl;
    if (std::future_status::ready == task.wait_for(std::chrono::seconds(10)))
    {
        result = task.get();
    }
    else
    {
        cout << "user doesnt enter input" << endl;
        cancellation_token = ATOMIC_VAR_INIT(true);
    }
    //TODO: Map result to variable
}

/////////////////////////////////////////////////////////////////////////////
// When Rule implementation
/////////////////////////////////////////////////////////////////////////////

//WhenRule.h
class Case { //contents of what a case consists of
private:
    string stringCondition;
    vector<AstNode*> ruleList;
public:
    Case(string);
    void addRule(AstNode* );
    void print();
};

class WhenRule : public AstNode {
public:
    WhenRule(vector<Case*> &caseList);
    void accept(AstVisitor& visitor, State& gameState) override;
    void execute(State&) override;
    void addCase(Case*);
    void print();

private:
    vector<Case*> caseList;
};

#endif

//WhenRule.cpp
Case::Case(string condition)
: stringCondition(condition)
{}

void Case::addRule (AstNode* rule){
    ruleList.push_back(rule);
}

WhenRule::WhenRule(vector<Case*> &caseList)
: caseList(caseList)
{}

//[QUESTION]: is this an appropriate way of executing the rule?
enum Outcome { Success, Failure };

Outcome isConditionTrue(Case* condition) {
    //TODO: condition here is still a string so it must be interpreted beforehand. our idea was to call the interpreter that will parse the string
    // and turn it into an actual boolean condition. class Case stores strings though so all data will still be stored as string. it would just 
    // be parsed during this exection. this was our idea for all of the other rules. data will be stored in strings and will be parsed each time 
    // when the rule needs to be executed. 
    bool interpretedCondition = //call interpreter;
    if (interpretedCondition){
        return Outcome::Success;
    } else {
        return Outcome::Failure;
    }
}

void WhenRule::execute(State& gameState) {
    Outcome outcome;
    for (Case condition : caseList) {
        outcome = isConditionTrue(condition);
        if (outcome == Outcome::Success) {
            executeHelper(gameState, condition);
        }
    }
}

void WhenRule::executeHelper(State& gameState, Case condition) {
    //yet to implement but it would call the execute function of the appropriate rule 
}