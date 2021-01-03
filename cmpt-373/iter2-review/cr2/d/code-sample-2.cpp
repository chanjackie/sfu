// ------------------------------------------------------------
//  ArithmeticOp.h (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

namespace arithmetic_op{
    template<class T>
    void add(T& to, const T& value){
        to += value;
    }
}

// ------------------------------------------------------------
//  OutputMes.h (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

namespace out_message{
    // This function sends a map of the output message to 
    // a specific player object contained in the to list.
    // NOTE: The returned mapping cannot be modified, i.e. it must be constant.
    template<class T>
    std::unordered_map<T, std::string> message(const std::vector<T>& to, std::string_view value) const{
        std::unordered_map<T, std::string> msg_mapping;
        for (auto &i: to) {
            auto s = std::format(value, i.getName());  // Only available in C++ 20, doing python-like formatting
                                                       // i could be player object containing all data of the current
                                                       // player in session. 
                                                       // i.getName() will return the player name as a string
            msg_mapping.insert({i, s});
        }
        return msg_mapping;
    }

    // This function displays the message on the main screen.
    // Needs more clarification on the global message functionality
    // At the moment, the interpretation is that it will be used to 
    // display the winner.
    template<class T>
    void global_message(std::string_view value, const T& winner){
            auto s = std::format(value, winner.getName());  
            std::cout << s << std::endl; 
    }

    // Not finished, need finalization of the player class
    // Printing the score of players in either asceding (default) or descending
    template<class T>
    void scores(const std::vector<T>& player_list, const T& score, bool ascending=true){
        if (ascending) {
            std::sort(player_list.begin(), player_list.end(), 
                [](const T& player1, const T& player2) {
                    return player1.getScore() <= player2.getScore();
                });
                
        } else {
            std::sort(player_list.begin(), player_list.end(), 
                [](const T& player1, const T& player2) {
                    return player1.getScore() > player2.getScore();
                });
        }
        for (auto &player : player_list) {
                std::cout << "Name: " << player.getName() << ", Score: " << player.getScore() 
                          << std::endl;
            }
    }
}

// ------------------------------------------------------------
//  PerPlayer.h and PerPlayer.cpp (Branch: organizing_structs_of_rules)
// ------------------------------------------------------------

// Containing the state of each player
// Not yet finalized

template <class T>
class PerPlayer {
    public:
        PerPlayer() = default;
        ~PerPlayer() = default;
        
        //Getter
        std::variant<std::unordered_map<std::string, std::variant<int, double, std::string, bool>>, 
                    std::vector<std::variant<std::string, int, double, bool>>, int, bool, double> getValues(){
                        return values;
                    }

        //Setter
        void updateValues(const T& value);

    private:
        std::variant<std::unordered_map<std::string, std::variant<int, double, std::string, bool>>, 
                    std::vector<std::variant<std::string, int, double, bool>>, int, bool, double> values;
};


template <class T>
void PerPlayer<T>::updateValues (const T& values) {
    this->values = values;
}

// ------------------------------------------------------------
//  Parser.cpp (Branch: config-parsing)
// ------------------------------------------------------------


const std::string CONFIG = "configuration";
const std::string NAME = "name";
const std::string PLAYERS = "player count";
const std::string MIN = "min";
const std::string MAX = "max";
const std::string AUDIENCE = "audience";
const std::string SETUP = "setup";
const std::string ROUNDS = "Rounds";

// Initialize game JSON from file path.
Parser::Parser(const char* filePath) {
	std::ifstream jsonStream;
	jsonStream.open(filePath);
	if (jsonStream.is_open() && !jsonStream.fail()) {
		jsonStream >> gameJson;
	}
}

Parser::~Parser() {}

json 
Parser::getGameJson() {
	return gameJson;
}

Config 
Parser::getParsedConfig() {
	Config config;

	// ignore this if gameJson isn't initialized
	if (gameJson) {
		config.setGameName(gameJson[CONFIG][NAME]);
		config.setMinPlayers(gameJson[CONFIG][PLAYERS][MIN]);
		config.setMaxPlayers(gameJson[CONFIG][PLAYERS][MAX]);
		config.setAudienceEnabled(gameJson[CONFIG][AUDIENCE]);
		config.setNumRounds(gameJson[CONFIG][SETUP][ROUNDS]);
	}

	return config;
}

// ------------------------------------------------------------
//  
// ------------------------------------------------------------


