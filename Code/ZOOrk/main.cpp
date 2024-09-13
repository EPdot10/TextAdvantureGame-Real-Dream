#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"


int main() {
    std::cout << "Welcome to my game--REAL DREAM!" << std::endl;
    std::cout << "Background introduce:" << std::endl;
    std::cout << " This is a fictional world. The IMC Corporation is a colossal monopolistic entity, which controls the world's resources. To combat IMC's overwhelming control, a resistance movement has emerged." << std::endl;
    std::cout << " You are a special agent of this resistance.\n";
    std::cout << " Your current mission is to infiltrate an unknown IMC research facility to locate Colonel Anderson, who has gone missing during his mission. And keep continue to investigate the institute." << std::endl;
    std::cout << "\nHelper-- use command to play this game. Here is our basic command:" << std::endl;
    std::cout << " 1. go [direction] -- move to another room" << std::endl;
    std::cout << " 2. look/inspect -- look around the room" << std::endl;
    std::cout << " 3. take/get [item] -- take an item" << std::endl;
    std::cout << " 4. drop [item] -- drop an item" << std::endl;
    std::cout << " 5. use/u [item] -- use an item" << std::endl;
    std::cout << " 6. talk -- talk to a character in current room" << std::endl;
    std::cout << " 7. map/m -- show the map" << std::endl;
    std::cout << " 8. lb/listbag" << std::endl;
    std::cout << " 9. quit -- quit the game" << std::endl;
    std::cout << " More command will be seen in the game" << std::endl;
    auto roomsMap = loadingMap();
    auto start = roomsMap["entry-hall"];
    ZOOrkEngine zoork(start, roomsMap);
    zoork.run();
    return 0;
}
