//////////
// Server
//////////

// functions in server

// Creates unique code to identify the session
std::string CasabeServer::GenerateInviteCode(Server* server) {
    size_t codeLength = 6;
    std::string tempCode;

    const char codeCharDB[] =
        "1234567890"
        "QWERTYUIOPASDFGHJKLZXCVBNM"
        "qwertyuiopasdfghjklzxcvbnm";

    // Use the time and id of calling process' parent 
    // to improve randomness of the seed
    srand(abs(time(NULL) * getpid()));

    // Loop generation until code is unique 
    // or 10 (arbitrary number) tries
    bool isUnique = false;
    for(size_t j = 0; j < 10 && !isUnique; j++){
      tempCode = "";

      for(size_t i = 0; i < codeLength; i++){
          tempCode.push_back(
              codeCharDB[rand() % (sizeof(codeCharDB) - 1)]
          );
      }

      // For unit testing
      std::cout << "Invite Code is: %s\n" << tempCode; 

      // Search for duplicate code
      std::vector<std::string>::iterator iterateCodes 
          = find(inviteCodeList.begin(), inviteCodeList.end(), tempCode);
      if (iterateCodes != inviteCodeList.end()){
          isUnique = true;
          inviteCodeList.push_back(tempCode);
      }
    }

    return (isUnique ? tempCode : "INVALID");

}

////////////
// Sessions
////////////

// Create new game instance for session
std::pair<std::string, std::string> Session::CreateGame(nlohmann::json reqObj, uintptr_t clientId) {
    
    gameInstance = Game();
    std::pair<std::string, std::string> statusPayload;   
    statusPayload.first = "awwwwsumpossum";
    statusPayload.second = inviteCode;

    return statusPayload;
}

// Add new player to game session
std::pair<std::string, std::string> Session::AddPlayer(nlohmann::json reqObj ,uintptr_t clientId) {

    std::pair<std::string, std::string> statusPayload;

    //check if player name is unqiue to session
    std::string payloadStr = JsonParser::jsonToStr(reqObj["payload"]);
    
    auto it = (std::find_if(gameInstance.GetPlayerList().begin(), 
                          gameInstance.GetPlayerList().end(),
                          [payloadStr](Player p) {return p.name.compare(payloadStr) == 0;}));

    if (it == gameInstance.GetPlayerList().end()) {

        // in BIZNEZ
        // Set player attributes
        Player newPlayer = gameInstance.CreatePlayer();
        newPlayer.id = clientId;
        statusPayload.first = "awwwwsumpossum";
        statusPayload.second = "Hello Player :)";

        // Add player to the game session's player list
        gameInstance.GetPlayerList().push_back(newPlayer);

    } else {
        /**
         * TODO: return error to client - cannot create player
         * */
        statusPayload.first = "yikes";
        statusPayload.second = "no";
    }
    
    return statusPayload;
}

std::pair<std::string, std::string> Session::StartNewGame(nlohmann::json reqObj, uintptr_t clientId) {
    std::pair<std::string, std::string> statusPayload;   
    statusPayload.first = "awwwwsumpossum";
    statusPayload.second = inviteCode;

    return statusPayload;
}

Session::Session(std::string inviteCode) : inviteCode(inviteCode) {

    // Create map of responses to functions
    mapResToFunc.insert(std::make_pair(200, &Session::ContinueTask));
    mapResToFunc.insert(std::make_pair(403, &Session::RejectPermissions));
    mapResToFunc.insert(std::make_pair(404, &Session::InvalidRequest));
    mapResToFunc.insert(std::make_pair(500, &Session::GameEngineError));
    mapResToFunc.insert(std::make_pair(503, &Session::ConnectionError));

    // Create map of requests to functions
    mapReqToFunc.insert(std::make_pair("Create Game", &Session::CreateGame));
    mapReqToFunc.insert(std::make_pair("Join", &Session::AddPlayer));
    mapReqToFunc.insert(std::make_pair("Start Game", &Session::StartNewGame));

    /**
     * 
     * TODO: implement other requests
     * mapReqToFunc.insert(std::make_pair("Add Rules", &Session::AddRules));
     * mapReqToFunc.insert(std::make_pair("Edit Rounds", &Session::EditRounds));
     * mapReqToFunc.insert(std::make_pair("End Game", &Session::EndCurrGame));
     * mapReqToFunc.insert(std::make_pair("Continue Game", &Session::ContinueGame));
     * 
     * */
}

// Manages responses to request messages
ResponseMessage Session::HandleRequest(nlohmann::json reqObj, uintptr_t id) {

    std::string commandStr = JsonParser::jsonToStr(reqObj["command"]);
    
    // Go to the helper function
    std::pair<std::string, std::string> statusPayload = mapReqToFunc[commandStr](*this, reqObj, id);

    ResponseMessage responseMsg;
    std::vector<uintptr_t> noClients;
    responseMsg.clientList = noClients;
    responseMsg.status = statusPayload.first;
    responseMsg.payload = statusPayload.second;   

    return responseMsg;
}


