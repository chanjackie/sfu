/* --------------------------- GameConfigBuilderJSON.h ----------------------------- */
#pragma once

#include "GameConfig.h"
#include "GameConfigBuilder.h"
#include "Rule.h"

// required in the template function below
#include "fmt/format.h"

// Class to handle parsing the JSON format of a game config
class GameConfigBuilderJSON {
// note: the implementation is split across two files because it's fairly large
// the rules are implemented in GameConfigBuilderJSON_Rules.cpp
// the rest is implemented in GameConfigBuilderJSON.cpp
public:
    using parse_error = GameConfigBuilder::parse_error;

    // config parsing functions
    GameConfig parse(const nlohmann::json &json);
    void parse(const nlohmann::json &json, GameConfig &gc);

    // rule parsing functions, because they're useful
    Rule parseRule(const nlohmann::json &json);
    RuleList parseRules(const nlohmann::json &json);

private:
    // helper parsers
    // actually these could be moved out of the JSON parser because they could be reused in other formats, todo
    Expression parseExpression(const std::string &str);
    VariableName parseVariableName(const std::string &str);
    Attribute parseAttribute(const std::string &str);
    Rules::MessageText parseMessage(const std::string &str);

    template <typename T>
    T checkNonnegative(T number) {
        if (number < 0) {
            throw parse_error(fmt::format("negative number given (value: {})", number));
        }
        return number;
    }

    // helper functions that interact with JSON
    Rules::ListOrExpression parseListOrExpression(const nlohmann::json &j);
    int parseInt(const nlohmann::json &j);
    double parseDouble(const nlohmann::json &j);
    Value parseValue(const nlohmann::json &j);
    GameConfig::Prompt parsePrompt(const nlohmann::json &j);

    // parse a timer duration (=> currently means nonnegative double)
    double parseDuration(const nlohmann::json &j);

    // specialized rule parsing functions
    Rule parseLoop(const nlohmann::json &j);
    Rule parseTimer(const nlohmann::json &j);
    Rule parseInputChoice(const nlohmann::json &j);
    // ... cut: a whole bunch more
};

/* --------------------------- GameConfigBuilderJSON.cpp ----------------------------- */

Expression GameConfigBuilderJSON::parseExpression(const std::string &str) {
    // todo: expression parsing not implemented
    if (str.empty()) {
		throw parse_error("empty string given as expression");
	}
	return Expression{str};
}

VariableName GameConfigBuilderJSON::parseVariableName(const std::string &str) {
    // todo: expression parsing not implemented
	if (str.empty()) {
		throw parse_error("empty string given as variable name");
	}
    return VariableName{str};
}

double GameConfigBuilderJSON::parseDouble(const nlohmann::json &j) {
	if (j.is_number()) {
		return j;
	} else {
		throw parse_error(fmt::format("expected number but got json of type {} ({})", j.type_name(), j));
	}
}

double GameConfigBuilderJSON::parseDuration(const nlohmann::json &j) {
    return checkNonnegative(parseDouble(j));
}

/* --------------------------- GameConfigBuilderJSON_Rules.cpp ----------------------------- */

Rule GameConfigBuilderJSON::parseTimer(const nlohmann::json &js) {
    using Mode = Rules::Timer::Mode;
    auto parseMode = [&](const nlohmann::json &j) {
        static std::map<std::string, Mode> lookup = {
            {"exact", Mode::EXACT},
            {"at most", Mode::ATMOST},
            {"track", Mode::TRACK},
        };
        std::string mode = j;
        auto it = lookup.find(mode);
        if (it == lookup.end()) {
            throw parse_error(fmt::format("unsupported timer mode: {}", mode));
        }
        return it->second;
    };

    Mode mode = parseMode(js.at("mode"));
    std::optional<VariableName> flag;
    if (mode == Mode::TRACK) {
        flag = parseVariableName(js.at("flag"));
    } else {
        flag = std::nullopt;
    }
    return Rule{Rules::Timer{
        parseDuration(js.at("duration")),
        mode,
        parseRules(js.at("rules")),
        flag
    }};
}

