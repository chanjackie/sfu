// ------------------------------------------------------------
//  GameSession.h (Branch: gamesession-class)
// ------------------------------------------------------------
#ifndef GAMESESSION_H 
#define GAMESESSION_H

#include "GameState.h"
#include "Server.h"

#include <string>


/**
 *  @class GameSession
 *
 *  @brief A class for maintaining one game session on the server
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

// ------------------------------------------------------------
//  GameSession.cpp (Branch: gamesession-class)
// ------------------------------------------------------------
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


// ------------------------------------------------------------
//  GameVarList.h
// ------------------------------------------------------------
// List data structure used in GameState which is the
// cpp represention of a game configuration
class GameVarList {
public:
    using ListItem = boost::variant <bool, int, std::string>;
    GameVarList() noexcept;
    ~GameVarList() noexcept;
    size_t size();
    void append(std::unordered_map <std::string, ListItem> newEntry);

    // TODO: maybe consider change tag name to a strong type
    // get a "slice" of the list by the tag name, similar to a SELECT query
    std::list<ListItem> select(std::string tag);

    template <class Predicate>
    GameVarList collect(Predicate pred) const;
    bool contains(const GameVarList::ListItem& item) const;
    void extend(const GameVarList& other);
    void reverse();
    void shuffle();
    void sort(std::string key = "");
    void deal(GameVarList& toList, const size_t count);
    void discard(const size_t count);

private:
    /* TODO: ensure all list item have same attributes, not sure how to do this
        Maybe always compare the keys of new items to the first item? */
    std::list<std::unordered_map <std::string, ListItem>> data;
}

// ------------------------------------------------------------
//  GameVarList.cpp
// ------------------------------------------------------------
class ReturnVisitor : public boost::static_visitor<GameVarList::ListItem> {
public:
    bool operator()(bool b) const { return b; }
    int operator()(int i) const { return i; }
    std::string operator()(std::string s) const { return s; }
};


GameVarList::GameVarList() noexcept
    : data(std::list<std::unordered_map <
        std::string, GameVarList::ListItem>>()) { }


GameVarList::~GameVarList() noexcept
    { }


size_t
GameVarList::size() {
    return data.size();
}


void
GameVarList::append(std::unordered_map<
    std::string, GameVarList::ListItem> newEntry) {
    data.push_back(newEntry);
}


std::list<GameVarList::ListItem>
GameVarList::select(std::string tag) {
    // list push_back does not require allocations
    std::list< GameVarList::ListItem > result;
    std::transform(data.begin(), data.end(), std::back_inserter(result),
        [tag](auto e){
            return boost::apply_visitor(ReturnVisitor(), e[tag]);
    });

    return result;
}


void
GameVarList::shuffle() {
    // note: regular shuffle cannot be used on a list(?)
    // so here I create a "view" of the list as a vector by copying the
    // references to entries in the list to use the shuffle function without
    // needing to create copies in the vector
    std::vector<std::reference_wrapper<std::unordered_map<std::string, GameVarList::ListItem>>>
        tempView(data.begin(),data.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tempView.begin(), tempView.end(), std::default_random_engine(seed));
    // construct a new list then replace the original DATA with this list
    std::list<std::unordered_map<std::string, GameVarList::ListItem>>
        shuffledData{ tempView.begin(),tempView.end() };
    data.swap(shuffledData);
}


// ***note: this code does not compile,
// it seems like comparing the values by returning the underlying type does not work
// is there any way to do comparison without implementing the comparator for the variant?
void
GameVarList::sort(std::string key) {
    // note: the defualt key is set to ""
    // if no KEY is given, then we want to access the first item in the map
    // the map is used even when the map is not required (each list entry only contains
    // a single value with no key)
    if (key.empty()) {
        std::sort(data.begin(), data.end(), [](auto a, auto b) {
            return boost::apply_visitor(ReturnVisitor(), (a.begin())->second) <
                boost::apply_visitor(ReturnVisitor(), (b.begin())->second);
        });
    } else {
        std::sort(data.begin(), data.end(), [key](auto a, auto b) {
            return boost::apply_visitor(ReturnVisitor(), a[key]) <
                boost::apply_visitor(ReturnVisitor(), b[key]);
        });
    }
}


void
GameVarList::deal(GameVarList& toList, size_t count) {
    std::copy_n(data.begin(), count, std::back_inserter(toList.data));
    this->discard(count);
}


void
GameVarList::discard(size_t count) {
    auto endIter = data.end();
    if (count < data.size()) {
        endIter = data.begin();
        std::advance(endIter, count);
    }
    data.erase(data.begin(), endIter);
}

