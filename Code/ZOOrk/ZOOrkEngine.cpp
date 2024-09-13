//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <utility>
#include <algorithm>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start, const std::map<std::string, std::shared_ptr<Room>>& roomsMap) : roomsMap(roomsMap) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "map" || command == "m") {
            handleMapCommand(arguments);
        } else if(command == "listbag" || command == "lb"){
            handleListBagCommand(arguments);
        } else if (command == "use" || command == "u"){
            handleUseCommand(arguments);
        }else if (command == "talk"){
            handleTalkCommand(arguments);
        }else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

// loadingMap function
std::map<std::string, std::shared_ptr<Room>> loadingMap() {
    std::map<std::string, std::shared_ptr<Room>> roomsMap;
    // current time's room
    auto entryHall = std::make_shared<Room>("entry-hall", "You're at the entrance gate. There's a steel door in front of you with the IMC Corporation logo.\n The door to the north is open, it seems like someone tried to escape. You can choose to enter.\n");
    auto imcLobby_Level1 = std::make_shared<Room>("IMC-lobby-Level1", "You've entered the IMC-lobby-Level 1. The lobby bears signs of a gunfight, with blood everywhere and bodies of soldiers in IMC uniforms lying on the floor. One soldier's body is strangely embedded in the ceiling, with only the lower half visible.\n A door to the west leads to the Office;\n A door to the east leads to the Observation Room;\nThere's a ventilation duct on the ceiling above, but you'll need a tool to reach it.\n");
    auto imcLobby_Level2 = std::make_shared<Room>("IMC-lobby-level2", "You've entered the second floor of the lobby. In the center of the floor, you see the upper half of the body from the first floor. Upon inspection, you realize it's Colonel Anderson. He's holding a wristband, and you read his last communication records: \n [Anderson discovered this IMC institute, reported the coordinates to the headquarters and sneaked into the base alone, and acquired a wearable device that the base was working on, according to him it was an experimental version of some kind of portable temporal weapon that IMC had been working on for years, in the shape of a wrist band, but accidentally triggered an alarm, and in the midst of the battle he had trouble meeting the enemy, and in the heat of the moment he activated the wristband he had acquired, and after that the record was interrupted.]\n You can use a ladder to go down to IMC-lobby-Level1.\n");
    auto office = std::make_shared<Room>("office", "The office is filled with bookshelves, and there's a ladder used for the shelves.\n A door to the north leads to the Study Room;\n A door to the south leads to the Archive;\n A door to the east leads to IMC-lobby-Level 1.\n");
    auto observationRoom = std::make_shared<Room>("observation-room", "You've entered the Observation Room. Inside, there's a glass cage with a naked man muttering to himself.\n You can talk to him (command: talk)\n A door to the north leads to the Lab;\n A door to the west leads to IMC-lobby-Level1.\n");
    auto studyRoom = std::make_shared<Room>("study-room", "The study room is filled with books and a photograph.\n A door to the south leads to the Office.\n");
    auto lab = std::make_shared<Room>("lab", "The lab contains a giant charging device that seems capable of charging the wristband, but it needs power to start.\n A door to the north leads to the Power-Supply-Room;\n A door to the south leads to the Observation Room.\n");
    auto powerSupplyRoom = std::make_shared<Room>("power-supply-room", "In the center of the power supply room, there's a power control console that can activate the backup power.\n A door to the west leads to the Time-Core-Room, but it requires a password;\n A door to the south leads to the Lab.\n");
    auto archives = std::make_shared<Room>("archives", "The archive room is filled with shelves, and there's a fire pit where all important documents have been burned.\n A door to the north leads to the Office.\n");
    auto timeCoreRoom = std::make_shared<Room>("time-core-room", "The time core room has a glowing spherical reactor in the center.\n There's one dressed like a scientist here.\n You can talk to him (command: talk)\n A door to the north leads to the Control Center, but the path is destroyed;\n A door to the east leads to the Power-Supply-Room.\n");
    auto controlCenter = std::make_shared<Room>("control-center", "The control center is filled with servers and control consoles.\n A door to the south leads to the Time-Core-Room.\n");


    // current passages
    Passage::createBasicPassage(entryHall.get(), imcLobby_Level1.get(), "north", true);
    Passage::createBasicPassage(imcLobby_Level1.get(), office.get(), "west", true);
    Passage::createBasicPassage(imcLobby_Level1.get(), observationRoom.get(), "east", true);
    // Passage::createBasicPassage(imcLobby_Level1.get(), imcLobby_Level2.get(), "up", true);
    Passage::createBasicPassage(observationRoom.get(), lab.get(), "north", true);
    Passage::createBasicPassage(lab.get(), powerSupplyRoom.get(), "north", true);
    Passage::createBasicPassage(powerSupplyRoom.get(), timeCoreRoom.get(), "west", true);
    // Passage::createBasicPassage(timeCoreRoom.get(), controlCenter.get(), "north", true);
    Passage::createBasicPassage(office.get(), studyRoom.get(), "north", true);
    Passage::createBasicPassage(office.get(), archives.get(), "south", true);



    auto entryHall_past = std::make_shared<Room>("entry-hall-past", "You're at the entrance gate --past timeline. There's a steel door in front of you with the IMC Corporation logo.\n The door to the north is locked.\n");
    auto imcLobby_Level1_past = std::make_shared<Room>("IMC-lobby-Level1-past", "You've entered the IMC-lobby-Level 1 --past timeline. The lobby is very quiet, the floor is clean, and everything seems normal.\n A door to the west leads to the Office;\nA door to the east leads to the Observation Room;\n There's a ventilation duct on the ceiling above, but you'll need a tool to reach it.\n");
    auto imcLobby_Level2_past = std::make_shared<Room>("IMC-lobby-level2-past", "You've entered the second floor of the lobby --past timeline. The center of the floor is empty.\n You can use a ladder to go down to IMC-lobby-Level1.\n");
    auto office_past = std::make_shared<Room>("office-past", "You've entered the office --past timeline, which is filled with bookshelves.\nA door to the north leads to the Study Room;\n A door to the south leads to the Archive;\n A door to the east leads to IMC-lobby-Level 1.\n");
    auto observationRoom_past = std::make_shared<Room>("observation-room-past", "You've entered the Observation Room --past timeline. Inside, there's a glass cage.\n A door to the north leads to the Lab;\n A door to the west leads to IMC-lobby-Level1.\n");
    auto studyRoom_past = std::make_shared<Room>("study-room-past", "You've entered the study room --past timeline, which is filled with books and a photograph.\n A door to the south leads to the Office.\n");
    auto lab_past = std::make_shared<Room>("lab-past", "You've entered the lab --past timeline. The giant charging device is gone, replaced by a pile of unassembled parts scattered around.\n A passage to the north leads to the Power-Supply-Room;\n A door to the south leads to the Observation Room.\n");
    auto powerSupplyRoom_past = std::make_shared<Room>("power-supply-room-past", "You've entered the Power Supply Room --past timeline. In the center, there's a power control console that seems to be able to charge some device.\n A door to the west leads to the Time-Core-Room, but it's still under construction.;\n A door to the south leads to the Lab.\n");
    auto archives_past = std::make_shared<Room>("archives-past", "You've entered the Archive Room --past timeline, which is filled with documents. You might find some clues here.\n A door to the north leads to the Office.\n");
    auto timeCoreRoom_past = std::make_shared<Room>("time-core-room-past", "You've entered the Time Core Room --past timeline. In the center, there's a spherical reactor under construction. \n A door to the north leads to the Control Center, and this door is not blocked;\n A door to the east leads to the Power-Supply-Room.\n");
    auto controlCenter_past = std::make_shared<Room>("control-center-past", "You've entered the Control Center --past timeline, there are servers and control consoles still under construction.\n A door to the south leads to the Time-Core-Room.\n");


    // past passages
    Passage::createBasicPassage(imcLobby_Level1_past.get(), entryHall_past.get(), "north", false);
    Passage::createBasicPassage(imcLobby_Level1_past.get(), office_past.get(), "west", true);
    Passage::createBasicPassage(imcLobby_Level1_past.get(), observationRoom_past.get(), "east", true);
    // Passage::createBasicPassage(imcLobby_Level1_past.get(), imcLobby_Level2_past.get(), "up", true);
    Passage::createBasicPassage(observationRoom_past.get(), lab_past.get(), "north", true);
    Passage::createBasicPassage(lab_past.get(), powerSupplyRoom_past.get(), "north", true);
    // Passage::createBasicPassage(powerSupplyRoom_past.get(), timeCoreRoom_past.get(), "west", true);
    Passage::createBasicPassage(timeCoreRoom_past.get(), controlCenter_past.get(), "north", true);
    Passage::createBasicPassage(office_past.get(), studyRoom_past.get(), "north", true);
    Passage::createBasicPassage(office_past.get(), archives_past.get(), "south", true);

    // time-travel passages
    Passage::createBasicPassage(entryHall.get(), entryHall_past.get(), "time-travel", true);
    Passage::createBasicPassage(imcLobby_Level1.get(), imcLobby_Level1_past.get(), "time-travel", true);
    Passage::createBasicPassage(imcLobby_Level2.get(), imcLobby_Level2_past.get(), "time-travel", true);
    Passage::createBasicPassage(office.get(), office_past.get(), "time-travel", true);
    Passage::createBasicPassage(observationRoom.get(), observationRoom_past.get(), "time-travel", true);
    Passage::createBasicPassage(studyRoom.get(), studyRoom_past.get(), "time-travel", true);
    Passage::createBasicPassage(lab.get(), lab_past.get(), "time-travel", true);
    Passage::createBasicPassage(powerSupplyRoom.get(), powerSupplyRoom_past.get(), "time-travel", true);
    Passage::createBasicPassage(archives.get(), archives_past.get(), "time-travel", true);
    Passage::createBasicPassage(timeCoreRoom.get(), timeCoreRoom_past.get(), "time-travel", true);
    Passage::createBasicPassage(controlCenter.get(), controlCenter_past.get(), "time-travel", true);

    // add items
    Item *ladder = new Item("ladder", "A ladder that seems like it can be used to reach higher places.");
    ladder->SettingUsage(imcLobby_Level1.get(), "You use the ladder to climb to the second floor.");
    office->addItem(ladder);

    Item *wristband = new Item("wristband", "A wristband with a button on it, seems to have some special function.");
    wristband->SettingUsage(nullptr, "You press the button on the wristband, but nothing happens. It seems to need power.");
    imcLobby_Level2->addItem(wristband);

    Item *powercontrol = new Item("powercontrol", "A power control console, seems like it can activate the backup power.");
    powercontrol->SettingUsage(powerSupplyRoom.get(), "You activated the backup power, and the facility's power is restored.");
    powerSupplyRoom->addItem(powercontrol);

    Item *photo = new Item("photo", "An old photo, seems to be a family photo of a staff member.");
    photo->SettingUsage(studyRoom.get(), "There's nothing special on the front of the photo, but the back has a line of text that has been rubbed off and is now unreadable.");
    studyRoom->addItem(photo);

    Item *photo_past = new Item("photo_past", "A new photo, seems to be a family photo of a staff member.");
    photo_past->SettingUsage(studyRoom_past.get(), "There's nothing special on the front of the photo, but the back has a clear line of text: Time Core password: 123456");
    studyRoom_past->addItem(photo_past);

    Item *archive = new Item("archive", "A file labeled: IMC-2040.");
    archive->SettingUsage(archives.get(), "You found a file titled 'Real Dream-0012'. After reading it, you discovered:\n 'Real Dream' is one of IMC's key projects.\n The plan is to research time travel devices and send a selected group of individuals back in time,\n bringing advanced knowledge and technology to strengthen IMC's power and monopoly.");
    archives_past->addItem(archive);

    Item *time_core = new Item("time_core", "A glowing spherical reactor that seems like it can be used for time travel, but it cannot be activated here. You must reach the control room to control it.");
    timeCoreRoom->addItem(time_core);

    Item *controler = new Item("controler", "A console that seems to control the time core.");
    controlCenter->addItem(controler);

    Item *charger = new Item("charger", "A giant charging device that seems to be able to charge the wristband.");
    charger->SettingUsage(lab.get(), "You activated the charging device, and the wristband is fully charged, emitting a faint glow. Congratulations, you can now use it.");
    lab->addItem(charger);

    // add item to room and set its target room

    Character *nakedman = new Character("nakedman", "A naked man who seems to have experienced explosions and abuse, with scars covering his upper body and face. The dim light and his scarface make it hard to see his face.");
    observationRoom->addCharacter(nakedman);

    Character *scientist = new Character("scientist", "A scientist anxiously moving rocks blocking the way to the control room.");
    timeCoreRoom->addCharacter(scientist);

    roomsMap["entry-hall"] = entryHall;
    roomsMap["IMC-lobby-Level1"] = imcLobby_Level1;
    roomsMap["IMC-lobby-level2"] = imcLobby_Level2;
    roomsMap["office"] = office;
    roomsMap["observation-room"] = observationRoom;
    roomsMap["study-room"] = studyRoom;
    roomsMap["lab"] = lab;
    roomsMap["power-supply-room"] = powerSupplyRoom;
    roomsMap["archives"] = archives;
    roomsMap["time-core-room"] = timeCoreRoom;
    roomsMap["control-center"] = controlCenter;

    roomsMap["entry-hall-past"] = entryHall_past;
    roomsMap["IMC-lobby-Level1-past"] = imcLobby_Level1_past;
    roomsMap["IMC-lobby-level2-past"] = imcLobby_Level2_past;
    roomsMap["office-past"] = office_past;
    roomsMap["observation-room-past"] = observationRoom_past;
    roomsMap["study-room-past"] = studyRoom_past;
    roomsMap["lab-past"] = lab_past;
    roomsMap["power-supply-room-past"] = powerSupplyRoom_past;
    roomsMap["archives-past"] = archives_past;
    roomsMap["time-core-room-past"] = timeCoreRoom_past;
    roomsMap["control-center-past"] = controlCenter_past;

    return roomsMap;
}

