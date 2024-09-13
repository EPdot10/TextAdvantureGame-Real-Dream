//
// Created by Xincheng on 2024-06-04.
//

#include "bag.h"
Bag::Bag() {
    items = std::vector<Item*>();
}
void Bag::addItem(Item* item) {
    items.push_back(item);
}
void Bag::removeItem(Item* item) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i] == item) {
            items.erase(items.begin() + i);
            return;
        }
    }
}

void Bag::removeItem(std::string name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            items.erase(items.begin() + i);
            return;
        }
    }
}

void Bag::listItems() {
    if (items.size() == 0) {
        std::cout << "There is nothing in the bag.\n";
    } else {
        std::cout << "Items in the bag:\n";
        for (int i = 0; i < items.size(); i++) {
            std::cout << items[i]->getName() <<": " << items[i]->getDescription() << std::endl;
        }
    }
}

bool Bag::hasItem(std::string name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

Item* Bag::getItem(std::string name) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getName() == name) {
            return items[i];
        }
    }
    return nullptr;
}