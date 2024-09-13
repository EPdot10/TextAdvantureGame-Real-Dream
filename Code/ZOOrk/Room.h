//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include "vector"
#include <map>

class Item;

class Passage;

class Character;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);
    void addItem(Item*);
    void removeItem(const std::string&);
    Item* getItem(const std::string&);
    bool hasItem(const std::string&);
    void listItems();
    std::vector<Item*> items;
//    Item* retrieveItem(const std::string&);
    void addCharacter(Character*);
//    void removeCharacter(const std::string&);
//    Character* getCharacter(const std::string&);

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

    Character* character = nullptr;

protected:

//    std::vector<Character*> characters;
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
};


#endif //ZOORK_ROOM_H
