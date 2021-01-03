// Class to represent game state

using PlayerMap = std::map<PlayerId, GameValue>; 

class GameState {
public:
    GameState() = default;
    GameState(PlayerMap players, GameValue constants, GameValue variables, MessageQueue messageQueue);

    // Caller is responsible for ensuring that ValueKeys passed to getters & setters
    // refer to keys that exist within the game state.
    const GameValue* getConstant(ValueKey key);
    
    std::vector<PlayerId> getPlayerIds() const;
    const GameValue& getPlayerVal(PlayerId id, ValueKey key);
    void addPlayerVariable(PlayerId player, ValueKey key, GameValue& val);
    void updatePlayerVariable(PlayerId id, ValueKey key, const GameValue& val);

    const GameValue& getVariable(ValueKey key) ;
    void addVariable(ValueKey key, GameValue& val);
    void updateVariable(ValueKey key, const GameValue& val);

    MessageQueue& getMessageQueue();

private:
    PlayerMap players; 
    GameValue constants;
    GameValue variables;
    MessageQueue messageQueue;
};

// Implementation

GameState::GameState(
    PlayerMap players, 
    GameValue constants, 
    GameValue variables, 
    MessageQueue messageQueue)
    : players{players}, 
        constants{constants}, 
        variables{variables}, 
        messageQueue{messageQueue} {}

struct Finder {
    Finder(ValueKey& toFind, GameValue& map) 
        : toFind{toFind}, map{map}, val{nullptr} {}

    template <typename N>
    void operator()(const N& notMap) {}

    void operator()(GameMapPtr& map) {
        auto find = map->find(toFind);
        val = &(find->second);
    }

    ValueKey& toFind;
    GameValue& map;
    GameValue* val;
};

struct Adder {
    Adder(ValueKey& key, GameValue& toAdd)
        : key{key}, toAdd{toAdd} {}

    template <typename N>
    void operator()(const N& notMap) {}

    void operator()(GameMapPtr& map) {
        map->emplace(key, std::move(toAdd));
    }

    ValueKey& key;
    GameValue& toAdd;
};

GameValue* findInMap(ValueKey& toFind, GameValue& map) {
    Finder finder{toFind, map};

    map.perform(finder);
    GameValue* val = finder.val;

    if (val == nullptr) {
        throw std::invalid_argument("Cannot find key: " + toFind.val + "in map.\n");
    }
    return val;
}

void addToMap(ValueKey& key, GameValue& toAdd, GameValue& map) {
    findInMap(key, map); // Ensure that key does not already exist.
    Adder adder{key, toAdd};
    
    map.perform(adder);
}


void updateInMap(ValueKey& toUpdate, GameValue& replacement, GameValue& map) {
    auto valRef = findInMap(toUpdate, map); 
    *valRef = replacement; // TODO: Implement operator= correctly. 
}

const GameValue* GameState::getConstant(ValueKey key) {
    return findInMap(key, constants);
}

std::vector<PlayerId> GameState::getPlayerIds() const {
    std::vector<PlayerId> ids;
    for (auto& [id, _] : players) {
        ids.push_back(id);
    }
    return ids;
}

const GameValue& GameState::getPlayerVal(PlayerId id, ValueKey key) {
    auto& map = players.find(id)->second; // Caller responsible for ensuring player id exists.
    return findInMap(key, map);
}

void GameState::addPlayerVariable(PlayerId id, ValueKey key, GameValue& val) {
    auto map = players.find(id)->second;
    addToMap(key, val, map);
}

void GameState::updatePlayerVariable(PlayerId id, ValueKey key, const GameValue& val) {
    // TODO: See issues in GameValue::updateInMap().
}

const GameValue& GameState::getVariable(ValueKey key) {
    return findInMap(key, variables);
}

void GameState::addVariable(ValueKey key, GameValue& val) {
    addToMap(key, val, variables);
}

void GameState::updateVariable(ValueKey key, const GameValue& val) {
    // TODO: See issues in GameValue::updateInMap().
}

MessageQueue& GameState::getMessageQueue() {
    return messageQueue;
}

// Structs to represent list operations

// Used for double visiting
struct GetValue {
        GetValue(ValueKey key) 
            : key{key} {}

        template <typename N>
        void operator()(const N& notMap) {}

        void operator()(GameMapPtr& map) {
            result = &(map->at(key));
        }

        GameListPtr* listOfMaps;
        ValueKey key;
        GameValue* result;
    };

    // Sets 'result' to a newly-created list based on the given element key.
    // JSON specification:
    // list.elements.key -> creates a new list consisting of values with key 'key' from 'list',
    // which is a list of maps. 
    //   - players.elements.weapon -> ["Rock", "Rock", "Scissors", ...]
    //   - players.elements.name -> ["Joe", "Jane", "Don", ...]
    struct GetElements {
        GetElements(ValueKey elementKey) 
            : elementKey{elementKey} {}

        template <typename N>
        void operator()(const N& notListOfMaps) {}

        void operator()(GameListPtr& listOfMaps) {
            // TODO: Ensure that this is actually a list of maps. For now assume it is.

            for (auto& map : *listOfMaps) {
                // Visit each GameValue in listOfMaps and attempt to extract the value 
                // associated with elementKey, if the GameValue is a map. 
                GetValue getVal{elementKey};
                map.perform(getVal);
                // TODO: This is creating a new game value from an existing one, and I think
                // there is an error around this. 
                result.emplace_back(getVal.result); // Check: append value, not ptr! 
            }
        }

        ValueKey elementKey;
        GameList result;
    };