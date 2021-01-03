// from src/server/GameServer.cpp
void
GameServer::run() {
  while (true) {
    bool errorWhileUpdating = false;
    try {
      server.update();
    } catch (std::exception& e) {
      std::cerr << "Exception from Server update:\n"
                << " " << e.what() << "\n\n";
      errorWhileUpdating = true;
    }

    if (errorWhileUpdating) {
      break;
    }

    //EXTREMELY IMPORTANT -- run the game logic!
    //iterate though the unordered list of current game sessions and update the game accordingly
    //TODO: create a update parser to send update requests to the correct class methods
    // for (auto &x : gameSessions) {
    //   if(x.second.game != NULL) {
    //     x.second.game->update();
    //   }
    // }

    // Get updates as GameMessages from game sessions
    std::unordered_map<std::string, GameSession>::iterator it = gameSessions.begin();
    while(it != gameSessions.end()) {
      GameSession session = (it->second);
      std::vector<GameMessage> updates = session.getUpdates();
      handleGameUpdates(updates, session);
      it++;
    }

    // Get messages from client
    auto incoming = server.receive();
    handleIncomingMessages(incoming);

    server.send(outgoingMessages);
    outgoingMessages.clear();

    sleep(1);
  }
}

// from src/server/GameServer.cpp
void
GameServer::processUnassignedClientMessage(const networking::Message &message) {
  std::ostringstream result;

  if (message.text == "new") {
    std::string inviteCode = getInviteCode();
    assignedClients.insert({message.connection.id, inviteCode});
    GameSession session{message.connection, inviteCode};
    gameSessions.insert({inviteCode, session});

    std::cout << "New session created: " << inviteCode << "\n";
    result << "Server> You are the host of the game with invite code " << inviteCode << "\n";
  } else {
    std::string inviteCode = message.text;
    bool validInviteCode = gameSessions.find(inviteCode) != gameSessions.end();
    if (validInviteCode) {
      assignedClients.insert({message.connection.id, inviteCode});
      gameSessions.at(inviteCode).addPlayer(message.connection);

      result << "Server> You have joined the gameSession " + inviteCode + "\n";
      std::cout << message.connection.id << " joined gameSession " << inviteCode << "\n";
    } else {
      std::cout << message.connection.id << " entered invalid code."<< "\n";
      result << "Server> You entered an invalid invite code.\n";
    }
  }

  outgoingMessages.push_back({message.connection, result.str()});
}

// from src/server/GameSession.h
class GameSession {
public:
  GameSession(const networking::Connection &host, std::string inviteCode);
  void addPlayer(const networking::Connection &player);
  std::vector<GameMessage> getUpdates();
  void receiveMessage(const networking::Connection &sender, std::string message);
  std::vector<networking::Connection> getPlayers();
  networking::Connection getHost();
  std::string getInviteCode();
private:
  networking::Connection host;
  std::string inviteCode;
  std::vector<networking::Connection> players;

  // Currently hardcoded to a RPS game
  GameObject* game;
};

// from src/server/GameObject.cpp
void addPlayer(const networking::Connection &newPlayer) {
    // If there are more than 2 players, don't do anything for now
    if (players.size() < 2) {
      players.push_back(newPlayer);

      // Send a message to all players and host that someone joined the game
      std::string message = std::to_string(newPlayer.id) + " has joined the game!";
      createMessage(host, message);
      for (auto& player : players) {
        createMessage(player, message);
      }

      // Once 2 players join, start the game
      if (players.size() == 2) {
        player1ID = std::to_string(players[0].id);
        player2ID = std::to_string(players[1].id);

        player1Connection = players[0];
        player2Connection = players[1];

        std::ostringstream roundMessage;
        roundMessage << "Welcome to Rock Paper Scissors!\n"
                     << "Round " + std::to_string(currentRound) + " of " + std::to_string(numRounds) + ".";
        createMessage(player1Connection, roundMessage.str());
        createMessage(player2Connection, roundMessage.str());
        createMessage(host, roundMessage.str());

        std::string optionMessage = "Please type \"rock\", \"paper\", or \"scissors\".";
        createMessage(player1Connection, optionMessage);
        createMessage(player2Connection, optionMessage);

        createMessage(host, "Waiting for players to respond...");

      }
    }
  }
