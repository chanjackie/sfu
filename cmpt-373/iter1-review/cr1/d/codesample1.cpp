// ------------------------------------------------------------
// chatserver.cpp line 111 (host-game-options branch)
// ------------------------------------------------------------
void setUpConfigurationFromJSON(const json& gameJson, Config* gameConfiguration) {
	for (auto& item : gameJson["configuration"].items()) {
		if (item.key() == "name") {
        // Game Name
        gameConfiguration->setGameName(item.value());
		} else if (item.key() == "audience") {
        // Audience Enabled
        if (item.value() == false) {
          // False
          gameConfiguration->setAudienceEnabled(false);
        } else {
          // True
          gameConfiguration->setAudienceEnabled(true);
        }
		} else if (item.key() == "player count") {
        // Player Min & Max Counts
        for (auto& item_player_count : gameJson["configuration"]["player count"].items()) {
			if (item_player_count.key() == "min") {
				// Min
				gameConfiguration->setMinPlayers(item_player_count.value());
			} else {
            // Max
            gameConfiguration->setMaxPlayers(item_player_count.value());
			}	
        }
		} else if (item.key() == "setup") {
			// Setup
			for (auto & item_set_up : gameJson["configuration"]["setup"].items()) {
				if (item_set_up.key() == "Rounds") {
				// Rounds
				gameConfiguration->setNumRounds(item_set_up.value());
				}
			}
		}
    }
}

// ------------------------------------------------------------
// ConfigTests.cpp (unit-test branch)
// ------------------------------------------------------------

class ConfigTests : public ::testing::Test {
    protected:
	Config* gameConfiguration;
	const std::string DEFAULT_NAME = "unconfigured_game";
	const int DEFAULT_PLAYERS = -1;
	const int DEFAULT_ROUNDS = -1;

	void InitializeConfigWithParams(std::string gameName, int minPlayer, int maxPlayer, bool audienceEnabled, int numOfRounds) {
		InitializeConfig();
		gameConfiguration->setGameName(gameName);
		gameConfiguration->setMinPlayers(minPlayer);
		gameConfiguration->setMaxPlayers(maxPlayer);
		gameConfiguration->setAudienceEnabled(audienceEnabled);
		gameConfiguration->setNumRounds(numOfRounds);
		ASSERT_TRUE(gameConfiguration);
	}

}

TEST_F(ConfigTests, TestSettersConfig) {
    std::string gameName = "UnitTestConfig";
    int minPlayer = 2;
    int maxPlayer = 4;
    int numRounds = 5;
    InitializeConfigWithParams(gameName, minPlayer, maxPlayer, true, numRounds);

    ASSERT_EQ(gameConfiguration->getGameName(), gameName);
    ASSERT_EQ(gameConfiguration->getMinPlayers(), minPlayer);
    ASSERT_EQ(gameConfiguration->getMaxPlayers(), maxPlayer);
    ASSERT_EQ(gameConfiguration->getAudienceEnabled(), true);
    ASSERT_EQ(gameConfiguration->getNumRounds(), numRounds);

    // Check whether the config is complete
    ASSERT_NE(gameConfiguration->isConfigComplete(), false);
}

// ------------------------------------------------------------
// chatserver.cpp line 111 (host-game-options branch)
// ------------------------------------------------------------
// related to Rule Struct
void
setupOrderedRules(json& gameJson, std::vector<Rule>& orderedRules) {
    for (auto& item : gameJson) {
      Rule rule;

      if (item.contains("rule")) {
        rule.name = item["rule"];
      }

      if (item.contains("list")) {
        rule.list = item["list"];
      }

      if (item.contains("element")) {
        rule.element = item["element"];
      }

      if (item.contains("value")) {
        rule.value = item["value"];
      }

      if (item.contains("from")) {
        rule.from = item["from"];
      }

      if (item.contains("count")) {
        rule.count = item["count"];
      }

      if (item.contains("target")) {
        rule.target = item["target"];
      }

      if (item.contains("to")) {
        rule.to = item["to"];
      }

      if (item.contains("score")) {
        rule.score = item["score"];
      }

      if (item.contains("ascending")) {
        if (item["ascending"] == true) {
          rule.ascending = "true";
        } else {
          rule.ascending = "false";
        }
      }

      if (item.contains("rules")) {
        setupOrderedRules(item["rules"], rule.rules);
      }

      orderedRules.push_back(rule);
    }
}


// ------------------------------------------------------------
// chatserver.cpp line 156 (master)
// ------------------------------------------------------------
// createGame function, responsible for providing user interface prompting the host for the path to the JSON configuration.
// Simply dumps JSON contents in first iteration.
void
createGame(Server& server) {
	bool done = false;
	json gameJson;
	std::string gameMenuText = ServerStrings::GAME_MENU;
	// onTextEntry function passed into ChatWindow to handle user input
	auto onTextEntry = [&done, &gameJson, &gameMenuText] (std::string input) {
		if ("q" == input) {
		  done = true;
		  return;
		}
		// Check if input ends with '.json'
		else if (!input.empty() && input.size() >= 5 && input.compare(input.size() - 5, 5, ".json") == 0) {
		  /*
		   * Json configuration parsing and game object creation handled here
		   * This part is omitted for code review because it is too long
		   */
		}
		if (gameMenuText.compare(ServerStrings::GAME_MENU) == 0) {
		  gameMenuText.append("\n Path is invalid, please enter a valid JSON file. \n");
		}
	};
	ChatWindow gameCreationWindow(onTextEntry);
	bool errorWhileUpdating = false;
	// Continue updating server while interface is being displayed
	while (!done && !errorWhileUpdating) {
		errorWhileUpdating = serverTick(server);
		gameCreationWindow.clearText();
		gameCreationWindow.displayText(gameMenuText);
		gameCreationWindow.update();
		sleep(0.5);
	}
}

// ------------------------------------------------------------
//  listRules.cpp (data-structures)
// ------------------------------------------------------------

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
// ------------------------------------------------------------
//  GlobalMessageRule.h (master)
// ------------------------------------------------------------

// Reviewing multiple rules as an object that inherits from Rules.h
// Using this pattern will require all the rules to be the child class from Rules.h
// By doing this, we can control the rules better with different derived classes and its functions.
#include "Rules.h"
class GlobalMessageRule : public Rules {
    public:
        GlobalMessageRule();
        GlobalMessageRule(std::string message);
        ~GlobalMessageRule();

        //Getters
        Rules::RulesName getRuleName();
        std::string getMessageValue();

        //Setters
        void setMessage(std::string message);
    private:
        std::string message;
};