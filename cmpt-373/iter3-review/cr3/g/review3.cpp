// Interpreter visits rules and performs behavior. 
void Interpreter::visit(InputTextRule& rule) {
  std::cout << "Visiting input text rule:\n";
  auto& messageQueue = states.getMessageQueue();

  Operation::sendMessage(messageQueue, rule.message);
  std::cout << "  Sending message: " << rule.message.getMessage() << std::endl;

  std::deque<Message>& incoming = Operation::getMessage(messageQueue);

  std::cout << "  Retrieving message" << std::endl;

  //TODO: test when message queue is implemented
  // std::list<std::string> playerlist = {"player1"};
  // incoming.push_back(Message{"test",playerlist});
  if (!incoming.empty()) {
      auto& input = incoming.front();
      const std::string inputMessage{input.getMessage()};
      std::cout << "  Input message: " << inputMessage << std::endl;
      
      auto& recipients = input.getRecipients();
      for (std::string p : recipients)
          std::cout << "  Input player: " << p << std::endl;
      
      auto currInput = GameValue{inputMessage};

      //TODO: change to work with single game state
      if (states.addPlayerVariable(rule.playerId, rule.key, currInput)) {
          std::cout << "  Setting player input with: " << inputMessage << std::endl;
      } else {
          std::cout << "  Error setting player input with: " << inputMessage << std::endl;
      }
  } else {
      std::cerr << "  Error retrieving messages" << std::endl;
  }
}

// List operations ===============================================

struct ListName {
  std::string val;
};

struct ElementCount {
  int val;
};

namespace ListOp {
// ExtendRule contains info needed to find the list to be extended e.g. the name of the
// list. This operation is what is called by the visitor to perform the behavior of 
// extending the list (e.g. gamevalue->perform(rule.extend)).

// This Extend operator handles not knowing whether the 'target' GameValue can be extended
// or not. We *also* need to handle acting differently based 'source' GameValue.
// Visitor invokes target->perform(Extend{toExtendWith}) - if the target can be 
// extended, operator()(std::vector<GameValue>& listToExtend) is called.
// Within this method, we then insert toExtendWith into the target based on whether
// the item is a single value or a list of values. 
struct Extend {
    Extend(GameValue& toExtendWith)
        : toExtendWith{toExtendWith} {}

    template <typename N>
    void operator()(N& notExtendable) {}
    
    void operator()(std::vector<GameValue>& listToExtend) {
        toExtendWith.perform(ExtendTarget{listToExtend});
    }

    GameValue& toExtendWith; 
};

struct ExtendTarget {
    ExtendTarget(std::vector<GameValue>& list)
        : list{list} {}

    template <typename N>
    void operator()(N& invalidExtension) {}

    void operator()(std::vector<GameValue>& otherList) {
        list.insert(list.end(), otherList.begin(), otherList.end());
    }

    void operator()(int num) {
        list.emplace_back(GameValue{num});
    }

    void operator()(std::string& str) {
        list.emplace_back(GameValue{str});
    }

    void operator()(bool truth) {
        list.emplace_back(GameValue{truth});
    }

    std::vector<GameValue>& list;
};

struct Reverse {
    template <typename N>
    void operator()(N& notReversable) {}

    void operator()(std::vector<GameValue>& listToReverse) {
        std::reverse(listToReverse.begin(), listToReverse.end());
    }
};

struct Shuffle {
    template <typename N>
    void operator()(N& notShufflable) {}

    void operator()(std::vector<GameValue>& listToShuffle) {
        std::random_shuffle(listToShuffle.begin(), listToShuffle.end());
    }
};

// Sorts the named list in ascending order. By default, only lists consisting entirely
// of numbers or strings can be sorted. If the named list contains maps, then a key to
// sort by is required.
struct Sort {
    Sort(ListName target, ValueKey sortKey = ValueKey{})
        : target{target}, sortKey{sortKey} {}

    template <typename N>
    void operator()(N& notSortable) {}

    void operator()(std::map<std::string, GameValue>& mapToSort) {
        // Handle sorting map by a key.
    }

    void operator()(std::vector<GameValue>& listToSort) {
        // Handle sorting a list.
    }

    ListName target;
    ValueKey sortKey;
};

// Moves 'toMove' elements from the (front/back?) of the list named 'source' to the
// list named 'target'.
struct Deal {
    Deal(GameValue& targetList, ElementCount toMove)
        : targetList{targetList}, toMove{toMove} {}

    template <typename N>
    void operator()(N& notDealable) {}

    void operator()(std::vector<GameValue>& sourceList) {
        if (sourceList.size() < toMove.val) {
            // throw
        }
        // ...
    }

    GameValue& targetList;
    ElementCount toMove;
};

// Removes 'toDiscard' elements from the (front/back?) of the list named 'target'.
struct Discard {
    Discard(ElementCount toDiscard)
        : toDiscard{toDiscard} {}

    template <typename N>
    void operator()(N& notDiscardable) {}

    void operator()(std::vector<GameValue>& targetList) {
        if (targetList.size() < toDiscard.val) {
            // throw
        }
        // ...
    }

    ElementCount toDiscard;
};

// Sets property 'size' to the number of elements in the given GameValue,
// if it's a list.
struct GetSize {
    GetSize(GameValue& valueToSize)
        : valueToSize{valueToSize} {}

    template <typename N>
    void operator()(N& notSizeable) {}

    void operator()(std::vector<GameValue>& list) {
        size.val = list.size();
    }

    GameValue& valueToSize;
    ElementCount size;
};

// Sets 'doesContain' to whether a given GameValue is present in a list.
struct Contains {
    Contains(GameValue& toFind) 
        : toFind{toFind} {}

    template <typename N>
    void operator()(N& notQueryable) {}

    void operator()(std::vector<GameValue>& list) {
        auto found = std::find(list.begin(), list.end(), toFind);
        doesContain = found == list.end();
    }

    GameValue& toFind;
    bool doesContain;
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
    void operator()(N& notListOfMaps) {}

    // TODO: How to match a list of maps vs. a list of other values?
    void operator()(std::vector<GameValue>& listOfMaps) {
        // Needs to match list of maps - find_if_not type of map?

        std::transform(listOfMaps.begin(), listOfMaps.end(), std::back_inserter(result),
            [this](const GameValue& val) {
            // How to extract map from value? Or push behavior into variant.
            // Many problems with this:
            //  - Method is coupled to & knows the exact type of the map 
            //  - Throws if variant does not contain map type
            auto valMap = val.get<std::map<std::string, GameValue>>();
            return valMap[elementKey.val];
        });
    }

    ValueKey elementKey;
    std::vector<GameValue> result;
};


struct Comparator {
    GameValue first;
    ComparisonKind comp;
    GameValue second;
};

// Sets 'collected' to a newly-created list based elements that evaluates to true
// with the comparator.
//   - list.elements.collect(elementName?, predicate)
//   - e.g. "players.elements.collect(player, player.weapon == weapon.beats)"
struct Collect {
    Collect(Comparator comp) 
        : comp{comp} {}

    template <typename N>
    void operator()(N& notCollectable) {}

    void operator()(std::vector<GameValue>& list) {
        // std::copy_if
    }

    Comparator comp;
    std::vector<GameValue> collected;
};

};
