// parser.cpp =======================================================
#include <iostream>
#include <filesystem>
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/any.hpp>
#include <string>

#include "parser.h"

nlohmann::json readJsonFile(std::string gameName){
    std::string gameJsonFilePath = DEFAULT_GAME_PATH + "/" + gameName + ".json";
    std::ifstream readGame(gameJsonFilePath);
    nlohmann::json jsonGame;
    readGame >> jsonGame;

    return jsonGame;
}

std::unordered_multimap<std::string, int> parseConfiguration(nlohmann::json jsonGame){
    //TODO: Need to fix this function to work for nested
    std::unordered_multimap<std::string, int> map;

    return map;
}

std::unordered_multimap<std::string, std::string> parseConstants(nlohmann::json jsonGame){

    std::unordered_multimap<std::string, std::string> map;

    for(auto& x : jsonGame["constants"].items()){
        map.insert({x.key(), x.value()});
    }

    return map;
}

std::unordered_multimap<std::string, int> parseVariables(nlohmann::json jsonGame){

    std::unordered_multimap<std::string, int> map;

    for(auto& x : jsonGame["variables"].items()){
        map.insert({x.key(), x.value()});
    }

    return map;
}

std::unordered_multimap<std::string, std::string> parsePerPlayer(nlohmann::json jsonGame){

    std::unordered_multimap<std::string, std::string> map;

    for(auto& x : jsonGame["per-player"].items()){
        map.insert({x.key(), x.value()});
    }

    return map;
}


std::unordered_multimap<std::string, std::string> parsePerAudience(nlohmann::json jsonGame){
    std::unordered_multimap<std::string, std::string> map;

    for(auto& x : jsonGame["per-audience"].items()){
        map.insert({x.key(), x.value()});
    }

    return map;
}

// ===============================================================

// Class definition - any structural changes?

class GlobalMessage{

public:
    GlobalMessage();

    GlobalMessage(std::string msg, std::string ruleParam, std::string valueParam);

    std::string getMessage();
    std::string getRule();
    std::string getValue();

    void processMessage(std::string msg);
    void replaceMessage(std::string msg);
    void printMessage();

private:
    std::string message;
    std::string rule;
    std::string value;
};

// ===============================================================

#pragma once
#include "rule.h"
#include <iterator>

template<typename Element>
class ForEachRule : Rule {
public:
    ForEachRule(std::vector<Element> collection);

    void execute(GameState state) override;

    // A ForEachRule's iteration is completed when it has gone through each of its
    // elements.  
    bool iterationComplete() override;

private:
    const std::vector<Element> collection;
    int iterations;
};

#include "include/forEachRule.h"

template<typename Element>
ForEachRule<Element>::ForEachRule(std::vector<Element> collection)
    : collection(collection), iterations(0)
    {}

template<typename Element>
void ForEachRule<Element>::execute(GameState state) {
    std::unordered_map<std::string, Player> players = state.getPlayers();
    //for first iteration add currentPlayer to vars map
    if (iterations==0) {
        auto firstPlayer=players.begin();
        state.addVar("currentPlayer", Value(firstPlayer->first));
    }
    //update vars map with new currentPlayer
    int i=0;
    for ( auto it = players.begin(); it != players.end(); ++it ) {
        if (i==iterations) {
           state.updateVar("currentPlayer", Value(it->first));
           break;
        }
        else {
            i++;
        }
    }
    iterations++;
} 

template<typename Element>
bool ForEachRule<Element>::iterationComplete() {
    return (iterations == collection.size()); 
}