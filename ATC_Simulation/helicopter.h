#ifndef HELICOPTER_H
#define HELICOPTER_H


#include <string>
#include <iostream>
#include "aircraft.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Parent class for all Helicopters
class Helicopter : public Aircraft {

    private:
        double rotorDiameter;

    public:
        Helicopter(std::string model, std::string cs, AircraftStatus stat, int alt, double spd, double weight, double wingspan, double height, int passengers, double rdiameter) : Aircraft(model, cs, stat, alt, spd, weight, wingspan, height, passengers) {
            rotorDiameter = rdiameter;
        }
        void emergencyProtocol() override {}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class Apache : public Helicopter {

    public:
        Apache(std::string cs) : Helicopter("Apache AH-64", cs, GROUNDED, 0, 0.0, 23001, 14.63, 3.87, 2, 14.63) {}

        void emergencyProtocol() override {
            std::cout << "\n[Apache - " << getCallSign() << "] Maintaining low altitude and re-directing to nearest landing site pad.\n";
        }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class KingStallion : public Helicopter {

    public:
        KingStallion(std::string cs) : Helicopter("Sikorsky CH-53K", cs, GROUNDED, 0, 0.0, 88000, 30.18, 8.46, 4, 24.08) {}
        
        void emergencyProtocol() override {
            std::cout << "\n[King Stallion - " << getCallSign() << "] Maintaining low altitude and re-directing to nearest landing site pad.\n";
        }
};

#endif