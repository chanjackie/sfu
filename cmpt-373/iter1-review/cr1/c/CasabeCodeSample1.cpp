/*
    Logic Nodes/Rules - fragments of how our rules are structured.
    Each node represents a rule. This segment also shows how we 
    are currently faking the parallelism.
*/

// LogicNode.hpp

class LogicNode {

public:

    LogicNode(/* args */);

    // Prepare next rule to execute
    bool Step();

    // Run the next rule, gameInstance used for fetching variables
    virtual bool Execute(Game* gameInstance) = 0;

    // Print the execution in pseudocode
    virtual void Print(int depth) = 0;

    //Getters and Setters for rules
    std::vector<LogicNode*>* GetRules(){
        return &(this->rules);
    }
    void SetRules(std::vector<LogicNode*> rl){
        this->rules = rl;
        // May need to loop through vector here to assign properly
    }

        //Getters and Setters for type
    std::string GetType(){
        return this->type;
    }
    void SetType(std::string tp){
        this->type = tp;
    }

    // Getters and Setters for index
    int GetIndex(){
        return this->index;
    }
    void SetIndex(int idx){
        this->index = idx;
    }

private:

    // Rules to execute
    std::vector<LogicNode*> rules;

    // Name of 
    std::string type;

    // Location of rule to execute
    int index;

};


class WhileNode : public LogicNode {

public:
    WhileNode();
    bool Execute(Game* gameInstance);
    void Print(int depth);

    // Getters and Setters for condition
    std::string GetCondition(){
        return this->condition;
    }
    void SetCondition(std::string cond){
        this->condition = cond;
    }    

private:
    std::string condition;

};

// LogicNode.cpp


// Move to next rule
bool LogicNode::Step() {

    // Prepare index for next rule
    //index += 1;
    SetIndex(GetIndex() + 1);

    // When end of rules reached prepare index to execute current node 
    //      and signal that end of list reached.
    if (GetIndex() == GetRules()->size()){
        //index = -1;
        SetIndex(-1);
        return true;
    }

    return false;

}

// Default Execute
bool LogicNode::Execute(Game* game_instance) {

    printf("Logic Node %s has no execution plan\n", GetType().c_str());
    return true;

}

// Print tne execution in pseudocode
void LogicNode::Print(int depth) {

    std::string tabs;
    tabs.insert(0, depth, '\t');

    printf("%s Logic Node %s has no print statement\n", tabs.c_str(), GetType().c_str());

    return;

}

WhileNode::WhileNode(){

}


bool WhileNode::Execute(Game* game_instance){
    // To Implement
    return false;
}

void WhileNode::Print(int depth) {

    std::string tabs;
    bool block_end = false;

    tabs.insert(0, depth, '\t');

    printf("%swhile( %s ) {\n", tabs.c_str(), GetCondition().c_str());


    block_end = Step();
    while(!block_end) {
        GetRules()->at(GetIndex())->Print(depth + 1);
        block_end = Step();
    }

    printf("%s}\n", tabs.c_str());

    return;

}

// Sample of how the rules will be executed in the game object.

#include "Game.hpp"
#include "LogicNode.hpp"

int main(){

    Casabe::Game* game = new Casabe::Game;
    game->rulesIndex = -1;

    Casabe::WhileNode* first_while = new Casabe::WhileNode;
    first_while->SetCondition("outer < 5");

    Casabe::WhileNode* second_while = new Casabe::WhileNode;
    second_while->SetCondition("inner < 5");

    Casabe::AddNode* first_add = new Casabe::AddNode;
    first_add->SetAddTo("inner");
    first_add->SetValue(-5);

    Casabe::AddNode* second_add = new Casabe::AddNode;
    second_add->SetAddTo("inner");
    second_add->SetValue(1);

    Casabe::AddNode* third_add = new Casabe::AddNode;
    third_add->SetAddTo("outer");
    third_add->SetValue(1);

    game->rulesList.push_back(first_while);

    first_while->GetRules()->push_back(first_add);
    first_while->GetRules()->push_back(second_while);
    first_while->GetRules()->push_back(third_add);

    second_while->GetRules()->push_back(second_add);
    
    game->Print();

    return 0;
}