/////////
// Parser
/////////

// functions in parser

std::vector<std::string> JsonParser::shuntingYardAlgo(const std::vector<std::string>& tokens) {
    std::vector<std::string> outputStack;
    std::vector<std::string> operatorStack;
    
    const std::map<std::string_view,std::pair<int, int>> operatorMap {
        {"+", std::make_pair<int,int>(0,LEFT_ASSOC)},
        {"-", std::make_pair<int,int>(0,LEFT_ASSOC)},
        {"*", std::make_pair<int,int>(5,LEFT_ASSOC)},
        {"/", std::make_pair<int,int>(5,LEFT_ASSOC)}
    };

    for(const auto& token : tokens) { 

        // auto lastOperator = std::find_end(operatorMap.begin(), operatorMap.end(), begin.end(), operatorMap.end());
        // auto currentOperator =  operatorMap.find(token);

        if(ispunct(token.front())) { // check if token is operator

            if(!operatorStack.empty()) {
                auto lastOperator =  operatorMap.find(operatorStack.back());
                auto currentOperator =  operatorMap.find(token);

                while(!operatorStack.empty()
                        && (comparePrec(lastOperator->second, currentOperator->second) > 0
                            || (comparePrec(lastOperator->second, currentOperator->second) == 0 
                                && isLeftAssoc(currentOperator->second)))) {

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
        [&outputStack](const auto& op) {outputStack.push_back(op);
    });

    return outputStack;
}

std::vector<std::string> JsonParser::tokenizeStr(const std::string_view str) {
    std::vector<std::string> result;
    auto policy = [](auto fst, auto snd) { 
        return (isalnum(fst) && ispunct(snd))
            || (ispunct(fst) && isalnum(snd));
    };

    for (auto first = str.begin(); first != str.end(); ++first) {
        
        auto last = std::adjacent_find(first, str.end(), policy);
        if(last == str.end()) {
            result.emplace_back(first, last);
            break;
        }
        result.emplace_back(first, last+1);
        first = last == str.end() ? last-1 : last;

    }
    return result;
}   

void JsonParser::removeSpaces (std::string& str) {
    auto it = std::remove_if(str.begin(), str.end(), [](auto& i){return std::isspace(i);});
    if(it != str.end()) {
        str.erase(it, str.end());
    }
}

void parseConfig(const nlohmann::json& j, Casabe::GameSpec& gameSpec)
{
    nlohmann::json jConfig = JsonParser::getConfig(j);

    gameSpec.setName(JsonParser::serializeJson(JsonParser::getName(j)));
    gameSpec.setMinPlayers(jConfig["player count"]["min"].get<int>());
    gameSpec.setMaxPlayers(jConfig["player count"]["max"].get<int>());
    gameSpec.setAudience(jConfig["audience"].get<bool>());
}

// Initial skeleton for parsing JSON to GameSpec foir protoyping
// TODO: LOTS O STUFF
Casabe::GameSpec JsonParser::parseGame(const nlohmann::json& j)
{
    Casabe::GameSpec gameSpec;

    std::string gameName = JsonParser::serializeJson(JsonParser::getName(j));

    parseConfig(j, gameSpec);

    auto rulesJson = JsonParser::getRules(j);
    JsonParser::parseRules(rulesJson, gameSpec.getRules());

    return gameSpec;
}

////////////
// GameVar
////////////

// enum Type class
enum class Type {
    BOOL, INT, STR, LIST, MAP
};

// GameVar class definition
class GameVar {

public:
    // Declare local type to simplify variant
    using var_t = std::variant< 
            bool,
            int, 
            std::string, 
            std::vector<GameVar>, 
            std::map<std::string, GameVar> 
            >;

    // Constructors to generate each type of variable
    GameVar(bool val, bool constant);
    GameVar(int val, bool constant);
    GameVar(std::string_view val, bool constant);
    GameVar(const char* val, bool constant); // Required to convert string literals to string instead of bool
    GameVar(std::vector<GameVar> val, bool constant);
    GameVar(std::map<std::string, GameVar> val, bool constant);
    
    ~GameVar() = default;

    // Getters and Setters
    // Setters return true on success (same type and not constant) 
    //  and false on failure 
    var_t Get();
    bool Set(bool val);
    bool Set(int val);
    bool Set(std::string val);
    bool Set(const char* val);
    bool Set(std::vector<GameVar>& val);
    bool Set(std::map<std::string, GameVar>& val);
    template <class T> 
    bool Set(T val){
        return false;
    }

    bool operator==(const GameVar& var) const noexcept {
        return type == var.type && value == var.value && isConstant == var.isConstant;
    }

private:
    Type type;
    var_t value;
    bool isConstant;

};

