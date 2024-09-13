//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"
#include "Room.h"
#include <memory>

class Room;

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

    void lookItem();

    void SettingUsage(Room*, std::string);

    Room* getTargetRoom();
    
    Room* targetRoom;
    
    std::string useDescription = "";

    int getUseCount() const {
        return useCount;
    }

    void addUseCount() {
        useCount++;
    }

protected:
    std::shared_ptr<Command> useCommand;
    int useCount = 0; 
};

#endif //ZOORK_ITEM_H
