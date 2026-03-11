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
        Helicopter(std::string model, std::string cs, AircraftStatus stat, int alt, int calt, double spd, double cspd, double weight, double wingspan, double height, int passengers, double rdiameter) : Aircraft(model, cs, stat, alt, calt, spd, cspd, weight, wingspan, height, passengers) {
            rotorDiameter = rdiameter;
        }
        void emergencyProtocol() override {}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class Apache : public Helicopter {

    public:
        Apache(std::string cs, AircraftStatus stat) : Helicopter("Apache AH-64", cs, stat, 0, 21000, 0.0, 165, 23001, 14.63, 3.87, 2, 14.63) {}

        void emergencyProtocol() override {
            std::cout << "\n[Apache - " << getCallSign() << "] Maintaining low altitude and re-directing to nearest landing site pad.\n";
        }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class KingStallion : public Helicopter {

    public:
        KingStallion(std::string cs, AircraftStatus stat) : Helicopter("Sikorsky CH-53K", cs, stat, 0, 16200, 0.0, 196, 88000, 30.18, 8.46, 4, 24.08) {}
        
        void emergencyProtocol() override {
            std::cout << "\n[King Stallion - " << getCallSign() << "] Maintaining low altitude and re-directing to nearest landing site pad.\n";
        }
};

#endif