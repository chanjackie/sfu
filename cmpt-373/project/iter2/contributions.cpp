/*
 * GameState class
 */

// GameState.h

#ifndef GAMESTATE_H 
#define GAMESTATE_H

#include "Rules.h"
#include "Config.h"
#include "GameVarList.h"
#include "Value.h"

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
    	/**
    	 *	Initialize per-player, per-audience and variables maps with Config object
    	 */
    	GameState(Config &c, Rules *r);

    	/**
    	 *	Default destructor
    	 */
    	~GameState();

        void pushRule(Rules r);
        Rules popRule();

        std::list<Value> selectVariable(std::string varName);
        std::list<Value> selectPlayerVal(std::string playerName, std::string varName);
        std::list<Value> selectAudienceVal(std::string audienceName, std::string varName);

        void initVariable(std::string varName, Value val, std::string playerName = "");

        void updateVariables(std::string varName, Value val);
        void updatePlayer(std::string playerName, std::string varName, Value val);
        void updateAudience(std::string audienceName, std::string varName, Value val);



    private:
        Config &config;
        std::stack<Rules> rulesStack;
        GameVarList variables;
        std::unordered_map<std::string, GameVarList> perPlayerMap;
        std::unordered_map<std::string, GameVarList> perAudienceMap;

};

#endif

// GameState.cpp

#include "GameState.h"
#include <algorithm>
#include <iostream>

GameState::GameState(Config &c, Rules *r) 
    : config{c} {
    for (uint64_t i=0; i<sizeof(r); i++) {
        pushRule(r[i]);
    }
}

void
GameState::pushRule(Rules r) {
    rulesStack.push(r);
}

Rules
GameState::popRule() {
    Rules rule = rulesStack.top();
    rulesStack.pop();
    return rule;
}

std::list<Value> 
GameState::selectVariable(std::string varName) {
    return variables.select(varName);
}

std::list<Value> 
GameState::selectPlayerVal(std::string playerName, std::string varName) {
    return perPlayerMap.at(playerName).select(varName);
}

std::list<Value> 
GameState::selectAudienceVal(std::string audienceName, std::string varName) {
    return perAudienceMap.at(audienceName).select(varName);
}

void
GameState::initVariable(std::string varName, Value val, std::string playerName) {
    std::unordered_map<std::string, Value> newMap;
    newMap.insert({varName, val});
    if (!playerName.empty()) {
        GameVarList varList;
        if (perPlayerMap.find(playerName) != perPlayerMap.end()) {
            varList = perPlayerMap.at(playerName);
        }
        varList.append(newMap);
        perPlayerMap[playerName] = varList;
    } else {
        variables.append(newMap);   
    }
}

void 
GameState::updateVariables(std::string varName, Value val) {
    std::list<Value> vals = variables.select(varName);
    if (!vals.empty()) {
        variables.update(varName, val);
    } else {
        std::cout << "Please initialize variable first\n";
    }
}

// TODO: optimize updatePlayer and updateAudience s.t. only one method 
// is needed to update either of perPlayerMap or perAudienceMap
void 
GameState::updatePlayer(std::string playerName, std::string varName, Value val) {
    if (perPlayerMap.find(playerName) != perPlayerMap.end()) {
        GameVarList varList = perPlayerMap.at(playerName);
        varList.update(varName, val);
        perPlayerMap[playerName] = varList;
    }
}

void 
GameState::updateAudience(std::string audienceName, std::string varName, Value val) {
    if (perAudienceMap.find(audienceName) != perAudienceMap.end()) {
        GameVarList varList = perAudienceMap.at(audienceName);
        varList.update(varName, val);
        perAudienceMap[audienceName] = varList;
    }
}

// game library CMakeLists.txt

add_library(game
  src/GameState.cpp
)

find_package(Boost 1.72 COMPONENTS system REQUIRED)

target_include_directories(game
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(game
  PRIVATE
    json_interpreter
    ${Boost_LIBRARIES}
)

set_target_properties(game
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS game
  ARCHIVE DESTINATION lib
)

/*
 * Chatwindow refactored into library (as it's being used both for the server interface and the chat client)
 */

// chatwindow library CMakeLists.txt
add_library(chatwindow
  src/ChatWindow.cpp
)

find_package(Curses REQUIRED)

target_include_directories(chatwindow
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(chatwindow
  PRIVATE
    ${CURSES_LIBRARIES}
)

set_target_properties(chatwindow
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS chatwindow
  ARCHIVE DESTINATION lib
)

/*
 * Other contributions:
 * - Added dynamic Value class skeleton
 * - Added update method skeleton to GameVarList class
 * - Modified chatserver.cpp to utilize ChatWindow rather than a specialized ServerWindow class to keep codebase DRY.
 */