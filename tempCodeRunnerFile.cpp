#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

// -----------------------------------------------------------------------------------------------------------------------------------------

enum ItemType {
    WEAPON,
    ARMOR,
    CONSUMABLE
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

        std::cout << name << " [" << typeLabel << "] +" << value << "\n";
    }
};

// Player Class
class Player {

    private:
    std::string name;
    int hp;
    int maxHp;
    int attackPower;
    int baseAttack;
    int defense;
    int gold;
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
    }

};

// Enemy Class
class Enemy {

    private:
    std::string name;
    int hp;
    int attackPower;
    int goldReward;

    public:
    Enemy(std::string enemyName, int enemyHp, int enemyAttack, int reward) {
        name = enemyName;
        hp = enemyHp;
        attackPower = enemyAttack;
        goldReward = reward;
    }

    // --- TAKE DAMAGE ---
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
    std::string getName() { return name; }

};

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
            int damage = player.getAttack();
            enemy.takeDamage(damage);
            std::cout << "\nYou hit the " << enemy.getName()
                      << " for " << damage << " damage!\n";
            
            // Check if enemy died from that hit
            if (!enemy.isAlive()) {
                std::cout << "\nYou defeated the " << enemy.getName() << "!\n";
                player.addGold(enemy.getGoldReward());
                std::cout << "You earned " << enemy.getGoldReward() << " gold.\n";

                // Drop loot based on which enemy died
                if (enemy.getName() == "Goblin") {
                    Item potion("Health Potion", CONSUMABLE, 30);
                    player.addItem(potion);
                }
                if (enemy.getName() == "Skeleton") {
                    Item sword("Iron Sword", WEAPON, 10);
                    player.addItem(sword);
                    Item shield("Wooden Shield", ARMOR, 3);
                    player.addItem(shield);
                }
                break;
            }

            // Enemy hits back if still alive
            int enemyDamage = enemy.getAttack();
            player.takeDamage(enemyDamage);
            std::cout << "The " << enemy.getName()
                      << " hits you for " << enemyDamage << " damage!\n";

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



// Room Structure
// The blueprint for every room in the game
// Each room will contain these 6 pieces of data
struct Room {
    std::string name;                                                                  // Room's Display Name
    std::string description;                                                           // Room's Description
    int northExit;                                                                     // Index of room to the North      -1 = No Exit
    int southExit;                                                                     // Index of room to the South      -1 = No Exit
    int eastExit;                                                                      // Index of room to the East       -1 = No Exit
    int westExit;                                                                      // Index of room to the West       -1 = No Exit
};

// Print Room Function
// Prints the room's name and description
void printRoom(const Room& room) {
    std::cout << "\n=============================\n";
    std::cout << " " << room.name;
    std::cout << "\n=============================\n";
    std::cout << room.description << "\n";
}

// Print Exit Function
// Looks at current room's exits and tells
// the player which directions are available
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
    // Creating an Array of 6 room structures
    // rooms[6] means "give me 6 Room-shaped slots in memory"
    Room rooms[6];

    // Room 0 -- Entrance
    rooms[0].name            = "Entrance";
    rooms[0].description     = "You wake up on a cold stone floor. The air smells\nof damp and decay. A corridor stretches to the NORTH.";
    rooms[0].northExit       = 1; // Leads to Corridor
    rooms[0].southExit       = -1;
    rooms[0].eastExit        = -1;
    rooms[0].westExit        = -1;

    // Room 1 -- Corridor
    rooms[1].name            = "Corridor";
    rooms[1].description     = "A long corridor with cracked stone walls.\nTorches flicker. Paths lead SOUTH, EAST, and WEST.";
    rooms[1].northExit       = -1;
    rooms[1].southExit       = 0; // Back to Entrance
    rooms[1].eastExit        = 3; // Leads to Library
    rooms[1].westExit        = 2; // Leads to Armory

    // Room 2 -- Armory
    rooms[2].name            = "Armory";
    rooms[2].description     = "Broken weapon racks line the walls. Most have been\nlooted. Exits: EAST back to corridor, SOUTH into darkness.";
    rooms[2].northExit       = -1;
    rooms[2].southExit       = 4;  // Leads to Dark Hall
    rooms[2].eastExit        = 1;  // Leads back to Corridor
    rooms[2].westExit        = -1; 

    // Room 3 -- Library
    rooms[3].name            = "Library";
    rooms[3].description     = "Dusty bookshelves tower over you. A faint glow\ncomes from the pages. Exit to the WEST.";
    rooms[3].northExit       = -1;
    rooms[3].southExit       = -1; 
    rooms[3].eastExit        = -1; 
    rooms[3].westExit        = 1; // Leads back to Corridor

    // Room 4 -- Dark Hall
    rooms[4].name            = "Dark Hall";
    rooms[4].description     = "You can barely see your hand in front of your face.\nSomething skitters in the darkness. Exit NORTH.";
    rooms[4].northExit       = 2; // Leads back to Corridor
    rooms[4].southExit       = 5; // Leads to Boss Door
    rooms[4].eastExit        = -1; 
    rooms[4].westExit        = -1; 

    // Room 5 -- Boss Door
    rooms[5].name            = "Boss Door";
    rooms[5].description     = "A massive iron door stands before you, covered in\nscorch marks. You hear breathing on the other side.";
    rooms[5].northExit       = 4; // Leads back to Dark Hall
    rooms[5].southExit       = -1; 
    rooms[5].eastExit        = -1; 
    rooms[5].westExit        = -1; 

    // Tracks current room player is in
    int currentRoom = 0;

    // We'll read the player's full command into this string
    std::string command;

    // Logic for if rooms have been cleared or not of enemies
    bool roomCleared[6] = {false, false, false, false, false, false};

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
            std::cin >> itemName;
            player.useItem(itemName);
        }
        else if (command == "equip") {
            std::string itemName;
            std::cin >> itemName;
            player.equipItem(itemName);
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

            if (currentRoom == 2 && !roomCleared[2]) {
                Enemy goblin("Goblin", 30, 8, 10);
                combat(player, goblin);
                if (!player.isAlive()) break;
                if (!goblin.isAlive()) {
                    roomCleared[2] = true; // Marks the room cleared AFTER combat
                }
            }
            if (currentRoom == 4 && !roomCleared[4]) {
                Enemy skeleton("Skeleton", 50, 12, 20);
                combat(player, skeleton);
                if (!player.isAlive()) break;
                if (!skeleton.isAlive()) {
                    roomCleared[4] = true; // Marks the room cleared AFTER combat
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