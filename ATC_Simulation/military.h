#ifndef MILITARY_H
#define MILITARY_H


#include <string>
#include <iostream>
#include "aircraft.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Parent class for all Military Aircraft
class MilitaryAircraft : public Aircraft {

    private:
        int missileCount;
        std::string weaponSystem1;
        std::string weaponSystem2;

    public:
        MilitaryAircraft(std::string model, std::string cs, AircraftStatus stat, int alt, double spd, double weight, double wingspan, double height, int passengers, int missiles, std::string weapon1, std::string weapon2) : Aircraft(model, cs, stat, alt, spd, weight, wingspan, height, passengers) {
            missileCount = missiles;
            weaponSystem1 = weapon1;
            weaponSystem2 = weapon2;
        }
        void emergencyProtocol() override {}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class F22Raptor : public MilitaryAircraft {

    public:
        F22Raptor(std::string cs) : MilitaryAircraft("F-22 Raptor", cs, GROUNDED, 0, 0.0, 83776, 44.49, 16.67, 1, 6, "AIM-120 AMRAAM", "AIM-9 Sidewinder") {}

        void emergencyProtocol() override {
            std::cout << "\n[F-22 - " << getCallSign() << "] Stealth mode activated. Diverting to nearest Air Force base.\n";
        }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class EurofighterTyphoon : public MilitaryAircraft {

    public:
        EurofighterTyphoon(std::string cs) : MilitaryAircraft("Eurofighter Typhoon", cs, GROUNDED, 0, 0.0, 51809, 35.93, 17.32, 1, 4, "MBDA Meteor", "AIM-9 Sidewinder") {}
        
        void emergencyProtocol() override {
            std::cout << "\n[Typhoon - " << getCallSign() << "] Stealth mode activated. Diverting to nearest Air Force base.\n";
        }
};

#endif