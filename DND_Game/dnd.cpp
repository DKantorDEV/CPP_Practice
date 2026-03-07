#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

// ----------------------------------------------------------------------

// Item Class
#include "item.h"

// Player Class
#include "player.h"

// Enemy Class
#include "enemy.h"

// --- COMBAT FUNCTION ---
void combat (Player& player, Enemy& enemy) {
    std::cout << "\n*** COMBAT BEGINS ***\n";
    std::cout << "You encounter a " << enemy.getName() << "!\n";

    std::string command;

    // Combat loop -- keeps going until someone dies
    while (player.isAlive() && enemy.isAlive()) {

        std::cout << "\n------------------------------\n";
        std::cout << "Your HP: " << player.getHp() << "\n";
        std::cout << enemy.getName() << " HP: " << enemy.getHp() << "\n";
        std::cout << "------------------------------\n";
        std::cout << "What do you do? [attack / run]\n> ";
        std::cin >> command;

        if (command == "attack") {
            // Player hits enemy
            int damage = player.getAttack() - 3 + (rand() % 7);
            enemy.takeDamage(damage);
            std::cout << "\nYou hit the " << enemy.getName()
                      << " for " << damage << " damage!\n";
            
            // Check if enemy died from that hit
            if (!enemy.isAlive()) {
                std::cout << "\nYou defeated the " << enemy.getName() << "!\n";
                player.addGold(enemy.getGoldReward());
                player.addXp(enemy.getXpReward());
                enemy.dropLoot(player);
                std::cout << "You earned " << enemy.getGoldReward() << " gold.\n";
                std::cout << "You earned " << enemy.getXpReward() << " XP.\n";
                break;
            }

            // Enemy hits back if still alive
            int missRoll = rand() % 10;
            if (missRoll == 0) {
                std::cout << "The " << enemy.getName() << "'s attack missed!\n";
            } else {
                int enemyDamage = enemy.getAttack() - 2 + (rand() % 5);
                player.takeDamage(enemyDamage);
                std::cout << "The " << enemy.getName()
                        << " hits you for " << enemyDamage << " damage!\n";
            }

            // Check if Player died
            if (!player.isAlive()) {
                std::cout << "\nYou have been defeated...\n";
                std::cout << "GAME OVER!\n";
                break;
            }
        }

        else if (command == "run") {
            // 50% chance to escape
            // rand() % 2 gives either 0 or 1 randomly
            int roll = rand() % 2;
            if (roll == 1) {
                std::cout << "\nYou managed to escape!\n";
                break;
            } else {
                std::cout << "\nYou failed to escape!\n";
                // Enemy hits you since you failed
                int enemyDamage = enemy.getAttack();
                player.takeDamage(enemyDamage);
                std::cout << "The " << enemy.getName()
                          << " hits you for " << enemyDamage << " damage!\n";
            }
        }

        else {
            std::cout << "\nInvalid Command. Try: attack, run\n";
        }
    }
}

// Room Structure Blueprint
struct Room {
    std::string name;                                                                  // Room's Display Name
    std::string description;                                                           // Room's Description
    int northExit;                                                                     // Index of room to the North      -1 = No Exit
    int southExit;                                                                     // Index of room to the South      -1 = No Exit
    int eastExit;                                                                      // Index of room to the East       -1 = No Exit
    int westExit;                                                                      // Index of room to the West       -1 = No Exit
};

// Print Room Function (name + desc)
void printRoom(const Room& room) {
    std::cout << "\n=============================\n";
    std::cout << " " << room.name;
    std::cout << "\n=============================\n";
    std::cout << room.description << "\n";
}

// Prints Exit Function
void printExits(const Room& room) {
    std::cout << "\nExits: ";
    if (room.northExit != -1) std::cout << "[NORTH] ";
    if (room.southExit != -1) std::cout << "[SOUTH] ";
    if (room.eastExit != -1) std::cout << "[EAST] ";
    if (room.westExit != -1) std::cout << "[WEST] ";
    std::cout << "\n";
}

