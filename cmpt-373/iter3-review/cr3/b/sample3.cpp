
// class to represent game messages. used to communicate between game objects and any front end attached.
// methods for conversion to and from json. this isnt a coupling to network components as json is a very nice
// way of passing data
#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace Message {

enum class MessageType {
    INPUT_CHOICE,
    INPUT_VOTE,
    INPUT_TEXT,
    OUTPUT_MSG,
    OUPUT_G_MSG,
    OUPUT_SCORES
};

// for to/from json
// TODO: investigate the errors with the json macros
// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Message::GameMessage,
//             recipientId,
//             type,
//             prompt,
//             choices,
//             result,
//             timeout);

using CLIENT_ID = unsigned long;

class GameMessage{
    public:
        GameMessage();
        GameMessage(CLIENT_ID);
        // for to/from json
        // NLOHMANN_DEFINE_TYPE_INTRUSIVE(Message::GameMessage,
        //     recipientId,
        //     type,
        //     prompt,
        //     choices,
        //     result,
        //     timeout);

        std::string to_string();

    private:
        CLIENT_ID recipientId;
        MessageType type;
        std::string prompt;
        std::vector<std::string> choices;
        std::pair<std::string, std::string> result; //{varName, value}
        unsigned long timeout;

        // debug members
        void message_dump();
};

}

// json parser.cpp
#include "JsonParser.h"

#include <fstream>
#include <iostream>

JsonParser::JsonParser(std::string fileName) {
  std::ifstream ifs(fileName);
  if (!ifs.is_open()) {
    std::string errorMsg = "Unable to open file " + fileName;
    throw errorMsg;
  }

  ifs >> jsonObj;
  ifs.close();
}

std::any
JsonParser::parseValue(json jsonVal) {
  if (jsonVal.is_boolean()) return jsonVal.get<bool>();
  if (jsonVal.is_number())  return jsonVal.get<double>();
  if (jsonVal.is_string())  return jsonVal.get<std::string>();
  if (jsonVal.is_array())   return parseArray(jsonVal);
  if (jsonVal.is_object())  return parseObject(jsonVal);

  // If jsonVal is null, don't do anything for now
}

std::vector<std::any>
JsonParser::parseArray(json array) {
  std::vector<std::any> result;
  for (auto& [_, val] : array.items()) {
    result.push_back(this->parseValue(val));
  }

  return result;
}

std::unordered_map<std::string, std::any>
JsonParser::parseObject(json object) {
  std::unordered_map<std::string, std::any> result;
  for (auto& [key, val] : object.items()) {
    result.insert({key, this->parseValue(val)});
  }

  return result;
}

GameConfig
JsonParser::parseConfig() {
  json config = jsonObj.at("configuration");

  std::string name = config.at("name").get<std::string>();
  bool hasAudience = config.at("audience").get<bool>();

  json playerCount = config.at("player count");
  int minPlayers = playerCount.at("min").get<int>();
  int maxPlayers = playerCount.at("max").get<int>();

  json setup = config.at("setup");
  std::unordered_map<std::string, SetupValue> setupPairs = this->parseSetup(setup);

  GameConfig gameConfig{name, minPlayers, maxPlayers, hasAudience, setupPairs};
  return gameConfig;
}

std::unordered_map<std::string, SetupValue>
JsonParser::parseSetup(json obj) {
  std::unordered_map<std::string, SetupValue> setup;

  for (auto& [key, val] : obj.items()) {
    SetupValue setupVal;

    if (val.is_boolean())      setupVal = val.get<bool>();
    else if (val.is_number())  setupVal = val.get<int>();
    else if (val.is_string())  setupVal = val.get<std::string>();
    else if (val.is_object())  setupVal = this->parseUserPrompt(val);

    setup.insert({key, setupVal});
  }

  return setup;
}


UserPrompt
JsonParser::parseUserPrompt(json obj) {
  UserPrompt userPrompt;

  std::string kind = obj.at("kind").get<std::string>();
  userPrompt.insert({"kind", kind});

  std::string prompt = obj.at("prompt").get<std::string>();
  userPrompt.insert({"prompt", prompt});

  return userPrompt;
}

// tokenizer for the json
#include <regex>
#include <iostream>

// TODO: tokenize() should accept a string and a list of expressions
//       instead of having it hardcoded here.
std::regex OPERATOR{"^(!|==)"};
std::regex SEPARATOR{"^[.()]"};
std::regex LIST_OPERATOR{"^(contains|collect|upfrom)"};
std::regex LIST_ATTRIBUTE{"^(size|elements)"};
std::regex IDENTIFIER{"^[a-zA-Z_]\\w*"};

std::vector<std::regex> expressions = {
  OPERATOR, SEPARATOR, LIST_OPERATOR, LIST_ATTRIBUTE, IDENTIFIER
};

std::optional<std::string>
getFirstMatch(std::string str) {
  std::smatch match;

  for (auto& expr : expressions) {
    if (std::regex_search(str, match, expr)) return match.str(0);
  }

  return std::nullopt;
}

std::vector<std::string>
Tokenizer::tokenize(std::string str) {
  std::vector<std::string> tokens;

  while (!str.empty()) {
    try {
      auto match = getFirstMatch(str);
      tokens.push_back(match.value());
      str = str.substr(match.value().length());
    } catch (const std::bad_optional_access &e) {
      throw InvalidExpressionError(str);
    }
  }

  return tokens;
}

// updated version of our game session object. entirely decoupled from network, has enum class to represent status of game as well
// currenly living in a feature branch as merging it would've broken the program 😅
enum class Status {
    WAITING,
    RUNNING,
    OVER,
    FINISHED
};

using GAME_ID = unsigned long;
using CLIENT_ID = unsigned long;

class GameSession {
    public:
        GameSession(GAME_ID, GameConfig);
        void addPlayer(CLIENT_ID);
        void removePlayer(CLIENT_ID);

        void addAudience(CLIENT_ID);
        void removeAudience(CLIENT_ID);

        void update(std::vector<Message::GameMessage>); // pass in incoming messages
        std::vector<Message::GameMessage> getMessages();
        GAME_ID getInviteCode();


    private:
        GAME_ID gameId; // this'll server as the invite code as well
        GAME_ID inviteCode; // same as above but diff name

        std::vector<CLIENT_ID> players;
        std::vector<CLIENT_ID> audience;

        // TODO: replace with game state
        GameObject* game;

        // game rules object
        GameConfig spec;

        // rpn evalutator which updates game state and latest incoming messages
        // to be added later
        //GameEngine engine;
        Status status;

        std::vector<Message::GameMessage> outgoing;
        std::vector<Message::GameMessage> incoming;
};