/**
 *  @class GameState
 *
 *  @brief A class for maintaining state of game elements.
 * 
 *  NOTES: PerPlayer class is still the experimental phase so a manual PerPlayer map is used
 *  as placeholder for now
 */

#include "Rules.h"
#include "Config.h"
#include "Value.h"

#include <stack>
#include <unordered_map>
#include <string>

class GameState {
    public:
        /**
         *    Initialize per-player, per-audience and variables maps with Config object
         */
        GameState(Config &c, Rules *r);

        /**
         *    Default destructor
         */
        ~GameState();

        void pushRule(Rules r);
        Rules popRule();

        Value getVariable(std::string varName);
        Value getPlayerVal(std::string playerName, std::string varName);
        Value getAudienceVal(std::string audienceName, std::string varName);

        void updateVariables(std::string varName, Value val);
        void updatePlayer(std::string playerName, std::string varName, Value val);
        void updateAudience(std::string audienceName, std::string varName, Value val);



    private:
        Config &config;
        std::stack<Rules> rulesStack;
        std::unordered_map<std::string, Value> variables;
        std::unordered_map<std::string, 
            std::unordered_map<std::string, Value>> perPlayerMap;
        std::unordered_map<std::string,
            std::unordered_map<std::string, Value>> perAudienceMap;

};

// ------------------------------------------------------------ 
// GameVarList.h and GameVarList.cpp (Branch: Data Structure)
// ------------------------------------------------------------

#include <string>
#include <list>
#include <unordered_map>
#include "boost/variant.hpp"

using ListItem = boost::variant< int, std::string >

class GameVarList {
    /* TODO: ensure all list item have same attributes, not sure how to do this
        Maybe always compare the keys of new items to the first item? */
    std::list< std::unordered_map < std::string, ListItem > > data;
public:
    GameVarList() noexcept;
    ~GameVarList() noexcept;
    size_t size();
    void append( std::unordered_map newEntry );

    // TODO: maybe consider change tag name to a strong type
    // get a "slice" of the list by the tag name
    std::list< ListItem > select( std::string tag );
};



GameVarList::GameVarList() 
    { }


size_t
GameVarList::size() {
    return data.size();
}


void
GameVarList append( std::unordered_map newEntry ) {
    data.push_back (newEntry);
}


std::list< ListItem >
GameVarList::select( std::string tag ) {
    // list push_back does not require allocations
    std::list result;
    std::transform( data.begin(), data.end(), std::back_inserter(result),
        [](const auto& e){ return e[tag]; });
    
    return result;
}


// ------------------------------------------------------------ 
// ------------------------------------------------------------

#include "listRules.h"
#include <algorithm>

template<class T>
bool
contains(std::vector<T> vec, T item) {
    auto iter = std::find(vec.begin(), vec.end(), item);

    return iter == vec.end(); 
}

template<class T, class Predicate>
std::vector<T>
collect(std::vector<T> vec, Predicate pred) {
    std::vector<T> result(vec.size());
    auto iter = std::copy_if(vec.begin(), vec.end(), pred);
    result.resize(vec.begin(), iter);

    return result;
}

template<class T>

template<class T>
bool
CustomGameList<T>::contains(T item) const noexcept {
    for (const auto& e : data) {
        if (item == e) {
            return true;
        }
    }

    return false;
}

template<class T>
template<class Predicate>
CustomGameList<T>
CustomGameList<T>::collect(Predicate pred) {
    CustomGameList<T> result;
    for (const auto& e : data) {
        if (pred(e)) {
            result.push_back(e);
        }
    }

    return result;
}

template<class T>
void
CustomGameList<T>::extend(const CustomGameList &other) {
    extend_n(other, data.size())
}

template<class T>
void
CustomGameList<T>::reverse() {
    std::reverse(data.begin(), data.end());
}

template<class T>
void
CustomGameList<T>::shuffle() {
    std::shuffle(data.begin(), data.end());
}

template<class T>
void
CustomGameList<T>::sort() {
    std::sort(data.begin(), data.end());
}

template<class T>
void
CustomGameList<T>::deal(const CustomGameList &other, int count) {
    other.extend_n(*this, count);
    this->discard(count);
}

template<class T>
void
CustomGameList<T>::discard(int count) {
    data.erase(data.begin(), data.begin() + count);
}

template<class T>
void
CustomGameList<T>::extend_n(const CustomGameList &other, int count) {
    data.reserve(data.size() + count);
    data.insert(data.end(), other.data.begin(), other.data.begin() + count);
}
