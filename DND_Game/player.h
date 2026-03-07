#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "item.h"
#include <fstream>


class Player {

    private:
    std::string name;
    int hp;
    int maxHp;
    int attackPower;
    int baseAttack;
    int defense;
    int gold;
    int xp = 0;
    int level = 1;
    std::vector<Item> inventory;
    std::string equippedWeapon;
    std::string equippedArmor;

    public:
    // Constructor for "constructing" characters
    Player(std::string playerName, int startingHp, int startingAttack) {
        name = playerName;
        hp = startingHp;
        maxHp = startingHp;
        attackPower = startingAttack;
        baseAttack = startingAttack;
        defense = 0;
        gold = 0;
        equippedWeapon = "";
        equippedArmor = "";
    }

    // --- SAVE SYSTEM
    void saveGame(int currentRoom, std::vector<bool>& roomCleared) {
        std::ofstream file("save.txt");
        file << name << "\n";
        file << hp << "\n";
        file << maxHp << "\n";
        file << attackPower << "\n";
        file << baseAttack << "\n";
        file << defense << "\n";
        file << gold << "\n";
        file << xp << "\n";
        file << level << "\n";
        file << equippedWeapon << "\n";
        file << equippedArmor << "\n";
        file << inventory.size() << "\n";
        file << currentRoom << "\n";
        for (int i = 0; i < roomCleared.size(); i++) {
            file << roomCleared[i] << "\n";
        }
        for (int i = 0; i < inventory.size(); i++) {
            file << inventory[i].getName() << "\n";
            file << inventory[i].getType() << "\n";
            file << inventory[i].getValue() << "\n";
        }

    }

    void loadGame(int& currentRoom, std::vector<bool>& roomCleared) {
        std::ifstream file("save.txt");
        file >> name;
        file >> hp;
        file >> maxHp;
        file >> attackPower;
        file >> baseAttack;
        file >> defense;
        file >> gold;
        file >> xp;
        file >> level;
        file.ignore();
        std::getline(file, equippedWeapon);
        std::getline(file, equippedArmor);
        int count;
        file >> count;
        file >> currentRoom;
        for (int i = 0; i < roomCleared.size(); i++) {
            bool val;
            file >> val;
            roomCleared[i] = val;
        }
        for (int i = 0; i < count; i++) {
            std::string itemName;
            int itemType, itemValue;
            file.ignore();
            std::getline(file, itemName);
            file >> itemType >> itemValue;
            inventory.push_back(Item(itemName, (ItemType)itemType, itemValue));
        }
    }

    // --- XP SYSTEM ---
    void addXp(int amount) {
        xp += amount;
        if (xp >= level*30) {
            level += 1;
            hp += 10;
            maxHp += 10;
            attackPower += 2;
            baseAttack += 2;
            std::cout << "You leveled up! You are now level " << level << "!" << std::endl;
        }
    }

    // ---- DAMAGE ----
    // Called when an enemy "hits" the player
    void takeDamage(int damage) {
        int actualDamage = damage - defense;
        if (actualDamage < 1) actualDamage = 1;
        hp -= actualDamage;
        if (hp < 0) hp = 0;
    }

    // --- ADD ITEM ---
    void addItem(Item item) {
        inventory.push_back(item);
        std::cout << item.getName() << " added to inventory.\n";
    }

    // --- PRINT INVENTORY ---
    void printInventory() {
        std::cout << "\n--- Inventory ---\n";

        if (inventory.empty()) {
            std::cout << "Your inventory is empty.\n";
            return;
        }
        for (int i = 0; i < inventory.size(); i++) {
            std::cout << "[" << i + 1 << "]";
            inventory[i].printInfo();
        }

        std::cout << "\nEquipped Weapon: "
                  << (equippedWeapon.empty() ? "None" : equippedWeapon) << "\n";
        std::cout << "\nEquipped Armor: "
                  << (equippedArmor.empty() ? "None" : equippedArmor) << "\n";
    }

