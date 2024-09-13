//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include "Bag.h"

class Player : public Character {
public:
    static Player *instance();

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

    void addItemToBag(Item* item);

    void listBagItems();

    void dropItemFromBag(Item* item);

    Item* getItemFromBag(std::string name){
        return bag->getItem(name);
    };

private:
    static Player *playerInstance;
    Room* currentRoom;
    Bag* bag = new Bag();

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
