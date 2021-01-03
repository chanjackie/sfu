// ------------------------------------------------------------------------------
// CREATED A PARSER CLASS TO USE NEW BOOST::VARAINT TYPE -> GAMEVARIANT
// ------------------------------------------------------------------------------

// h file
#ifndef SOCIAL_GAMING_PARSER_H
#define SOCIAL_GAMING_PARSER_H

#include <boost/variant.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

using namespace std;
using json = nlohmann::json;

typedef boost::variant<unordered_map<string, string>, int, double, bool, string, vector<unordered_map<string, string>>> GameVariant;

unordered_map<string, GameVariant> jsonToMap(json map);

#endif

// cpp file
#include "Parser.h"
#include <iostream>

unordered_map<string, GameVariant> jsonToMap(json jsonMap) {

    // GameMap is a map of setup || constants || variables ...
    unordered_map<string, GameVariant> GameMap;

    for (auto& itrr : jsonMap.items())
    {
        string key = itrr.key();

        switch (jsonMap[key].type()) {
            // type=bool
        case json::value_t::boolean:
            GameMap[key] = jsonMap[key].get<bool>();
            break;
            //type=integer
        case json::value_t::number_integer:
        case json::value_t::number_unsigned:
            GameMap[key] = jsonMap[key].get<int>();
            break;
            //type=double
        case json::value_t::number_float:
            GameMap[key] = jsonMap[key].get<double>();
            break;
            //type=string
        case json::value_t::string:
            GameMap[key] = jsonMap[key].get<string>();
            break;
            //type=map
        case json::value_t::object:
            GameMap[key] = jsonMap[key].get<unordered_map<string, string>>();
            break;
            //type=list
            // need to handle all types when extracting values
        case json::value_t::array:
        {
            vector<unordered_map<string, string>> vec;
            for (auto val : jsonMap[key]) {
                switch (val.type()) {
                case json::value_t::object:
                    vec.push_back(val.get<unordered_map<string, string>>());
                    break;
                // rest of the cases here
                default:
                    cout << "";
                }
            }
            GameMap[key] = vec;
        }
        break;
        default:
            cout << "";
        }
    }

    return GameMap;

}


// ------------------------------------------------------------------------------
// MODIFIED CLASS FOR CONSTANTS, VARIABLES, CONFIGURATION TO USE VARIANT TYPE GAMEVARIANT
// CREATED A "SETTINGS" CLASS FOR CONFIGURATION
// only attaching sample configuration class
// ------------------------------------------------------------------------------

// h file
#ifndef SOCIAL_GAMING_CONFIGURATION_H
#define SOCIAL_GAMING_CONFIGURATION_H
#include "Parser.h"
using namespace std;

struct PlayerCount {
    int min;
    int max;
};

// settings can be changed by users
class Settings {
private:
    unordered_map<string, GameVariant> settingsMap;

public:
    Settings(unordered_map<string, GameVariant> settingsMap);
    void printSettings();
    // update a setting
    void UpdateSetting(string keyToUpdate, GameVariant valueToUpdate);
    GameVariant getAtKey(string);
};

class Configuration {
private:

    // this might need refactoring as unordered_map<string, GameVariant>
    string name;
    PlayerCount playerCount;
    bool audience;
    Settings setup;
    // data that may be uploaded by the owner for quiz based games ?

public:
    Configuration(string name, int min, int max, bool audience, Settings setup);

    string getName();
    PlayerCount getPlayerCount();
    bool isAudible();
    Settings getSetUp();

    GameVariant getAtKey(string);
    void print();
};
#endif


// cpp file
#include "Configuration.h"
#include <iostream>

// Settings
Settings::Settings(unordered_map<string, GameVariant> settingsMap) : settingsMap(settingsMap) {}

GameVariant Settings::getAtKey(string key) {
    return this->settingsMap[key];
}


// Configuration
Configuration::Configuration(string name, int min, int max, bool audience, Settings setup)
    : name(name), playerCount({ min, max }), audience(audience), setup(setup) {}


void Configuration::print() {
    cout << "Configuration: \n"
        "   name: " << name << endl <<
        "   playerCount: min: " << playerCount.min << " max: " << playerCount.max << endl <<
        "   audience: " << audience << endl;
    setup.printSettings();

}

GameVariant Configuration::getAtKey(string key) {

    // check Settings;
    GameVariant value_at_key = this->setup.getAtKey(key);

    return value_at_key;

}


// ------------------------------------------------------------------------------
// CREATED A GAME STATE CLASS
// ------------------------------------------------------------------------------

// h file
#ifndef SOCIAL_GAMING_STATE_H
#define SOCIAL_GAMING_STATE_H

#include "Player.h"
#include "Constants.h"
#include "Configuration.h"
#include "Variables.h"
#include "PlayerSetup.h"

class State
{
private:
    vector<Player> playerList;
    vector<Player> winnerList;
    Configuration configuration;
    Constants constants;
    Variables variables;
    PerPlayer per_player;
    PerAudience per_audience;
    bool isGameEnd;

public:
    State(vector<Player> playerList, Configuration configuration,
        Constants constants, Variables variables, PerPlayer per_Player, PerAudience per_Audience);