Rule GameConfigBuilderJSON::parseInputChoice(const nlohmann::json &js) {
    auto parseOptionalTimeout = [&](const std::string &key) -> std::optional<double> {
        if (js.contains(key)) {
            return parseDuration(js.at(key));
        } else {
            return std::nullopt;
        }
    };
    return Rule{Rules::InputChoice{
        parseVariableName(js.at("to")),
        parseMessage(js.at("prompt")),
        parseListOrExpression(js.at("choices")),
        parseVariableName(js.at("result")),
        parseOptionalTimeout("timeout")
    }};
}

Rule GameConfigBuilderJSON::parseLoop(const nlohmann::json &js) {
    using Mode = Rules::Loop::Mode;
    auto [mode,condition] = [this]() -> std::pair<Mode,Expression> {
        if (js.contains("until")) {
            return {Mode::UNTIL, parseExpression(js.at("until"))};
        } else if (js.contains("while")) {
            return {Mode::WHILE, parseExpression(js.at("while"))};
        } else {
            throw GameConfigBuilder::parse_error("loop rule has no until/while param");
        }
    }();
    return Rule{Rules::Loop{condition, mode, parseRules(js.at("rules"))}};
}

/* --------------------------- Token.h ------------------------------------------------------ */
class Token {
public:
	enum Type {
		equals,
		identifier,
		dot,
		integer,
		error
	};

	Token(Type type)
		: type{ type }
	{}

	virtual ~Token() = default;

	Type getType() const {
		return type;
	}

	friend std::ostream& operator<<(std::ostream& os, const Token& token) {
		return token.toString(os);
	}
protected:
	Type type;
private:
	virtual std::ostream& toString(std::ostream& os) const = 0;
};

/* --------------------------- Tokenizer.cpp ------------------------------------------------------ */
std::vector<std::unique_ptr<Token>> Tokenizer::tokenize(std::string text) {
	std::vector<std::unique_ptr<Token>> tokens;
	/*
		Remove whitespace from string
		From: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
		Answer by: Matt Price
	*/
	text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
	TextStream textStream{ text };

	while (textStream.hasNext()) {
		tokens.push_back(std::move(findNextToken(textStream)));
	}

	return tokens;
}

std::unique_ptr<Token> Tokenizer::findNextToken(TextStream& textStream) {
	std::string tokenText;
	tokenText.reserve(textStream.text.length());
	std::string test;

	auto startIndex = textStream.position;
	auto numOfCharsToAdd = 1;
	char firstChar = textStream.next();
	if (isNumberStart(firstChar)) {
		while (std::isdigit(textStream.next())) {
			numOfCharsToAdd++;
		}
		textStream.pushBack();
		tokenText.append(textStream.text, startIndex, numOfCharsToAdd);

		return IntegerToken::makeIntegerToken(tokenText);
	} else if (isIdentifierStart(firstChar)) {
		while (std::isalpha(textStream.next())) {
			numOfCharsToAdd++;
		}
		textStream.pushBack();
		tokenText.append(textStream.text, startIndex, numOfCharsToAdd);

		return IdentifierToken::makeIdentifierToken(tokenText);
	} else if (isPunctuatorStart(firstChar)) {
		auto secondChar = textStream.peek();
		if (firstChar == '=' && secondChar == '=') {
			textStream.next();
			tokenText.append(textStream.text, startIndex, 2);

			return OperatorToken::makeOperatorToken(tokenText, Token::Type::equals);
		} else if (firstChar == '.') {
			tokenText.append(textStream.text, startIndex, 1);
			return OperatorToken::makeOperatorToken(tokenText, Token::Type::dot);
		}
	}

	return ErrorToken::makeErrorToken("Unimplemented character");
}

bool Tokenizer::isNumberStart(char c) {
	return std::isdigit(c);
}

bool Tokenizer::isIdentifierStart(char c) {
	return std::isalpha(c);
}

bool Tokenizer::isPunctuatorStart(char c) {
	return std::ispunct(c);
}