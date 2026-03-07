#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include "player.h"


class Enemy {

    private:
    std::string name;
    int hp;
    int attackPower;
    int goldReward;
    int xpReward;

    public:
    Enemy(std::string enemyName, int enemyHp, int enemyAttack, int reward, int exp) {
        name = enemyName;
        hp = enemyHp;
        attackPower = enemyAttack;
        goldReward = reward;
        xpReward = exp;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }

    // --- IS ALIVE ---
    bool isAlive() {
        return hp > 0;
    }

    // --- GETTERS ---
    int getAttack() { return attackPower; }
    int getHp() { return hp; }
    int getGoldReward() { return goldReward; }
    int getXpReward() { return xpReward; }
    std::string getName() { return name; }

    // Virtual method for loot drops
    virtual void dropLoot(Player& player) {}

};

class Goblin : public Enemy {
    public : Goblin() : Enemy("Goblin", 30, 8, 10, 12) {}
    void dropLoot(Player& player) override {
        Item potion("Health Potion", CONSUMABLE, 30);
        player.addItem(potion);
    }
};

class Skeleton : public Enemy {
    public : Skeleton() : Enemy("Skeleton", 40, 7, 12, 15) {}
    void dropLoot(Player& player) override {
        Item sword("Iron Sword", WEAPON, 10);
        player.addItem(sword);
        Item shield("Wooden Shield", ARMOR, 3);
        player.addItem(shield);
    }
};

class Troll : public Enemy {
    public : Troll() : Enemy("Troll", 55, 10, 18, 25) {}
    void dropLoot(Player& player) override {
        Item potion("Health Potion", CONSUMABLE, 30);
        player.addItem(potion);
    }
};

class Dragon : public Enemy {
    public : Dragon() : Enemy("Dragon", 70, 14, 25, 32) {}
    void dropLoot(Player& player) override {
        Item sword("Diamond Sword", WEAPON, 18);
        player.addItem(sword);
        Item shield("Obsidian Shield", ARMOR, 8);
        player.addItem(shield);
    }
};

class Mutant : public Enemy {
    public : Mutant() : Enemy("Mutant", 105, 20, 40, 52) {}
    void dropLoot(Player& player) override {
        Item trophy("Mutant Head", COLLECTIBLE, 0);
        player.addItem(trophy);
        Item potion("Health Potion", CONSUMABLE, 30);
        player.addItem(potion);
    }
};

#endif