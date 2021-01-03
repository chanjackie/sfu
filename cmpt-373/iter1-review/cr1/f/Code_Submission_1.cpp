////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
//Parser.h
class JSONToASTParser : public DomainSpecificParser {
public:
  JSONToASTParser(std::string json)
      : json{nlohmann::json::parse(std::move(json))} {}
  JSONToASTParser(Json &&json) : json{json} {}

private:
  const Json json;
  // Implement these in a Top Down fashion
  AST parseHelper() override;
  std::unique_ptr<ASTNode> parseRule(const Json &);
  std::unique_ptr<Rules> parseRules(const Json &);
  std::unique_ptr<FormatNode> parseFormatNode(const Json &);
  std::unique_ptr<GlobalMessage> parseGlobalMessage(const Json &);
  std::unique_ptr<VarDeclaration> parseVarDeclaration(const Json &);
  std::unique_ptr<Variable> parseVariable(const Json &);
  std::unique_ptr<ParallelFor> parseParallelFor(const Json &);
};
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
//Parser.cpp
#include "Parser.h"
#include "ASTVisitor.h"
#include <assert.h>

namespace AST {

AST JSONToASTParser::parseHelper() { return AST{parseRules(json[0]["rules"])}; }

std::unique_ptr<Rules> JSONToASTParser::parseRules(const Json &json) {

  auto rulePtr = std::make_unique<Rules>();
  for (const auto &rule : json) {
    auto &&x = parseRule(rule);
    rulePtr->appendChild(std::move(x));
  }
  return rulePtr;
}

std::unique_ptr<ASTNode> JSONToASTParser::parseRule(const Json &json) {
  if (json["rule"] == "global-message") {
    return parseGlobalMessage(json);
  } else if (json["rule"] == "parallelfor") {
    return parseParallelFor(json);
  } else {
    assert("rule not implemented yet");
    return std::unique_ptr<ASTNode>{};
  }
}

std::unique_ptr<FormatNode> JSONToASTParser::parseFormatNode(const Json &json) {

  return std::make_unique<FormatNode>(json["value"]);
}

std::unique_ptr<GlobalMessage>
JSONToASTParser::parseGlobalMessage(const Json &json) {

  auto &&format = parseFormatNode(json);
  return std::make_unique<GlobalMessage>(std::move(format));
}

std::unique_ptr<ParallelFor>
JSONToASTParser::parseParallelFor(const Json &json) {

  auto &&var = parseVariable(json);
  auto &&varDec = parseVarDeclaration(json);
  auto &&rules = parseRules(json["rules"]);

  return std::make_unique<ParallelFor>(std::move(var), std::move(varDec),
                                       std::move(rules));
}

std::unique_ptr<VarDeclaration>
JSONToASTParser::parseVarDeclaration(const Json &json) {

  return std::make_unique<VarDeclaration>(json["element"]);
}

std::unique_ptr<Variable> JSONToASTParser::parseVariable(const Json &json) {

  return std::make_unique<Variable>(json["list"]);
}
} // namespace AST
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
//GameInstance.h
#pragma once

#include "ASTVisitor.h"
#include "Room.h"
#include <list>
#include <map>
#include <memory>
#include <string>

class GameServer;
class GameManager;

struct Player {
  int id;
  std::string name;
};

struct PlayerMessage {
  Player *player;
  std::string message;
};

class GameInstance : public AST::Communicator {
public:
  GameInstance(Room &room, GameServer &server);
  void loadGame(AST::AST &ast, AST::Environment env = AST::Environment{});
  void runGame();
  bool isRunning() { return !gameTask.isDone(); }

  bool queueMessage(const User &user, std::string message);

  void sendToPlayer(const Player &player, std::string message);

  void sendGlobalMessage(std::string message) override;

  std::deque<PlayerMessage> receiveFromPlayer(const Player &player);

  const std::vector<Player> &getPlayers() const { return players; }

  bool isGameUnused() const { return room->getMembers().empty(); }

private:
  Room *room;
  GameServer *server;
  std::map<int, bool> playerMessageRequest;
  std::vector<Player> players;
  std::map<int, userid> playerIdMapping;
  std::map<userid, int> reversePlayerIdMapping;
  std::list<PlayerMessage> inboundMessageQueue;
  coro::Task<> gameTask;
  std::unique_ptr<AST::ASTVisitor> interpreter;
};
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
//GameInstance.cpp
#include "GameInstance.h"
#include "GameServer.h"
#include <algorithm>

GameInstance::GameInstance(Room &room, GameServer &server)
    : room{&room}, server{&server} {
  int counter = 0;
  for (auto &[id, user] : room.getMembers()) {
    players.push_back({counter, user->name});
    playerIdMapping.insert({counter, id});
    playerMessageRequest.insert({counter, false});
    reversePlayerIdMapping.insert({id, counter});
    ++counter;
  }
}

void GameInstance::sendToPlayer(const Player &player, std::string message) {
  auto userId = playerIdMapping.at(player.id);
  auto &user = room->getMember(userId);
  server->sendMessageToUser(user, std::move(message));
}

void GameInstance::sendGlobalMessage(std::string message) {
  server->sendMessageToRoom(*room, std::move(message));
}

std::deque<PlayerMessage>
GameInstance::receiveFromPlayer(const Player &player) {
  std::deque<PlayerMessage> messages;
  auto &&[x, y] =
      std::ranges::partition(inboundMessageQueue, [&player](auto &message) {
        return player.id != message.player->id;
      });
  std::ranges::move(x, inboundMessageQueue.end(), std::back_inserter(messages));
  inboundMessageQueue.erase(x, inboundMessageQueue.end());
  playerMessageRequest.at(player.id) = messages.empty();
  return messages;
}

bool GameInstance::queueMessage(const User &user, std::string message) {
  if (gameTask.isDone()) {
    return false;
  }
  auto playerId = reversePlayerIdMapping.at(user.getId());
  auto &player = players.at(playerId);
  if (!playerMessageRequest.at(playerId)) {
    return false;
  }
  inboundMessageQueue.push_back({&player, std::move(message)});
  return true;
}

void GameInstance::loadGame(AST::AST &ast, AST::Environment env) {
  (this->interpreter).reset();
  this->interpreter = std::make_unique<AST::Interpreter>(std::move(env), *this);
  gameTask = ast.accept(*(this->interpreter));
}

void GameInstance::runGame() {
  if (!gameTask.isDone()) {
    gameTask.resume();
  }
}