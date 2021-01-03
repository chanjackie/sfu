/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Server.h"
#include "ServerWindow.h"
#include "ServerStrings.h"
#include "Parser.h"
#include "Config.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <memory>


using networking::Server;
using networking::Connection;
using networking::Message;
using json_interpreter::Parser;


std::vector<Connection> clients;


void
onConnect(Connection c) {
  // std::cout << "New connection found: " << c.id << "\n";
  clients.push_back(c);
}


void
onDisconnect(Connection c) {
  // std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}


// TODO
std::string
processMessages(Server& server, const std::deque<Message>& incoming) {
  std::ostringstream result;
  for (auto& message : incoming) {
    if (message.text == "quit") {
      server.disconnect(message.connection);
    } else {
      result << message.connection.id << "> " << message.text << "\n";
    }
  }
  return result.str();
}


// TODO
std::deque<Message>
buildOutgoing(const std::string& log) {
  std::deque<Message> outgoing;
  for (auto client : clients) {
    outgoing.push_back({client, log});
  }
  return outgoing;
}


std::string
getHTTPMessage(const char* htmlLocation) {
  if (access(htmlLocation, R_OK ) != -1) {
    std::ifstream infile{htmlLocation};
    return std::string{std::istreambuf_iterator<char>(infile),
                       std::istreambuf_iterator<char>()};

  } else {
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
  }
}

bool
serverTick(Server &server) {
  bool errorWhileUpdating = false;
  try {
    server.update();
  } catch (std::exception& e) {
    std::cerr << "Exception from Server update:\n"
              << " " << e.what() << "\n\n";
    errorWhileUpdating = true;
  }

  auto incoming = server.receive();
  auto log = processMessages(server, incoming);
  auto outgoing = buildOutgoing(log);
  server.send(outgoing);
  return errorWhileUpdating;
}

// TODO: LOOK HERE - TOMMY
std::string
setUpConfigurationFromJSON(const json& gameJson, std::string specifiedConfigurationJsonKey) {

    for (auto& item : gameJson["configuration"].items()) {
      if (item.key() == specifiedConfigurationJsonKey && item.key() == "name") {
        // Game Name
        return item.value();
      } else if (item.key() == specifiedConfigurationJsonKey && item.key() == "audience") {
        // Audience Enabled
        if (item.value() == false) {
          return "false";
        } else {
          return "true";
        }
      }
    }
    
    return "Your specified key for the game's configuration was not found.\n";
}

/* 
 * Tommy's Reminder(s):
 * .is_object()
 * .is_array()
 * for (json::iterator itr = gameJson.begin(); itr != gameJson.end(); itr++) { std::cout << *itr << endl;}
*/

void
createGame(Server& server) {
  bool done = false;
  json gameJson;
  std::string gameMenuText = ServerStrings::GAME_MENU;

  auto onTextEntry = [&done, &server, &gameJson, &gameMenuText] (std::string input) {
    if ("q" == input) {
      done = true;
      return;
    }

    // Check if input ends with '.json'
    else if (!input.empty() && input.size() >= 5 &&
              input.compare(input.size() - 5, 5, ".json") == 0) {

      Parser parser(input.c_str());
      gameJson = parser.getGameJson();
      
      if (!gameJson.is_null()) {
        // TODO: LOOK HERE - TOMMY
        std::string gameName = setUpConfigurationFromJSON(gameJson, "name");
        std::string audienceEnabled = setUpConfigurationFromJSON(gameJson, "audience");
  
        gameMenuText.append(gameName + "\n");
        gameMenuText.append(audienceEnabled + "\n");

        // gameMenuText = "Valid JSON file found, dumping contents ('q' to exit): \n\n";
        // [ .dump(4) : prints ALL the contents of a given JSON file ]
        // [ The 4 represents tab spacing when printing the contents of a given JSON file]\
        //
        // gameMenuText.append(gameJson.dump(4));
        // gameMenuText.append("\n");
      }       
    }

    if (gameMenuText.compare(ServerStrings::GAME_MENU) == 0) {
      gameMenuText.append("\n Path is invalid, please enter a valid JSON file. \n");
    }
  };

  ServerWindow gameCreationWindow(onTextEntry);
  bool errorWhileUpdating = false;
  while (!done && !errorWhileUpdating) {
    errorWhileUpdating = serverTick(server);
    gameCreationWindow.clearText();
    gameCreationWindow.displayText(gameMenuText);
    gameCreationWindow.update();
    sleep(0.5);
  }
}

void
displayConnections(Server &server) {
  bool done = false;
  auto onTextEntry = [&done] (std::string input) {
    done = true;
  };
  ServerWindow connectionWindow(onTextEntry);
  bool errorWhileUpdating = false;
  while (!done && !errorWhileUpdating) {
    errorWhileUpdating = serverTick(server);
    connectionWindow.clearText();
    connectionWindow.displayText("Current Connections (Press 'ENTER' to return to the server menu):\n");
    for (Connection &c : clients) {
      std::ostringstream connectString;
      connectString << "Connection ID: " << c.id << "\n";
      connectionWindow.displayText(connectString.str());
    }
    connectionWindow.update();
    sleep(0.5);
  }
}


int
main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
    return 1;
  }

  unsigned short port = std::stoi(argv[1]);
  Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};

  bool done = false;
  bool onMainMenu = true;
  auto onTextEntry = [&done, &server, &onMainMenu] (std::string input) {
    if ("1" == input) {
      onMainMenu = false;
      createGame(server);
    } else if ("2" == input) {
      onMainMenu = false;
      displayConnections(server);
    } else if (std::count(ServerStrings::shutdownTexts.begin(), ServerStrings::shutdownTexts.end(), input)
      || "3" == input) {
      done = true;
    }
  };

  ServerWindow serverWindow(onTextEntry);
  serverWindow.clearText();
  serverWindow.displayText(ServerStrings::SERVER_MENU);

  while (true) {
    if (!onMainMenu) {
      serverWindow.clearText();
      serverWindow.displayText(ServerStrings::SERVER_MENU);
      onMainMenu = true;
    }
    bool errorWhileUpdating = serverTick(server);

    if (errorWhileUpdating || done) {
      break;
    }
    serverWindow.update();
  }
  return 0;
}

