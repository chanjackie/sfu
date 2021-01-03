// JsonParser.cpp

nlohmann::json JsonParser::readFile(std::string fileName)
{
    nlohmann::json json;
    std::ifstream i(fileName);
    i >> json;

    return json;
}

nlohmann::json JsonParser::getConfig(nlohmann::json game)
{
    return game["/configuration"_json_pointer];
}

nlohmann::json JsonParser::getConstants(nlohmann::json game)
{
    return game["/constants"_json_pointer];
}

nlohmann::json JsonParser::getVariables(nlohmann::json game)
{
    return game["/variables"_json_pointer];
}

nlohmann::json JsonParser::getPerPlayer(nlohmann::json game)
{
    return game["/per-player"_json_pointer];
}

nlohmann::json JsonParser::getPerAudience(nlohmann::json game)
{
    return game["/per-audience"_json_pointer];
}


void JsonParser::printJson(nlohmann::json j)
{
    std::cout << j.dump(2) << "\n\n";
}

std::string JsonParser::serializeJson(nlohmann::json j)
{
    return j.dump();
}

nlohmann::json JsonParser::deSerealizeToJson(std::string str)
{
    return nlohmann::json::parse(str);
}

void JsonParser::parseRules (nlohmann::json rules) {
    for(const auto& rule : rules) {
        if(rule["rule"] == "foreach") {
            printJson(rule["rule"]);
            parseRules(rule["rules"]);
        } else if (rule["rule"] == "parallelfor") {
            printJson(rule["rule"]);   
            parseRules(rule["rules"]);
        } else if (rule["rule"] == "inparallel") {
             printJson(rule["rule"]);   
             parseRules(rule["rules"]);
        } else if (rule["rule"] == "loop") {
             printJson(rule["rule"]);   
             parseRules(rule["rules"]);
        } else if (rule["rule"] == "switch") {
            printJson(rule["rule"]);   
            parseRules(rule["rules"]);
        } else if (rule["rule"] == "when") {
            for(const auto& a_case : rule["cases"]) {
                printJson(a_case["condition"]);
                parseRules(a_case["rules"]);
            }
        } else {        
             printJson(rule["rule"]);            
        }
    }   
};

// JsonParsingsTests.cpp

TEST(JSONTests, ReadFile)
{
    //Construct equivalent json object to test.json
    json j1 = json::parse("{\"configuration\": {\"name\": \"Test\",\"player count\": {\"min\": 2, \"max\": 4},\"audience\": false,\"setup\": {\"Rounds\": 10}}}");

    json j2 = readFile(PATH_TO_TEST1_JSON);
    
    //Configuration -> Modified for Not Equal test
    json j3 = json::parse("{\"configuration\": {\"name\": \"False\",\"player count\": {\"min\": 2, \"max\": 4},\"audience\": false,\"setup\": {\"Rounds\": 10}}}");
    
    EXPECT_EQ(j1, j2);
    EXPECT_NE(j2, j3);
}

TEST(JSONTests, getConfig)
{
    json j1 = json::parse("{\"audience\": false,\"name\": \"Rock, Paper, Scissors\",\"player count\": {\"min\": 2, \"max\": 4},\"setup\": {\"Rounds\": 10}}");
    json j2 = readFile(PATH_TO_TEST2_JSON);

    EXPECT_EQ(getConfig(j2), j1);
}

TEST(JSONTests, getConstants)
{
    json j1 = json::parse("{\"weapons\": [{ \"name\": \"Rock\",     \"beats\": \"Scissors\"},{ \"name\": \"Paper\",    \"beats\": \"Rock\"},{ \"name\": \"Scissors\", \"beats\": \"Paper\"}]}");
    json j2 = readFile(PATH_TO_TEST2_JSON);

    EXPECT_EQ(getConstants(j2), j1);
}

TEST(JSONTests, getVariables)
{
    json j1 = json::parse("{\"winners\": []}");
    json j2 = readFile(PATH_TO_TEST2_JSON);

    EXPECT_EQ(getVariables(j2), j1);
}

TEST(JSONTests, getRules)
{
    json j1 = json::parse("[{\"element\":\"round\",\"list\":\"configuration.Rounds.upfrom(1)\",\"rule\":\"foreach\",\"rules\":[{\"rule\":\"global-message\",\"value\":\"Round {round}. Choose your weapon!\"}]},{\"ascending\":false,\"rule\":\"scores\",\"score\":\"wins\"}]");
    json j2 = readFile(PATH_TO_TEST2_JSON);

    EXPECT_EQ(getRules(j2), j1);
}

