#include "aircraft.h"
#include "commercial.h"
#include "military.h"
#include "cargo.h"
#include "helicopter.h"

#include <string>
#include <iostream>
#include <vector>

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () {

    // Aircraft tracked by tower
    std::vector<Aircraft*> tower;

    // Add each aircraft to the tower
    tower.push_back(new AirbusA350("Airbus A350-1000"));
    tower.push_back(new Dreamliner787("Boeing 787-9 Dreamliner"));
    tower.push_back(new F22Raptor("F-22 Raptor"));
    tower.push_back(new EurofighterTyphoon("Eurofighter Typhoon"));
    tower.push_back(new SuperGalaxyC5M("C-5M Super Galaxy"));
    tower.push_back(new Freighter747("747-8 Freighter"));
    tower.push_back(new Apache("Apache AH-64"));
    tower.push_back(new KingStallion("Sikorsky CH-53K"));

    return 0;

}