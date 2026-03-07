#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>


enum ItemType {
    WEAPON,
    ARMOR,
    CONSUMABLE,
    COLLECTIBLE
};

class Item {

    private:
    std::string name;
    ItemType type;
    int value;

    public:
    Item(std::string itemName, ItemType itemType, int itemValue) {
        name = itemName;
        type = itemType;
        value = itemValue;
    }

    // Getters
    std::string getName() { return name; }
    ItemType getType() { return type; }
    int getValue() { return value; }

    // Prints single line desc. of the item
    void printInfo() {
        std::string typeLabel;
        if (type == WEAPON)       typeLabel = "Weapon";
        if (type == ARMOR)        typeLabel = "Armor";
        if (type == CONSUMABLE)   typeLabel = "Consumable";
        if (type == COLLECTIBLE)  typeLabel = "Collectible";

        std::cout << name << " [" << typeLabel << "] +" << value << "\n";
    }
};

#endif