// go command
void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else if(arguments[0] == "t" || arguments[0] == "time"){
        if(isWristbandCharged){
            Item *wristBand = player->getItemFromBag("wristband");
            if(wristBand->getUseCount() == 0){
                std::cout << "!!! I found myself in the past, the past when the IMC was just starting to build the organisation.\n";
            }
            if(wristBand->getUseCount() == 10){
                // game over
                std::cout << "You used the wristband, but it ran out of energy. Game over.\n";
                gameOver = true;
            }
            if(player->getCurrentRoom()->getName().find("past") != std::string::npos)
            {
                direction = "time-travel-back";
                std::cout << "Time-traveling start, you through a bright light and see.\n";
                wristBand->addUseCount();
            }else{
                direction = "time-travel";
                std::cout << "Time-traveling start, you through a bright light and see.\n";
                wristBand->addUseCount();
            }
        }else{
            std::cout << "You cann't use this command now.\n";
        }
    }else {
        direction = arguments[0];
    }
    // player need to use labpassword to open the lab door; need to use photo_past(password) to open the power-supply-room door
    if(player->getCurrentRoom()->getName() == "observation-room" && direction == "north" && player->getItemFromBag("labpassword") == nullptr){
        std::cout << "Door is locked with a password, need u to put password in your bag\n";
    }else if(player->getCurrentRoom()->getName() == "observation-room" && direction == "north" && player->getItemFromBag("labpassword") != nullptr){
        std::cout << "Opening lab door with lab password\n";
        Room* currentRoom = player->getCurrentRoom();
        auto passage = currentRoom->getPassage(direction);
        player->setCurrentRoom(passage->getTo());
        passage->enter();
    }else if(player->getCurrentRoom()->getName() == "power-supply-room" && direction == "west" && player->getItemFromBag("photo_past") == nullptr){
        std::cout << "Door is locked with a password, can't open now.\n";
    }else if(player->getCurrentRoom()->getName() == "power-supply-room" && direction == "west" && player->getItemFromBag("photo_past") != nullptr){
        std::cout << "please enter the password:\n";
        std::string password;
        std::getline(std::cin, password);
        if(password == "123456"){
            std::cout << "Opening control center door.\n";
            Room* currentRoom = player->getCurrentRoom();
            auto passage = currentRoom->getPassage(direction);
            player->setCurrentRoom(passage->getTo());
            passage->enter();
        }else{
            std::cout << "Password is wrong.\n";
        }
    }else{
        Room* currentRoom = player->getCurrentRoom();
        auto passage = currentRoom->getPassage(direction);
        player->setCurrentRoom(passage->getTo());
        passage->enter();
    }
    
}

