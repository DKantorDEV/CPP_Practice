#ifndef CARGO_H
#define CARGO_H


#include <string>
#include <iostream>
#include "aircraft.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Parent class for all Cargo Aircraft
class CargoAircraft : public Aircraft {

    private:
        std::string specialCargo;

    public:
        CargoAircraft(std::string model, std::string cs, AircraftStatus stat, int alt, int calt, double spd, double cspd, double weight, double wingspan, double height, int passengers, std::string cargo) : Aircraft(model, cs, stat, alt, calt, spd, cspd, weight, wingspan, height, passengers) {
            specialCargo = cargo;
        }
        void emergencyProtocol() override {}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class SuperGalaxyC5M : public CargoAircraft {

    public:
        SuperGalaxyC5M(std::string cs, AircraftStatus stat) : CargoAircraft("C-5M Super Galaxy", cs, stat, 0, 41000, 0.0, 518, 840000, 222.74, 65.09, 6, "Military Equipment") {}

        void emergencyProtocol() override {
            std::cout << "\n[C-5M - " << getCallSign() << "] Bailing all Cargo. Diverting to nearest Landing Site.\n";
        }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class Freighter747 : public CargoAircraft {

    public:
        Freighter747(std::string cs, AircraftStatus stat) : CargoAircraft("747-8 Freighter", cs, stat, 0, 43000, 0.0, 564, 987008, 224.41, 63.65, 4, "General Freight") {}
        
        void emergencyProtocol() override {
            std::cout << "\n[747-8 - " << getCallSign() << "] Bailing all Cargo. Diverting to nearest Landing Site.\n";
        }
};

#endif