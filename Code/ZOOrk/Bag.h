// bag 用于给player存放物品
#ifndef ZOORK_BAG_H
#define ZOORK_BAG_H
#include "Item.h"
#include <vector>
#include <string>
class Bag {
public:
    Bag();
    void addItem(Item*);
    void removeItem(Item*);
    void removeItem(std::string);
    void listItems();
    bool hasItem(std::string);
    Item* getItem(std::string);
private:
    std::vector<Item*> items;
};
#endif //ZOORK_BAG_H