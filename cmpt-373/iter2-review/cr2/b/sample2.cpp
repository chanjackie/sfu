// this reads in the game rule json file
#include "JsonParser.h"

using JsonParser::JasonParserObject;

JasonParserObject::JasonParserObject(string fileName) : fileName{ fileName } {
    ifstream i(fileName);
    i >> j;
}

void
JasonParserObject::getRulesInSpecificationStructure() {
    cout << "gameSpecificationStructure" << endl;
    vector<string> keyVector = { "size", "name", "configuration", "constants",
    "variables", "per-player", "per-audience", "rules" };

    for (vector<string>::iterator it = keyVector.begin(); it != keyVector.end(); ++it) {
        if (j.contains(*it)) {
            cout << *it << " !! " << j[*it] << endl;
        }
    }
}

json
JasonParserObject::getJsonRules() {
    return j["rules"];
}

void
JasonParserObject::findRulesRecurvise(json initJSON) {
    cout << "findRulesRecurvise" << endl;

    for (json::iterator it = initJSON.begin(); it != initJSON.end(); ++it) {
        //cout << "it" << *it << endl;
        if (it->contains("rule")) {
            cout << " Rules1. " << it.value()["rule"] << endl;
        }

        if (it->contains("rules")) {
            findRulesRecurvise(it.value()["rules"]);
        }

        if (it->contains("cases")) {
            findRulesRecurvise(it.value()["cases"]);
        }

    }
}

// this code configures the server. in a future update it will also load the directory of the game files
#include "serverConfig.h"

using nlohmann::json;

serverConfig::serverConfig(std::string _filePath){
            std::ifstream input(_filePath);
            json config;
            input >> config;

            port = config.at("port").get<unsigned short>();
            client_path = config.at("client_path").get<std::string_view>();
}

const unsigned short serverConfig::getPort(){ return port; }

const std::string serverConfig::getClient_path() { return client_path; }