// Main Game Loop
int main() {

    srand(time(0)); // Seeds the random number generator with current time

    // Ask for player's name first
    std::cout << "Enter your name, adventurer: ";
    std::string playerName;
    std::cin >> playerName;

    // Create the player object using the constructor
    // Player(name, hp, attackPower)
    Player player(playerName, 100, 15);

    // Building the Rooms
    std::vector<Room> rooms;

    // Logic for if rooms have been cleared or not of enemies
    std::vector<bool> roomCleared;

    // Vector for adding enemies to rooms
    std::vector<Enemy*> roomEnemies;
    roomEnemies.push_back(nullptr);             // Room 0 - Entrance
    roomEnemies.push_back(nullptr);             // Room 1 - Corridor
    roomEnemies.push_back(new Goblin());        // Room 2 - Armory
    roomEnemies.push_back(new Troll());         // Room 3 - Library
    roomEnemies.push_back(new Skeleton());      // Room 4 - Dark Hall
    roomEnemies.push_back(new Dragon());        // Room 5 - Dragon Door
    roomEnemies.push_back(new Goblin());        // Room 6 - Command Center
    roomEnemies.push_back(new Troll());         // Room 7 - Control Room
    roomEnemies.push_back(new Mutant());        // Room 8 - Captain's Quarters

    // Room 0 -- Entrance
    Room r;
    r.name            = "Entrance";
    r.description     = "You wake up on a cold stone floor. The air smells\nof damp and decay. A corridor stretches to the NORTH.";
    r.northExit       = 1; // Leads to Corridor
    r.southExit       = -1;
    r.eastExit        = -1;
    r.westExit        = -1;
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 1 -- Corridor
    r.name            = "Corridor";
    r.description     = "A long corridor with cracked stone walls.\nTorches flicker. Paths lead SOUTH, EAST, and WEST.";
    r.northExit       = -1;
    r.southExit       = 0; // Back to Entrance
    r.eastExit        = 3; // Leads to Library
    r.westExit        = 2; // Leads to Armory
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 2 -- Armory
    r.name            = "Armory";
    r.description     = "Broken weapon racks line the walls. Most have been\nlooted. Exits: EAST back to corridor, SOUTH into darkness.";
    r.northExit       = -1;
    r.southExit       = 4;  // Leads to Dark Hall
    r.eastExit        = 1;  // Leads back to Corridor
    r.westExit        = -1; 
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 3 -- Library
    r.name            = "Library";
    r.description     = "Dusty bookshelves tower over you. A faint glow\ncomes from the pages. Exit to the WEST.";
    r.northExit       = -1;
    r.southExit       = -1; 
    r.eastExit        = -1; 
    r.westExit        = 1; // Leads back to Corridor
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 4 -- Dark Hall
    r.name            = "Dark Hall";
    r.description     = "You can barely see your hand in front of your face.\nSomething skitters in the darkness. Exit NORTH and SOUTH.";
    r.northExit       = 2; // Leads back to Corridor
    r.southExit       = 5; // Leads to Boss Door
    r.eastExit        = -1; 
    r.westExit        = -1; 
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 5 -- Boss Door
    r.name            = "Dragon Door";
    r.description     = "A massive iron door stands before you, covered in\nscorch marks. You hear breathing on the other side. Exits are NORTH and WEST.";
    r.northExit       = 4; // Leads back to Dark Hall
    r.southExit       = -1; 
    r.eastExit        = -1; 
    r.westExit        = 6; // Leads to Command Center 
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 6 -- Command Center
    r.name            = "Command Center";
    r.description     = "Woah! There are a lot of computers and\ntechnology in here. There seems to be an exit SOUTH and EAST.";
    r.northExit       = -1;
    r.southExit       = 7; // Leads to Control Room
    r.eastExit        = 5; // Leads back to Dragon Door
    r.westExit        = -1;
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 7 -- Control Room
    r.name            = "Control Room";
    r.description     = "This must be where they control the place. It's completely\nabandonded. You see an exit NORTH and WEST.";
    r.northExit       = 6; // Leads back to Command Center
    r.southExit       = -1;
    r.eastExit        = -1;
    r.westExit        = 8; // Leads to Captain's Quarters
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Room 8 -- Captain's Quarters
    r.name            = "Captain's Quarters";
    r.description     = "It reeks in here! It smell's like someone died here. WATCH OUT!";
    r.northExit       = -1;
    r.southExit       = -1;
    r.eastExit        = -1;
    r.westExit        = -1;
    rooms.push_back(r);
    roomCleared.push_back(false);

    // Tracks current room player is in
    int currentRoom = 0;

    // We'll read the player's full command into this string
    std::string command;

    // Game Loop
    while (true) {

        // Every Turn: Show's the room and available exits
        printRoom(rooms[currentRoom]);
        printExits(rooms[currentRoom]);

        // Show the prompt and wait for input
        std::cout << "\n> ";
        std::cin >> command;

        // Command Logic
        if (command == "quit") {
            std::cout << "\nFarewell, adventurer!\n";
            break; // Exits the loop, ends the program
        }
        else if (command == "look") {
            // do nothing - the loop will reprint the room at the top
        }
        else if (command == "stats") {
            player.printStats();
        }
        else if (command == "inventory") {
            player.printInventory();
        }
        else if (command == "use") {
            std::string itemName;
            std::cin.ignore();
            std::getline(std::cin, itemName);
            player.useItem(itemName);
        }
        else if (command == "equip") {
            std::string itemName;
            std::cin.ignore();
            std::getline(std::cin, itemName);
            player.equipItem(itemName);
        }
        else if (command == "shop") {
            player.printShop();
        }
        else if (command == "map") {
            std::cout << "\n===== Maps Display =====" << std::endl;
            for (int i = 0; i < rooms.size(); i++) {
                std::cout << std::left << std::setw(12) << rooms[i].name << ": " << (roomCleared[i] ? "Cleared" : "Not Cleared") << "\n";
            }
        }
        else if (command == "save") {
            player.saveGame(currentRoom, roomCleared);
            std::cout << "Game Saved" << "\n";
        }
        else if (command == "load") {
            player.loadGame(currentRoom, roomCleared);
            std::cout << "Game Loaded" << "\n";
        }
        else if (command == "help") {
            std::cout << "\n===== Help Commands =====" << std::endl;
            std::cout << "= 'quit' ---------- Quit the Game" << std::endl;
            std::cout << "= 'look' ---------- Prints the Room Message" << std::endl;
            std::cout << "= 'stats' --------- Prints player's stats" << std::endl;
            std::cout << "= 'inventory' ----- Prints player's inventory contents" << std::endl;
            std::cout << "= 'use' ----------- Uses an item from player's inventory" << std::endl;
            std::cout << "= 'equip' --------- Equips an item from player's inventory" << std::endl;
            std::cout << "= 'shop' ---------- A shop where you can purchase items" << std::endl;
            std::cout << "= 'go' ------------ 'go' followed by a direction to enter a room" << std::endl;
            std::cout << "= 'map' ----------- See which rooms have been cleared already" << std::endl;
            std::cout << "= 'save' ---------- Saves the current game" << std::endl;
            std::cout << "= 'load' ---------- Loads the previous game" << std::endl;
            std::cout << "= 'help' ---------- Prints a list of commands available" << std::endl;
        }
        else if (command == "go") {
            // "go" needs a second word - Which Direction?
            // We read a second string from the same input line
            std::string direction;
            std::cin >> direction;

            if (direction == "north") {
                if (rooms[currentRoom].northExit != -1) {
                    currentRoom = rooms[currentRoom].northExit;
                } else {
                    std::cout << "\nThere is no exit to the NORTH.\n";
                }
            }
            else if (direction == "south") {
                if (rooms[currentRoom].southExit != -1) {
                    currentRoom = rooms[currentRoom].southExit;
                } else {
                    std::cout << "\nThere is no exit to the SOUTH.\n";
                }
            }
            else if (direction == "east") {
                if (rooms[currentRoom].eastExit != -1) {
                    currentRoom = rooms[currentRoom].eastExit;
                } else {
                    std::cout << "\nThere is no exit to the EAST.\n";
                }
            }
            else if (direction == "west") {
                if (rooms[currentRoom].westExit != -1) {
                    currentRoom = rooms[currentRoom].westExit;
                } else {
                    std::cout << "\nThere is no exit to the WEST.\n";
                }
            }
            else {
                // Catch anything we don't recognize
                std::cout << "\nUnknown direction: " << direction << "\n";
            }

            Enemy* enemy = roomEnemies[currentRoom];
            if (enemy != nullptr && !roomCleared[currentRoom]) {
                combat(player, *enemy);
                if (!player.isAlive()) break;
                if (!enemy->isAlive()) {
                    roomCleared[currentRoom] = true;
                    if (currentRoom == 8) {
                        std::cout << "You defeated the Mutant Boss! You beat the game!\n";
                        break;
                    }
                }
            }

        }
        else {
            std::cout << "\nUnknown command: \"" << command << "\"\n";
            std::cout << "Try: go [north/south/east/west], look, quit\n";
        }
    }

    return 0;

}