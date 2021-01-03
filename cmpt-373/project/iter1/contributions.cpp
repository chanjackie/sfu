/*
 * Parser class
 */

// Parser.h
#ifndef PARSER_H 
#define PARSER_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace json_interpreter {
/**
 *  @class Interpreter
 *
 *  @brief A class for interpreting JSON data for a game.
 *
 *  The Interpreter class that takes a JSON file and creates a Game.
 */
class Parser {
    public:
    	/**
    	 *	Construct a Parser with a file path to a JSON file as argument
    	 */
    	Parser(const char* filePath);

    	/**
    	 *	Default destructor
    	 */
    	~Parser();

    	// Getters
    	json getGameJson();
    private:
    	json gameJson;


};

}
#endif

// Parser.cpp

#include "Parser.h"
#include <iostream>
#include <fstream>
// #include <nlohmann/json.hpp>

using json_interpreter::Parser;
// using json = nlohmann::json

// Initialize game JSON from file path.
Parser::Parser(const char* filePath) {
    std::ifstream jsonStream;
    jsonStream.open(filePath);
    if (jsonStream.is_open() && !jsonStream.fail()) {
        jsonStream >> gameJson;
    }
}

Parser::~Parser() {}

json Parser::getGameJson() {
    return gameJson;
}


/*
 * chatserver.cpp contributions
 */

// createGame function, responsible for providing user interface prompting the host for the path to the JSON configuration.
// Simply dumps JSON contents in first iteration.
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
    else if (!input.empty() && input.size() >= 5
      && input.compare(input.size() - 5, 5, ".json") == 0) {
      Parser parser(input.c_str());
      gameJson = parser.getGameJson();
      if (!gameJson.is_null()) {
        gameMenuText = "Valid JSON file found, dumping contents ('q' to exit): \n\n";
        gameMenuText.append(gameJson.dump());
        gameMenuText.append("\n");
        return;
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

// displayConnections function is responsible for giving the host a 
// real-time list of currently connected clients.
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

// Implemented a server interface for chatserver.cpp in main, and refactored 
// server updates to a separate serverTick() function.
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

/*
 * CMakeLists.txt in web-socket-networking-master/lib/json-interpreter to 
 * incorprate nlohmann JSON library (later improved on by stn5)
 */

find_package(nlohmann_json 3.7.3 REQUIRED)

add_library(json_interpreter
    src/Parser.cpp
#   src/addRule.cpp
#   src/Config.cpp
#   src/Game.cpp
#   src/perPlayer.cpp
#   src/questionAnswer.cpp
)

target_include_directories(json_interpreter
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(json_interpreter
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

install(TARGETS json_interpreter
    ARCHIVE DESTINATION lib
)

target_link_libraries(json_interpreter PRIVATE nlohmann_json::nlohmann_json)

/*
 * Other contributions:
 * - Reorganized project structure to follow sample web-socket-networking-master repository
 * - Lightly modified other CMakeLists.txt to allow project to build properly
 * - Wrote additional instructions in README.md to build this project, as well as to provide a JSON configuration to the server interface.
 */