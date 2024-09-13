//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room>, const std::map<std::string, std::shared_ptr<Room>>&);

    ZOOrkEngine loadingMap();

    void run();

    bool isPowerOn = false;

    bool isWristbandCharged = false;

private:
    bool gameOver = false;
    Player *player;

    std::map<std::string, std::shared_ptr<Room>> roomsMap; // Mapping of room names to room objects

    void handleGoCommand(std::vector<std::string>);

    void handleLookCommand(std::vector<std::string>);

    void handleTakeCommand(std::vector<std::string>);

    void handleDropCommand(std::vector<std::string>);

    void handleQuitCommand(std::vector<std::string>);

    void handleMapCommand(std::vector<std::string>);

    void handleListBagCommand(std::vector<std::string>);

    void handleUseCommand(std::vector<std::string>);

    void handleTalkCommand(std::vector<std::string>);

    void handleArchiveChoice();

    void handleControlRoomChoice();

    Room* getRoom(std::string roomName);

    static std::vector<std::string> tokenizeString(const std::string&);

    static std::string makeLowercase(std::string);
};

std::map<std::string, std::shared_ptr<Room>> loadingMap();


#endif //ZOORK_ZOORKENGINE_H