    vector<Player> getPlayers();
    vector<Player> getWinners();
    Configuration getConfiguration();
    Constants getConstants();
    Variables getVariables();
    PerPlayer getPlayerSetp();
    PerAudience getAudienceSetup();

    // update state
    void UpdateState_Config(Configuration);
    void UpdateState_Constants(Constants);
    void UpdateState_Variables(Variables);
    void UpdateState_PerPlayer(PerPlayer);
    void UpdateState_PerAudience(PerAudience);
    void UpdateState_PlayersList(Player&);

    // string manipulations or condition checks
    vector<GameVariant> getStateList(string);
    bool checkCondition(string);

    void print();
};
#endif


// cpp file
#include "State.h"

// constructor
State::State(vector<Player> playerList, Configuration configuration,
    Constants constants, Variables variables, PerPlayer perPlayer, PerAudience perAudience)
    : playerList(playerList), configuration(configuration), constants(constants), variables(variables),
    per_player(perPlayer), per_audience(perAudience) {}

// Update State Functions
void State::UpdateState_Config(Configuration c) {
    this->configuration = c;
}
void State::UpdateState_Constants(Constants c) {
    this->constants = c;
}
void State::UpdateState_Variables(Variables v) {
    this->variables = v;
}
void State::UpdateState_PerPlayer(PerPlayer pp) {
    this->per_player = pp;
}
void State::UpdateState_PerAudience(PerAudience pa) {
    this->per_audience = pa;
}
void State::UpdateState_PlayersList(Player& p) {
    this->playerList.push_back(p);
}

// Get from State Functions
vector<Player> State::getPlayers() {
    return playerList;
}
vector<Player> State::getWinners() {
    return winnerList;
}
Configuration State::getConfiguration() {
    return configuration;
}
Constants State::getConstants() {
    return constants;
}

// incomplete
// Replace with State Value Functions
// ignores the unimplemented functions for now
vector<GameVariant> State::getStateList(string input) {

    vector<GameVariant> result;

    // we can get configuration.some_key for now
    if (input.find("configuration") != string::npos) {
        size_t pos = input.find(".") + 1;
        string substr_input = input.substr(pos, input.length());
        size_t nextPos = substr_input.find(".");
        string config_key = substr_input.substr(0, nextPos);
        GameVariant value = this->configuration.getAtKey(config_key);
        result.push_back(value);

    }
    else if (input.find("constants") != string::npos) {
        // none in rockPaperScissors
    }
    else if (input.find("variables") != string::npos) {
        // none in rockPaperScissors
    }
    else if (input.find("per-player") != string::npos) {
        // none in rockPaperScissors
    }
    else if (input.find("per-audience") != string::npos) {
        // none in rockPaperScissors
    }
    else {
        // search within constants
        GameVariant value = this->constants.getAtKey(input);
        result.push_back(value);

        //search within variables

        // search within per-player, per-audience

    }
    // value.replace(open, close, "VARIABLE");
    return result;
}

// others
void State::print() {
    this->configuration.print();
    this->constants.print();
    this->variables.print();
    this->per_player.print();
    this->per_audience.print();
    return;
}

// ------------------------------------------------------------------------------
// TEST FILE FOR STATE CLASS
// ------------------------------------------------------------------------------
class StateTest : public ::testing::Test {
protected:

    virtual void SetUp() override {
        string filePath = "rockPaperScissors.json";
        ifstream ifs(filePath, std::ifstream::binary);
        if (ifs.fail())
        {
            throw std::runtime_error("Cannot open Json file");
        }
        json GAMEJSON = json::parse(ifs);
        // EXTRACT GAME SPECIFICATION STRUCTURE
        config = GAMEJSON["configuration"];
        constants = GAMEJSON["constants"];
        variables = GAMEJSON["variables"];
        per_player = GAMEJSON["per-player"];
        per_audience = GAMEJSON["per-audience"];
        rules = GAMEJSON["rules"];

        game_settings = new Settings(jsonToMap(config["setup"]));
        configuration = new Configuration(config["name"], config["player count"]["min"],
            config["player count"]["max"], config["audience"], *game_settings);
        constant = new Constants(jsonToMap(constants));
        variable = new Variables(jsonToMap(variables));
        per_Player = new PerPlayer(jsonToMap(per_player));
        per_Audience = new PerAudience(jsonToMap(per_audience));

        mock_state = new State(allPlayer, *configuration, *constant, *variable, *per_Player, *per_Audience);

    }

    virtual void TearDown() override {
        delete game_settings;
        delete configuration;
        delete constant;
        delete variable;
        delete per_Player;
        delete per_Audience;
        delete mock_state;
    }

    json config;
    json constants;
    json variables;
    json per_player;
    json per_audience;
    json rules;

    Settings* game_settings;
    Configuration* configuration;
    Constants* constant;
    Variables* variable;
    PerPlayer* per_Player;
    PerAudience* per_Audience;
    vector<Player> allPlayer;
    State* mock_state;
};

// TEST GETTING LISTS FROM STATE
TEST_F(StateTest, List_config) {
    // get list
    string config_rounds_upfrom_1 = "configuration.Rounds.upfrom(1)";
    vector<GameVariant> result = mock_state->getStateList(config_rounds_upfrom_1);
    GameVariant expected = 10;
    EXPECT_TRUE(expected == result[0]);
}
// ------------------------------------------------------------------------------
