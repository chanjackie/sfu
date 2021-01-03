===================================== Part 1: MessageHandler.h =========================================
#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

#include <iostream>
#include <string>
#include <deque>
#include <string_view>
#include "Server.h"
#include "GameManager.h"

using networking::Message;

using Command = std::string;

class MessageHandler {
public:
    MessageHandler(GameManager& Manager) : manager(Manager) { };
	~MessageHandler();

    void handleMessages(const std::deque<Message>& incoming);

private:
    GameManager& manager;

    Command create = "create";
    Command join = "join";
    Command leave = "leave";

    void handleCreateMessage(const Message& message, const std::string& argument);
    void handleJoinMessage(const Message& message, const std::string& argument);
    void handleLeaveMessage(const Message& message, const std::string& argument);
    void handle(const Message& message);

    typedef void(MessageHandler::*handler)(const Message&, const std::string&);

    std::map<Command, handler> commandToHandler = {
        {create, &MessageHandler::handleCreateMessage},
        {join, &MessageHandler::handleJoinMessage},
        {leave, &MessageHandler::handleLeaveMessage}
    };
};

#endif

===================================== Part 2: MessageHandler.cpp =========================================
void MessageHandler::handleMessages(const std::deque<Message>& incoming){
    for (auto& message : incoming) {
        auto text = message.text;
        auto commandSeparator = text.find(" ");
        std::string_view command = std::string_view(text).substr(0, commandSeparator);
        std::string_view argument = std::string_view(text).substr(commandSeparator + 1);

        auto it = commandToHandler.find(std::string(command));
        if (it != commandToHandler.end()) {
            std::invoke(it->second, this, message, std::string(argument));
        } else {
            handle(message);
        }
    }
}

void MessageHandler::handleCreateMessage(const Message& message, const std::string& argument) {    
    manager.createNewGame(message.connection);    
}

void MessageHandler::handleJoinMessage(const Message& message, const std::string& argument) {    
    manager.addPlayerToGame(std::stoul(argument), message.connection);    
}

void MessageHandler::handleLeaveMessage(const Message& message, const std::string& argument) {
    manager.removePlayerFromGame(message.connection);
}

void MessageHandler::handle(const Message& message){
    manager.addMessageForGames(message);
}

===================================== Part 3: Game.cpp =========================================
/*
Game captures the state of the game from beginning to end
works with players
*/

#include <iostream>

#include "Game.h"
#include <Player.h>

namespace game {


//need to pass in a game configuration
Game::Game(GameConfig& gc, uintptr_t creatorId, uint32_t gameId){
  this->gameId = gameId;
  this->gc = gc;
  this->creatorId = creatorId;
} 

Game::~Game(){}

//starts a game
void Game::update(){
  //clear outgoing message buffer before handling and constructing new outgoing messages.
  outgoingMessages.clear();

  if(!incomingMessages.empty()){
    // Do stuff with inputBuffer
    // ...
    // Chat Room Game
    // ----------------------------------------------------------------
    

    for(auto &message : incomingMessages){
      for(auto &player : players){
        outgoingMessages.push_back(
          GameMessage{player, message.player.getName() + ": " + message.text + "\n"}
        );
      }
    }
    // ----------------------------------------------------------------
  }
  //empty inputbuffer
  incomingMessages.clear();
}

void Game::recieveMessage(GameMessage inputStream){
  incomingMessages.push_back(inputStream);
}

std::deque<GameMessage> Game::sendMessage(){
  return outgoingMessages;
}

//adds a player to the game
bool Game::addPlayer(Player player){
  if(players.size() + 1 > maxPlayers){
    return false;
    }
  players.push_back(player);
  return true;
}

std::string Game::getJoinCode(){
  return std::to_string(gameId);
}

uint32_t Game::getGameId(){
	return gameId;
}

bool Game::enoughPlayers() {
  return (players.size() <= this->gc.getMaxPlayers() && players.size() >= this->gc.getMinPlayers());
}

const std::vector<Player>& Game::getPlayers() {
  return players;
}

Player& Game::getPlayer(Connection c){

  auto it = std::find_if(players.begin(), players.end(), [&c](const Player &p) {
      return p.getConnection() == c;
  });

  if (it != players.end()) {
    return *it;
  }
  
  throw std::out_of_range("Connection not found in players!");
}

void Game::removePlayer(Player player) {
    auto it = std::find(players.begin(), players.end(), player);
    if (it != players.end()){
      players.erase(it);            
    }
    else{
      throw std::out_of_range("Could not remove player!");
    }
}

} //namespace game

===================================== Part 4: Player.h =========================================
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Server.h"

using networking::Connection;

class Player {
public:
    Player(std::string name, Connection connection);

    std::string getName() const;  
    Connection getConnection() const;  

    bool operator==(const Player& other) const;
private:                
    std::string name;
    Connection connection; 
};



#endif