/*
    Game Object - this is how we are currently executing/printing our 
    rules within the game object (uses logic nodes)
*/

// Game.cpp

// Change this ... eventually
// Get it running
bool Game::Execute() {

    if ( rulesIndex == -1) {
        printf("---- Game Start ----\n");

        if ( Step() ) {
            return true;
        }

    }

    while( rulesList.at(rulesIndex)->Execute(this) ) {

        if ( Step() ) {
            printf("---- Game End ----\n");
            return true;
        }

    }

    return false;
}

void Game::Print(){
    while( !Step() ){
        rulesList.at(rulesIndex)->Print(0);
    }
}

// Get variable value
std::string Game::GetVariableValue(std::string variableName){
    std::map<std::string,std::string>::iterator it;

    it = variableMap.find(variableName);

    if(it != variableMap.end()){
        return it->second;
    }

    
}


/*
    Fragments showing our wrapper for the given network library so
    that we can have our own Server API to work with.
*/

// CasabeServer.hpp

using networking::Server;
using networking::Connection;
using networking::Message;

struct MessageResult {
  std::string result;
  bool shouldShutdown;
};

void onConnect(Connection c);
void onDisconnect(Connection c);
std::string getHTTPMessage(const char* htmlLocation);

// std::vector<Connection> clients;

class CasabeServer {
public:
    // CasabeServer(unsigned short port, Server &server): server(server), port(port) {}
    CasabeServer();
    CasabeServer(unsigned short port, const char* htmlLocation) : server(port, getHTTPMessage(htmlLocation), onConnect, onDisconnect) {}

    void start();

    // static void onConnect(Connection c);
    // static void onDisconnect(Connection c);

    MessageResult processMessages(const std::deque<Message>& incoming);
    std::deque<Message> buildOutgoing(const std::string& log);
    // std::string getHTTPMessage(const char* htmlLocation);

    // static std::vector<Connection> clients;
private:
    Server server;
    unsigned short port;
    // std::vector<Session> sessionList;
};


// CasabeServer.cpp


#include "CasabeServer.hpp"

using networking::Server;
using networking::Connection;
using networking::Message;

std::vector<Connection> clients;


// Include in CasabeServer class???
std::string getHTTPMessage(const char* htmlLocation) {
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

void onConnect(Connection c) {
  std::cout << "New connection found: " << c.id << "\n";
  clients.push_back(c);
}


void onDisconnect(Connection c) {
  std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}

void CasabeServer::start() {
  while (true) {
    bool errorWhileUpdating = false;
    try {
      server.update();
    } catch (std::exception& e) {
      std::cerr << "Exception from Server update:\n"
                << " " << e.what() << "\n\n";
      errorWhileUpdating = true;
    }

    auto incoming = server.receive();
    auto [log, shouldQuit] = processMessages(incoming);
    auto outgoing = buildOutgoing(log);
    server.send(outgoing);

    if (shouldQuit || errorWhileUpdating) {
      break;
    }

    sleep(1);

  }
}


MessageResult CasabeServer::processMessages(const std::deque<Message>& incoming) {
  std::ostringstream result;
  bool quit = false;
  for (auto& message : incoming) {
    if (message.text == "quit") {
      server.disconnect(message.connection);
    } else if (message.text == "shutdown") {
      std::cout << "Shutting down.\n";
      quit = true;
    } else {
      result << message.connection.id << "> " << message.text << "\n";
    }
  }
  return MessageResult{result.str(), quit};
}


std::deque<Message> CasabeServer::buildOutgoing(const std::string& log) {
  std::deque<Message> outgoing;
  for (auto client : clients) {
    outgoing.push_back({client, log});
  }
  return outgoing;
}


// This is how we are going to call our Server API.


int main(int argc, char* argv[]) {
  // on start
  // the server application will initialise any needed objects (NetworkManager, .. , etc)
  // (optional/eventualy) load in all (json,etc.) files from a folder and put them in a vector 
  // (optional/eventualy) parse each (json,etc.) files into some object (game object etc.) using casabe engine API Iguess
  // start an infinate loop to continuously recieve requests from host and client

  if (argc < 3) {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
    return 1;
  }

  unsigned short port = 4000;

  CasabeServer casabServ{port, argv[2]};

  casabServ.start();

  return 0;
}






