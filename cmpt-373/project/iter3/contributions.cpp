/**
 * GameState.h
 */

#ifndef GAMESTATE_H 
#define GAMESTATE_H

#include "Rules.h"
#include "Config.h"
#include "GameVarList.h"

#include <stack>
#include <unordered_map>
#include <string>


/**
 *  @class GameState
 *
 *  @brief A class for maintaining state of game elements.
 */
class GameState {
    public:
        using ListItem = GameVarList::ListItem;
    	/**
    	 *	Initialize per-player, per-audience and variables maps with Config object
    	 */
    	GameState(Config c);

    	/**
    	 *	Default destructor
    	 */
    	~GameState() = default;

        // NOTE: Currently using RulesName enum as placeholder until new rules struct/class is implemented
        void pushRule(Rules::RulesName r);
        Rules::RulesName popRule();

        GameVarList getGameVars() const;
        GameVarList getPlayerVars(std::string playerName) const;
        GameVarList getAudienceVars(std::string audienceName) const;
        Config getGameConfig() const;

        // void initVariable(std::string varName, ListItem val, std::string playerName = "");

        void updateVariables(GameVarList& list);
        void updatePlayer(std::string playerName, GameVarList& list);
        void updateAudience(std::string audienceName, GameVarList& list);


    private:
        const Config config;
        std::stack<Rules::RulesName> rulesStack;
        GameVarList variables;
        std::unordered_map<std::string, GameVarList> perPlayerMap;
        std::unordered_map<std::string, GameVarList> perAudienceMap;

};

#endif

/**
 * GameState.cpp
 */

#include "GameState.h"
#include <algorithm>
#include <iostream>

using ListItem = GameVarList::ListItem;

GameState::GameState(Config c) 
    : config{c} {}

void
GameState::pushRule(Rules::RulesName r) {
    rulesStack.push(r);
}

Rules::RulesName
GameState::popRule() {
    Rules::RulesName rule = rulesStack.top();
    rulesStack.pop();
    return rule;
}

GameVarList
GameState::getGameVars() const {
    return variables;
}

GameVarList
GameState::getPlayerVars(std::string playerName) const {
    return perPlayerMap.at(playerName);
}

GameVarList
GameState::getAudienceVars(std::string audienceName) const {
    return perAudienceMap.at(audienceName);
}

Config
GameState::getGameConfig() const {
    return config;
}


void 
GameState::updateVariables(GameVarList& list) {
    variables = list;
}

void 
GameState::updatePlayer(std::string playerName, GameVarList& list) {
    perPlayerMap[playerName] = list;
}

void 
GameState::updateAudience(std::string audienceName, GameVarList& list) {
    perAudienceMap[audienceName] = list;
}

/**
 * GameSession.h
 */

#ifndef GAMESESSION_H 
#define GAMESESSION_H

#include "GameState.h"
#include "Server.h"

#include <string>


/**
 *  @class GameSession
 *
 *  @brief A class for maintaining a game session on the server
 */
using networking::Connection;

struct INVITE_CODE {
    std::string code;
};

class GameSession {
public:
    using CONNECTION_ID = uintptr_t;

    // Constructor holds GameState object and generates a random invite code for the session.
    GameSession(GameState& state);

    ~GameSession();

    INVITE_CODE getInviteCode() const;
    std::vector<Connection> getConnections() const;

    void addConnection(Connection c);
    void removeConnection(CONNECTION_ID cid);


private:
    GameState gameState;
    INVITE_CODE inviteCode;

    std::vector<Connection> connections;
};

#endif

/**
 * GameSession.cpp
 */

#include "GameSession.h"

#include <stdlib.h>
#include <ctime>
#include <algorithm>

// Generates random string consisting of letters and numbers of length 6.
INVITE_CODE
generateCode() {
    srand((unsigned int)time(NULL));
    std::string code(6, 0);
    const char values[] = {
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
    };
    auto randomChar = [values]() -> char
    {
        const size_t max_index = (sizeof(values)-1);
        return values[rand() % max_index];
    };

    std::generate_n(code.begin(), 6, randomChar);
    INVITE_CODE generatedCode;
    generatedCode.code = code;
    return generatedCode;
}


GameSession::GameSession(GameState& state) 
    : gameState{state} {
    inviteCode = generateCode();
}

GameSession::~GameSession() {}

INVITE_CODE
GameSession::getInviteCode() const {
    return inviteCode;
}

std::vector<Connection>
GameSession::getConnections() const {
    return connections;
}

void
GameSession::addConnection(Connection c) {
    connections.push_back(c);
}

void
GameSession::removeConnection(CONNECTION_ID cid) {
    connections.erase(std::remove_if(connections.begin(), connections.end(), [cid](Connection c) {
        return c.id == cid;
        }), connections.end());
}

/*
 * Parser class
 */

// Parser.h
#ifndef PARSER_H 
#define PARSER_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace json_interpreter {
/**
 *  @class Interpreter
 *
 *  @brief A class for interpreting JSON data for a game.
 *
 *  The Interpreter class that takes a JSON file and creates a Game.
 */
class Parser {
    public:
        /**
         *  Construct a Parser with a file path to a JSON file as argument
         */
        Parser(const char* filePath);

        /**
         *  Default destructor
         */
        ~Parser();

        // Getters
        json getGameJson();
    private:
        json gameJson;


};

}
#endif

// Parser.cpp

#include "Parser.h"
#include <iostream>
#include <fstream>
// #include <nlohmann/json.hpp>

using json_interpreter::Parser;
// using json = nlohmann::json

// Initialize game JSON from file path.
Parser::Parser(const char* filePath) {
    std::ifstream jsonStream;
    jsonStream.open(filePath);
    if (jsonStream.is_open() && !jsonStream.fail()) {
        jsonStream >> gameJson;
    }
}

Parser::~Parser() {}

json Parser::getGameJson() {
    return gameJson;
}

/**
 * Other contributions:
 * - Various bugfixing in chatserver.cpp to fix compiler errors
 * - Class and CMakeLists.txt refactoring for new dependencies/remove old dependencies
 */