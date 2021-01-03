// this was our least productive week so not a lot of code...sigh

// this is some code that'll tokenize the json rules

std::regex OPERATOR{"^(!|==)"};
std::regex SEPARATOR{"^[.()]"};
std::regex LIST_OPERATOR{"^(contains|collect|upfrom)"};
std::regex LIST_ATTRIBUTE{"^(size|elements)"};
std::regex IDENTIFIER{"^[a-zA-Z_]\\w*"};

std::vector<std::regex> expressions = {
  OPERATOR, SEPARATOR, LIST_OPERATOR, LIST_ATTRIBUTE, IDENTIFIER
};

std::optional<std::string>
getFirstMatch(std::string str) {
  std::smatch match;

  for (auto& expr : expressions) {
    if (std::regex_search(str, match, expr)) return match.str(0);
  }

  return std::nullopt;
}

std::vector<std::string>
Tokenizer::tokenize(std::string str) {
  std::vector<std::string> tokens;

  while (!str.empty()) {
    try {
      auto match = getFirstMatch(str);
      tokens.push_back(match.value());
      str = str.substr(match.value().length());
    } catch (const std::bad_optional_access &e) {
      throw InvalidExpressionError(str);
    }
  }

  return tokens;
}

// this is an object that'll be storing the load json spec into
// it'll be used to instantiate different games
#include <string>
#include <unordered_map>
#include <variant>

using UserPrompt = std::unordered_map<std::string, std::string>;
using SetupValue = std::variant<int, bool, std::string, UserPrompt>;

class GameConfig {
public:
  GameConfig(std::string name,
             int minPlayers,
             int maxPlayers,
             bool hasAudience,
             std::unordered_map<std::string, SetupValue> setup
  );

private:
  std::string name;
  int minPlayers;
  int maxPlayers;
  bool hasAudience;
  std::unordered_map<std::string, SetupValue> setup;
};