// look command
void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    std::cout << "You are looking around...\n";
    if (arguments.empty()) {
        player->getCurrentRoom()->enter();
        player->getCurrentRoom()->listItems();
        if(player->getCurrentRoom()->character != nullptr){
            std::cout << "Character: \n";
            std::cout << player->getCurrentRoom()->character->getDescription() << std::endl;
        }
    } else {
        std::string target = arguments[0];
        if (player->getCurrentRoom()->hasItem(target)) {
             player->getCurrentRoom()->getItem(target)->lookItem();
        }else {
             std::cout << "There is no " << target << " here.\n";
        }
    }
}

// handle talk command
void ZOOrkEngine::handleTalkCommand(std::vector<std::string> arguments) {
    if (player->getCurrentRoom()->character == nullptr) {
        std::cout << "There is no one to talk here.\n";
    } else {
        std::string name = player->getCurrentRoom()->character->getName();
        if(name == "nakedman"){
            if (!player->getCurrentRoom()->character->isTalked){
                std::cout << "Talking with nakedman\n You: Who are you? What's happening here?\n Nakedman: I lost my memory in an explosion and was captured here by a group of people. They did many inhuman experiments on me...\n Nakedman: Wait, I remember this wrist band of yours! A vague part of my memory tells me it's dangerous, don't try to use it, he'll invite disaster! Your companion died for it, too!\n You: Do you know how to get out of here?\n Nakedman: I don't know. The only thing I know is the code to Lab. I wrote it down on a piece of paper for you. You can go there and check it out.\n";
                player->getCurrentRoom()->character->isTalked = true;
                Item *labpassword = new Item("labpassword", "A piece of paper that says: Lab passworld: 7355608");
                labpassword->SettingUsage(player->getCurrentRoom(), "You used the code, opened the lab's door。");
                player->getCurrentRoom()->addItem(labpassword);
                handleTakeCommand({"labpassword"});
            }else{
                std::cout << "You talk to the nakedman\n Nakedman: There is nothing more to say, have a good day! or night? I don't know!! :) :) :) :)\n";
            }
        }
        if(name == "scientist"){
            if (!player->getCurrentRoom()->character->isTalked){
                std::cout << "You talk to the scientist.\n You: Who are you? What's happening here?\n Scientist: I am a scientist here. We have successfully experimented with time travel on a small wearable device. \n Scientist: Now I need to follow orders and go to the control room to activate the large time travel device.\n You: What's the purpose of this time travel device?\n Scientist: It was supposed to be a secret, but it's okay to tell you now. We discovered that the sun will explode in 100 years, it will destroying the entire solar system.\n The scientists have determined that with the current state of global cooperation, it will be impossible to develop a method to save the world within 100 years.\n Scientist: To maintain social stability, IMC has kept the impending doomsday a secret, and only a few people know about it.\n Scientist: IMC plans to increase its monopoly on various industries and concentrate the world's resources to secretly explore ways to save humanity.\n Scientist: : However, an agent infiltrated here, stole the small time travel device, and destroyed the passage to the control room.\n Scientist: Now I must find a way to get back to the control room and initiate the 'Real Dream' project.\n Scientist: Wait?! Who are you? Why am I telling you this? \n You: ...\n";
                std::cout << "Talking end. You need to find some way to get into the control room.(Hint:Time changes everything!)\n";
                player->getCurrentRoom()->character->isTalked = true;
            }else{
                std:: cout << " Scientist: Stop wasting my time! There's nothing more to say.\n";
            }
        }
    }
}

