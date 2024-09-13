//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

Player *Player::playerInstance = nullptr;

Player *Player::instance() {
    if (!playerInstance) {
        playerInstance = new Player();
    }
    return playerInstance;
}


void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItemToBag(Item* item) {
    if (bag != nullptr) {
        bag->addItem(item);
         std::cout << "You picked up the " << item->getName() << " into your bag" << std::endl;
    }
}

void Player::dropItemFromBag(Item* item) {
    if (bag != nullptr) {
        bag->removeItem(item);
        std::cout << "You dropped the " << item->getName() << "from your bag" << std::endl;
    }
}

void Player::listBagItems() {
    std::cout << "Items in your bag:\n";
    if (bag != nullptr) {
        bag->listItems();
    }else{
        std::cout << "You don't have a bag" << std::endl;
    }
}

