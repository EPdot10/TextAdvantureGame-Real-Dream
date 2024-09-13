//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addItem(Item *i) {
    items.push_back(i);
}

void Room::removeItem(const std::string &name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            items.erase(items.begin() + i);
            return;
        }
    }
}

void Room::listItems() {
    if (items.size() == 0) {
        std::cout << "There is no item in the room.\n";
    } else {
        std::cout << "Items in this room:\n";
        for (int i = 0; i < items.size(); i++) {
            std::cout << items[i]->getName() << ": "<< items[i]->getDescription() <<std::endl;
        }
    }
}

Item *Room::getItem(const std::string &name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            return items[i];
        }
    }
    std::cout << "get nullptr item\n";
    return nullptr;
}

bool Room::hasItem(const std::string &name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

void Room::addCharacter(Character *c) {
    character = c;
}