// take command
void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    std::vector<std::string> untakeableItems = {"photo", "archive", "controler", "time_core", "charger", "powercontrol"};
    if(arguments.empty()){
        std::cout << "Please input the item you want to take.\n";
        return;
    }
    else{
        std::string target = arguments[0];
        auto it = std::find(untakeableItems.begin(), untakeableItems.end(), target);
        Item* item = player->getCurrentRoom()->getItem(target);
        if(item != nullptr){
            if(it == untakeableItems.end()){
                player->addItemToBag(item);
                player->getCurrentRoom()->removeItem(target);
                std::cout << "You took the " << target << ".\n";
            }
            else{
                std::cout << "You can't take the " << target << ".\n";
            }  
        }else{
            std::cout << "There is no " << target << " here.\n";
        }
    }
}

// drop command
void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if(arguments.empty()){
        std::cout << "Please input the item you want to drop.\n";
        return;
    }
    else{
        std::string target = arguments[0];
        Item* item = player->getItemFromBag(target);
        if(item != nullptr){
            player->getCurrentRoom()->addItem(item);
            player->dropItemFromBag(item);
            std::cout << "You drop the " << target << ".\n";
        }else{
            std::cout << "There is no " << target << " in your bag.\n";
        }
    }

}

// handle use command
void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Please specify an item to use.\n";
    }

    std::string itemName = arguments[0];
    Item* item;
    if(player->getItemFromBag(itemName) == nullptr){
        if(!player->getCurrentRoom()->hasItem(itemName)){
            item = nullptr;
        }else{
            item = player->getCurrentRoom()->getItem(itemName);
        }
    }else{
        item = player->getItemFromBag(itemName);
    }

    if(item != nullptr){
        // ladder usage
        if (item->getName() == "ladder") {
            if(player->getCurrentRoom() == item->getTargetRoom()){
                std::cout << item->useDescription << std::endl;
                // add new passage
                auto level1 = roomsMap["IMC-lobby-Level1"];
                auto level2 = roomsMap["IMC-lobby-level2"];
                Passage::createBasicPassage(level1.get(), level2.get(), "up", true);
                // go to new room
                handleGoCommand({"up"});
            }
            else{
                std::cout << "You can't use the " << itemName << " here.\n";
            }
        }

        // uncharged wristband usage
        else if (item->getName() == "wristband") {
            std::cout << item->useDescription << std::endl;
        }

        // charger usage
        else if(item->getName() == "charger"){
            if(!isPowerOn){
                std::cout << "There is no power, you need to turn on the power first.\n";
            }
            else{
                if (player->getItemFromBag("wristband") == nullptr){
                    std::cout << "You need to offer someing to charge.\n";
                }
                else{
                    Item* wristband = player->getItemFromBag("wristband");
                    if(isWristbandCharged){
                        std::cout << "The wristband is already charged.\n";
                    }
                    else{
                        std::cout << "You put your wrist band on the charger's plug, Charger machine is start working!\n";
                        isWristbandCharged = true;
                        item = new Item("charged-wristband", "A wristband that has been charged, as if it had some special function, is ready to use! Use the go time/t command to use it.");
                        item->SettingUsage(nullptr, "You press the button on your wristband and a glow is emitted.");
                        std::cout << "You got a charged wristband.\n";
                        std::cout << "New command to use your wristband (to travel time): go time/t\n";
                    }
                }  
            }
        }

        // powercontrol usage
        else if(item->getName() == "powercontrol"){
            if(isPowerOn){
                std::cout << "The power is already on.\n";
            }
            else{
                std::cout << item->useDescription << std::endl;
                isPowerOn = true;
            }
        }

        // photo_past usage
        else if(item->getName() == "photo_past"){
            std::cout << item->useDescription << std::endl;
            std::cout << "automaticly put the photo into your bag. (save your time)\n";
            item = new Item("photo_past", "A new photo of what appears to be a family group photo of a staff member. On the back it says TimeCore passworld: 123456");
            player->getCurrentRoom()->removeItem("photo_past");
            player->addItemToBag(item);
        }

        // archive usage
        else if(item->getName() == "archive"){
            std::cout << item->useDescription << std::endl;
            std::cout << "automaticly put the archive into your bag. (save your time)\n";
            player->addItemToBag(item);
            player->getCurrentRoom()->removeItem(item->getName());
            handleArchiveChoice();
        }

        // time core usage
        else if(item->getName() == "time_core"){
            std::cout << "You can't use the " << itemName << " here, you need to go to the control room to control it.\n";
        }

        // controler usage
        else if(item->getName() == "controler"){
            handleControlRoomChoice();
        }

        // unknown usage
        else {
            std::cout << "Unknow usage.\n";
        }
    }else{
        std::cout << "There is no " << itemName << " to use.\n";
    }
}


