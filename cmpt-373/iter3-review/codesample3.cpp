// ------------------------------------------------------------
//  GameState.cpp (Branch: gameobject-class)
// ------------------------------------------------------------

#include "GameState.h"
#include <algorithm>
#include <iostream>

GameState::GameState(Config &c) 
	: config{c} {}

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

// NOTE: -
// You most likely do not want to use a linked list.
// Linked lists are best in places where you need address stability
//  or the ability to transfer elements across lists
//  (e.g. in different queues in an OS). In other cases, they are
//  usually not what you want.
// Do these APIs do queueing?
// This might also be at an abstraction level that provides less value
//   than it otherwise might.
// Is it providing name resolution across multiple scopes?
// There is more that could be hidden.

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

// NOTE: *
// Is the name of the player something that you want to use at this point?
// Are there other alternatives?
// Presently the API still allows more freedom here than you actually want.
// NOTE: -
// Be careful about pass by value and pass by reference.
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

// ------------------------------------------------------------
//  VariableTypes.h 
// ------------------------------------------------------------

#ifndef VARIABLESTYPES_H
#define VARIABLESTYPES_H

#include <type_traits>
class VariablesTypes {
    public:
        enum Types {
            // STRING,
            INT,
            DOUBLE,
            BOOL,
            UNDEFINED, // this enum will grow
        };

        VariablesTypes() : inputType(Types::UNDEFINED) {}

        
// NOTE: -
// What are the tradeoffs here?
// Can you think of a way to make this so that you don't ever care
// what the type of the thing was outside of the context in which
// the type is already known?
        template<typename InputType>
        Types getTypes (InputType input) {
            if constexpr(std::is_same<int, InputType>::value) {
                return Types::INT;
            }
            else if constexpr(std::is_same<double, InputType>::value) {
                return Types::DOUBLE;
            }
            else if constexpr(std::is_same<bool, InputType>::value) {
                // do something here
                return Types::BOOL;
            }
            // Not working currently
            // If the type is string
            // const char* should return string
            // if constexpr(std::is_same<const char*, InputType>::value) {
            //     return Types::STRING;
            // }

            return Types::UNDEFINED;
        }

        Types getInputType() { return inputType; }

    private:
        Types inputType;
};

#endif

// ------------------------------------------------------------
//  timercpp.h (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

#include <iostream>
#include <thread>
#include <chrono>

// Timer third party library: https://github.com/99x/timercpp

class Timer {
    bool clear = false;

    public:
        void setTimeout(auto function, int delay);
        void setInterval(auto function, int interval);
        void stop();

};

// NOTE: -
// If you are using threads, you are making your life harder than it needs to be.

void Timer::setTimeout(auto function, int delay) {
    this->clear = false;
    std::thread t([=]() {
        if(this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(this->clear) return;
        function();
    });
    t.detach();
}

void Timer::setInterval(auto function, int interval) {
    this->clear = false;
    std::thread t([=]() {
        while(true) {
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(this->clear) return;
            function();
        }
    });
    t.detach();
}

void Timer::stop() {
    this->clear = true;
}

// ------------------------------------------------------------
// HumanInput.h (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

#ifndef HUMANINPUT_H
#define HUMANINPUT_H

#include <vector>
#include <string_view>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "timercpp.h"

/***
 *** Need suggestion on how to approach the problem of taking in human input.
 *** This is only a placeholder as it is modeled after the Rock, Paper, Scissor.
 *** We need suggestion on how we could propmt and take input of a specific player,
 *** This currently does not work as it only prompt once on the server.
 ***/

// NOTE: *
// Good question.
// We can talk about this in class
// The problem is that you need to refine your group model of an interactive program.

//NOTE: -
// Separately. How easy to understand are these APIs?
// There are a lot of strings flowing around.
// In some cases, they make sense, because there is purely string data
// In other cases (e.g. keys of the map) the nature and purpose of the strings
//  is unclear.
// Even in the other cases, some lightweight types would make the APIs
//  inherently easier to use.

namespace human_input{
    template<class P>
    void input_choice(const P& player, std::string_view prompt, std::unordered_map<std::string, std::string>& choices, std::string& respond, long timeout = -1){
        if (timeout > 0) {
            Timer t = Timer();
            t.setTimeout([&]() {
                auto s = std::format(prompt, player.getName());

                std::cout << s << std::endl;

                for (auto i : choices) {
                    std::cout << i->first << std::endl;
                }

                std::cout << ">";
                std::cin >> respond;
            }, timeout);
        }
    }

    template<class P>
    void input_text(const P& player, std::string_view prompt, std::string& respond, long timeout = -1){
        if (timeout > 0) {
            Timer t = Timer();
            t.setTimeout([&]() {
                auto s = std::format(prompt, player.getName());

                std::cout << s << std::endl;

                std::cout << ">";
                std::cin >> respond;
            }, timeout);
        }
    }

    // TODO: Need to figure out how to prompt the input for each user within this function 
    // then count the vote
    template<class P>
    void input_vote(const P& player, std::string_view prompt, std::unordered_map<std::string, std::string>& choices, std::unordered_map<std::string, int>, long timeout = -1){
        if (timeout > 0) {
            Timer t = Timer();
            t.setTimeout([&]() {
                auto s = std::format(prompt, player.getName());

                std::cout << s << std::endl;

                for (auto i : choices) {
                    std::cout << i->first << std::endl;
                }

                std::string input;
                std::cout << ">";
                std::cin >> input;
            }, timeout);
        }
    }
}
#endif
