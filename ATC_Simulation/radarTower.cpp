#include "aircraft.h"
#include "commercial.h"
#include "military.h"
#include "cargo.h"
#include "helicopter.h"

#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () {

    // Aircraft tracked by tower
    std::vector<Aircraft*> tower;

    // Add each aircraft to the tower
    tower.push_back(new AirbusA350("Airbus A350-1000", TAKEOFF));
    tower.push_back(new Dreamliner787("Boeing 787-9 Dreamliner", TAKEOFF));
    tower.push_back(new F22Raptor("F-22 Raptor", GROUNDED));
    tower.push_back(new EurofighterTyphoon("Eurofighter Typhoon", AIRBORNE));
    tower.push_back(new SuperGalaxyC5M("C-5M Super Galaxy", GROUNDED));
    tower.push_back(new Freighter747("747-8 Freighter", EMERGENCY));
    tower.push_back(new Apache("Apache AH-64", TAKEOFF));
    tower.push_back(new KingStallion("Sikorsky CH-53K", LANDING));

    while (true) {

        // --- Update Aicraft's Info ---
        for (int i = 0; i < tower.size(); i++) {
            tower[i]->update();
        }

        // --- Prints the Aircraft's Info ---
        for (int j = 0; j < tower.size(); j++) {
            tower[j]->printInfo();
        }

        

    }

    return 0;

}