// listBag command
void ZOOrkEngine::handleListBagCommand(std::vector<std::string> arguments) {
    player->listBagItems();
}

// quit command
void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

// map command
void ZOOrkEngine::handleMapCommand(std::vector<std::string> arguments) {
    std::cout << "This is IMC's map:\n";
    std::vector<std::string> map = {
        "               [Control-Center]",
        "                       |",
        "               [Time-Core-Room]-------[Power-Supply-Room]",
        "                                               |",
        "[Study Room]   [IMC-lobby-Level2]            [Lab]",
        "   |                   |                       |",
        "[Office]-------[IMC-lobby-Level1]------[Observation-Room]",
        "   |                   |",
        "[Archive]         [Entry-Hall]"
    };
    for (const auto &line : map) {
        std::cout << line << std::endl;
    }
    std::cout << "You are currently in: " << player->getCurrentRoom()->getName() << std::endl;
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

void ZOOrkEngine::handleArchiveChoice(){
    std::string input;
    std::cout << "You have discovered the secrets of the IMC Institute, and now you can choose to:\n 1. Use the wristband to return to the original time and space and leave the Institute to report back to the Resistance.\n 2.Choose to continue exploring and find the large temporal device to destroy it.\n> ";
    std::cout << "Please input your choice. Do u want to leave here: (y/n)\n";
    std::getline(std::cin, input);
    if (input == "y" || input == "yes") {
        std::cout << "Congratulations! **Devil ending**:\n You evacuated the Institute in time to report your findings to the Resistance.\n The Resistance, after learning this news. Publicising to the public that IMC was researching weapons of mass destruction, the Resistance led the sweep of the IMC Institute.\n They used a large time travel device to travel to the past to wipe out the IMC, and in the process, the Resistance became the new First Monopoly.\n ... 100 years past ... \n The solar system exploded.\n";
        gameOver = true;
    }
    if (input == "n" || input == "no")
    {
        std::cout << "Nice choice, you are brave enough to face future the danger!\n Game continue...\n";
    }
    else
    {
        std::cout << "Input error.\n";
    }
    std::cin.clear();
}

void ZOOrkEngine::handleControlRoomChoice(){std::string input;
    std::cout << "You have found the core device of the IMC research facility - the large time travel device, and you have found the console. You can now choose:\n";
    std::cout << "1. Stick to the resistance's position: activate the system's self-destruct program and destroy the Time Core\n";
    std::cout << "2. Change your stance and help IMC implement the Real Dream plan: replace the IMC scientist and start the Real Dream plan to send yourself 100 years into the past, taking on the mission to save humanity.\n";
    std::cout << "3. Do nothing, let IMC execute their plan.\n";
    std::cout << "Please input your choice: (1/2/3)\n";
    std::getline(std::cin, input);

    if (input == "1") {
        std::cout << "Congratulations! **Nightmare Ending**:\n";
        std::cout << "You activated the self-destruct program of the research facility. During the explosion, you could only use the wristband to travel through time to escape.\n";
        std::cout << "Although you successfully transported yourself away, you were affected by the explosion and lost your memory.\n";
        std::cout << "When you wake up from your coma, you find yourself in a transparent cage, being sent to the observation room...\n";
        std::cout << "Your nightmare begins.\n";
        gameOver = true;
    }

    else if (input == "2") {
        std::cout << "Congratulations! **Sun Ending**:\n";
        std::cout << "According to the Real Dream plan, you activated the Time Core, but you set yourself as the target for transportation.\n";
        std::cout << "100 years ago, with your knowledge from the future, you became the leader of IMC, dedicating your life to finding a way to prevent the sun's explosion...\n";
        std::cout << "200 years later, the solar system still exploded. You were not the one who could save humanity.\n";
        gameOver = true;
    }

    else if (input == "3") {
        std::cout << "Congratulations! **IMC Ending**:\n";
        std::cout << "You chose to do nothing and used the wristband to escape the research facility.\n";
        std::cout << "You reported to the resistance that this research facility was just an ordinary facility, and soon after, you left the resistance.\n";
        std::cout << "Shortly after, IMC successfully launched the Real Dream plan, handing over the future of humanity to IMC.\n";
        std::cout << "Although the monopoly of the IMC group made people's lives difficult for 200 years, IMC successfully prevented the sun's explosion.\n";
        gameOver = true;
    }
    else
    {
        std::cout << "Input error.\n";
    }
    std::cin.clear();
}