TEST(JSONTests, serialization)
{
    json j1 = readFile(PATH_TO_TEST2_JSON);
    std::string serialized = serializeJson(getName(j1));

    std::cout << serialized << std::endl;

    EXPECT_STREQ(serialized.c_str(), "\"Rock, Paper, Scissors\"");

    json j2 = deSerealizeToJson(serialized);

    printJson(j2);

    EXPECT_EQ(getName(j1), j2);
}

TEST(JSONTests, serialization_largeFile)
{
    json j1 = readFile(PATH_TO_TEST2_JSON);
    std::string serialized = serializeJson(j1);

    std::cout << serialized << std::endl;

    json j2 = deSerealizeToJson(serialized);

    printJson(j2);

    EXPECT_EQ(j1, j2);
}

// LogicNodes.cpp

bool InParallelNode::Execute(Game* game_instance) {
    
    // Execute all threads that have not completed
    for( auto i=0; i<GetRules()->size(); i++) {

        if ( !threadComplete.at(i) ) {

            threadComplete.at(i) = GetRules()->at(i)->Execute(game_instance);

        }

    }

    // If all threads complete, reset vector and return true
    if( std::count(threadComplete.begin(), threadComplete.end(), false) == 0 ) {

        std::fill(threadComplete.begin(), threadComplete.end(), false);
        return true;
    }

    return false;
}

// LogicNodes.hpp
                  
class InParallelNode : public LogicNode {

public:
    InParallelNode();
    ~InParallelNode();
    bool Execute(Game* gameInstance);
    void Print(int depth);
    void AddRule(LogicNode* rule);

private:
    std::vector<bool> threadComplete;

};

void InParallelNode::Print(int depth) {
    std::string tabs;
    bool block_end = false;

    tabs.insert(0, depth, '\t');

    printf("%sInParallel {\n", tabs.c_str());


    block_end = Step();
    while(!block_end) {
        GetRules()->at(GetIndex())->Print(depth + 1);
        block_end = Step();
    }

    printf("%s}\n", tabs.c_str());

    return;
}

void InParallelNode::AddRule(LogicNode* rule) {
    GetRules()->push_back(rule);
    threadComplete.push_back(false);
    return;
}


bool InputTextNode::Execute(Game* gameInstance){
    if (!waiting){
        // Waiting for a response
        waiting = true; 
        result = "";

        // Request for input from the server

    } else{

        // temporary use for dummy implementation (until networking server is set up)
        if(fakeServer.GetNumWaitTimesDummyServerResponse() == 0) {
            result = "Hello world!";
        } else {
            // continue waiting for server
            fakeServer.DecrementNumWaitTimesDummyServerResponse();
        }

        if(result.compare("") != 0){

            // No longer waiting for response
            waiting = false; 
            return true;
        }
    }

    return false;

}

// InputTextNodeTests.cpp

TEST(InputTextNodeTests, NotWaitForServer) {
    const int NUM_WAIT_TIMES_DUMMY_SERVER = 0;

    Game* game_instance = new Game;
    game_instance->rulesIndex = -1;

    FakeServer mockFakeServer;
    mockFakeServer.SetNumWaitTimesDummyServerResponse(NUM_WAIT_TIMES_DUMMY_SERVER);

    InputTextNode* inputTextNode = new InputTextNode(mockFakeServer);


    game_instance->rulesList.push_back(inputTextNode);
    

    EXPECT_EQ(game_instance->Execute(), false) << "First execution succeeded when it should have failed.";
    EXPECT_EQ(inputTextNode->fakeServer.GetNumWaitTimesDummyServerResponse(), NUM_WAIT_TIMES_DUMMY_SERVER) << "First numWaitTimes not 0.";
    EXPECT_EQ(game_instance->Execute(), true) << "Second execution failed when it should have succeeded.";
    EXPECT_EQ(inputTextNode->fakeServer.GetNumWaitTimesDummyServerResponse(), NUM_WAIT_TIMES_DUMMY_SERVER) << "Second numWaitTimes not 0.";

    delete(game_instance);
    delete(inputTextNode);
}

