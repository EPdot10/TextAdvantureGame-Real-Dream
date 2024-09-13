//
// Created by Richard Skarbez on 5/7/23.
//

#include "Item.h"

#include <utility>

Item::Item(const std::string &n, const std::string &d) : GameObject(n, d),
                                                         useCommand(std::make_shared<NullCommand>()) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : GameObject(n, d),
                                                                                     useCommand(std::move(c)) {}

void Item::use() {
    useCommand->execute();
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}

void Item::lookItem() {
    std::cout << "You looked the " << name << std::endl;
    std::cout << description << std::endl;
}

void Item::SettingUsage(Room* r, std::string s) {
    targetRoom = r;
    useDescription = s;
}

Room* Item::getTargetRoom(){
    return targetRoom;
}