    // --- USE ITEM ---
    void useItem(std::string itemName) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i].getName() == itemName) {

                // Found it -- check what type it is
                if (inventory[i].getType() == CONSUMABLE) {
                    heal(inventory[i].getValue());
                    std::cout << "You used " << itemName
                              << " and restored " << inventory[i].getValue() << " HP.\n";
                    inventory.erase(inventory.begin() + i);
                    return;
                } else {
                    std::cout << itemName << " is not a consumable item.\n";
                    return;
                }
            }
        }
        // If we get here, we never found the item
        std::cout << "You don't have a \"" << itemName << "\" in your inventory.\n";
    }

    // --- EQUIP ITEM ---
    void equipItem(std::string itemName) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i].getName() == itemName) {
                if (inventory[i].getType() == WEAPON) {
                    // Remove the old weapon's bonus first
                    // Then apply the new one
                    attackPower = baseAttack;
                    attackPower += inventory[i].getValue();
                    equippedWeapon = itemName;
                    std::cout << "You equipped " << itemName << ".\n";
                    std::cout << "Attack is now " << attackPower << ".\n";
                    return;
                }
                if (inventory[i].getType() == ARMOR) {
                    defense = inventory[i].getValue();
                    equippedArmor = itemName;
                    std::cout << "You equipped " << itemName << ".\n";
                    std::cout << "Defense is now " << defense << ".\n";
                    return;
                }
                // Found the item but it's a consumable -- can't equip those
                std::cout << itemName << " cannot be equipped. Use it instead.\n";
                return;
            }
        }
        std::cout << "You don't have a \"" << itemName << "\" in your inventory.\n";
    }

    // ---- HEAL ----
    // Called when a player uses a potion
    void heal(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp;
    }

    // ---- IS ALIVE ----
    // Returns true if hp > 0 and false if dead
    bool isAlive() {
        return hp > 0;
    }

    // --- GET DEFENSE ---
    int getDefense() {
        return defense;
    }

    // ---- GET ATTACK ----
    // Returns player's attack power.
    // Since attackPower is private, outside code can't read it directly
    // This function is the "window" that lets outside code see it
    // This is called a "getter"
    int getAttack() {
        return attackPower;
    }

    // ---- GET NAME ----
    // Same idea - a getter for the name
    std::string getName() {
        return name;
    }

    // ---- GET HP -----
    // Same idea - a getter for current hp
    int getHp() {
        return hp;
    }

    // ---- ADD GOLD ----
    // Adds gold after killing an enemy
    void addGold(int amount) {
        gold += amount;
    }

    // ---- PRINT STATS ----
    // Prints everything about the player in a clean format
    void printStats() {
        std::cout << "\n--- " << name << "'s Stats ---\n";
        std::cout << "HP:      " << hp << " / " << maxHp << "\n";
        std::cout << "Attack:  " << attackPower << "\n";
        std::cout << "Defense: " << defense << "\n";
        std::cout << "Gold:    " << gold << "\n";
        std::cout << "Weapon:  " << (equippedWeapon.empty() ? "None" : equippedWeapon) << "\n";
        std::cout << "Armor:   " << (equippedArmor.empty() ? "None" : equippedArmor) << "\n";
        std::cout << "Level :  " << level << "\n";
        std::cout << "XP:      " << xp << " / " << level * 30 << "\n";
    }

    void printShop() {
        while (true) {
            std::cout << "\n===== Welcome to the Shop =====" << std::endl;
            std::cout << "=  Health Potion: ----- 10 Gold\n";
            std::cout << "=  Gold Sword: -------- 40 Gold\n";
            std::cout << "=  Bronze Shield: ----- 28 Gold\n";
            std::cout << "===============================" << std::endl;
            std::cout << "Available Gold: " << gold << std::endl;
            std::cout << "\nWould you like to purchase something? (y) or (n)\n";
            std::string userChoice;
            std::cin >> userChoice;

            // Shop Logic
            if (userChoice == "y") {
                std::cout << "\nWhat would you like to purchase?" << std::endl;
                std::string userShopChoice;
                std::cin.ignore();
                std::getline(std::cin, userShopChoice);
                if (userShopChoice == "Health Potion") {
                    if (gold >= 10) {
                        gold -= 10;
                        Item potion("Health Potion", CONSUMABLE, 30);
                        addItem(potion);
                    }
                    else {
                        std::cout << "Not enough gold." << std::endl;
                    }
                }
                else if (userShopChoice == "Gold Sword") {
                    if (gold >= 40) {
                        gold -= 40;
                        Item sword("Gold Sword", WEAPON, 20);
                        addItem(sword);
                    }
                    else {
                        std::cout << "Not enough gold." << std::endl;
                    }
                }
                else if (userShopChoice == "Bronze Shield") {
                    if (gold >= 28) {
                        gold -= 28;
                        Item armor("Bronze Shield", ARMOR, 15);
                        addItem(armor);
                    }
                    else {
                        std::cout << "Not enough gold." << std::endl;
                    }
                }
            }
            else if (userChoice == "n" || userChoice == "quit") {
                break;
            }
        }
    
    }
};

#endif