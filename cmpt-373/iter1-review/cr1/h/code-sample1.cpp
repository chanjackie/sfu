//////////////////////////////////SERVER SIDE CODE//////////////////////////////////////

// takes the the messages from processMessages()
// and creates a deque of output Messages assigned to the appropriate room members
// returns deque of messages in the form of
//                              Connection: Recipient ID  	(where recipient = a user who's in the same room as the sender)
//                              Text: USER_ID> MESSAGE_TEXT
std::deque<Message>
postOffice(const std::deque<Message>& processedMessages){
   std::deque<Message> output;
   for (auto& message : processedMessages) {
        auto sendersRoom = getRoomById(message.sendersRoomId);

        // check if message.whisperId exists
        // if true, push_back one message object to the whisperId
        // else, send message to all rooms members as normal

        if (message.whisperID.id != 0){
          output.push_back({ message.c, message.text, message.sendersRoomId});
          output.push_back({ message.whisperID, message.text, message.sendersRoomId});

        }
        else{
          for (auto user : sendersRoom->getUsers()) {
            output.push_back({ user.connection, message.text, message.sendersRoomId});
          }
        }
   }

   return output;
}

// part of our function that handles server commands
else if (commandName == "create")
  {
    std::string targetRoomName;
    auto tokens = tokenizeMessage(message.text);

    try
    {
      targetRoomName = tokens.at(1);
    }
    catch (const std::exception &e)
    {
      std::cout << "Room name is not provided for /create" << '\n';
      std::cout << e.what() << "\n";
      result << "Please provide a room name.\n";
    }

    // check if the room already exists
    Room *existingRoom = getRoomByName(targetRoomName);

    if (existingRoom != nullptr)
    {
      result << "The room " << targetRoomName << " exists. Please use /join " << targetRoomName
             << " to join the room.\n";
    }
    else
    {
      Room newRoom(rooms.size(), targetRoomName);
      User* user = getUser(message.c);

      // leave the user's current room
      Room* currentRoom = getRoomById(user->getRoom());
      std::cout << currentRoom->getRoomId() << "\n";

      if (currentRoom != nullptr) {
        currentRoom->removeUser(*user);
      }

      newRoom.addUser(*user);
      rooms.push_back(newRoom);
      result << "Created and joined room " << targetRoomName << " (" << newRoom.getRoomId() << ").\n";
    }
  }

////////////////////////////////////////////JSON PARSING SIDE:////////////////////////////////////////////////////////

//Traverses through all the rules in json file and calls the specific functions
ForEachRule *Loader::forEachRule(json element) {
    ForEachRule *forEach = new ForEachRule(element.at("list").get<string>(), element.at("element").get<string>());
    json rules = element["rules"];
    for (const json rule : rules) {
        auto ruleName = rule.at("rule").get<string>();

        if (ruleName == "global-message") {
            GlobalMessage *ruleIndex = globalMessageRule(rule);
            forEach->addRule(ruleIndex);
        } else if (ruleName == "parallelfor") {
            ParallelFor *ruleIndex = parallelForRule(rule);
            forEach->addRule(ruleIndex);
        } else if (ruleName == "discard") {
            DiscardRule *ruleIndex = discardRule(rule);
            forEach->addRule(ruleIndex);
        } else if (ruleName == "when") {
            WhenRule *when = whenRule(rule);
            forEach->addRule(when);
        } else if (ruleName == "foreach") {
            ForEachRule *ruleIndex = forEachRule(rule);
            forEach->addRule(ruleIndex);
        } else if (ruleName == "input-choice") {
            InputChoiceRule *ruleIndex = inputChoiceRule(rule);
            forEach->addRule(ruleIndex);
        }
    }
    return forEach;
}

//Creates the whenRule object for the "when rule"
WhenRule *Loader::whenRule(json rule) {
    json conditions = rule["cases"];
    
    WhenRule *whenRule = new WhenRule();
    for (const json ele : conditions) {
        string check = ele["condition"].dump();
        Case* cas = new Case(check);
        
        json ruleList = ele["rules"];

        for (const json element : ruleList) {
            auto ruleName = element.at("rule").get<string>();
            if (ruleName == "extend") {
                ExtendRule* ruleIndex = extendRule(element);
                cas -> addRule(ruleIndex);
            } else if (ruleName == "global-message") {
                GlobalMessage *ruleIndex = globalMessageRule(element);
                cas -> addRule(ruleIndex);
            } else if (ruleName == "foreach") {      
                ForEachRule *ruleIndex = forEachRule(element);
                cas -> addRule(ruleIndex);
            }
        }
        cout << endl;
        whenRule -> addCase(cas);
        //parse the given condition
        //if condition is true: extract element["rules"]
    }

    return whenRule;
}