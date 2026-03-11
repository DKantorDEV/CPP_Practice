#ifndef COMMERCIAL_H
#define COMMERCIAL_H


#include <string>
#include <iostream>
#include "aircraft.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Parent class for all Commercial Aircraft
class CommercialAircraft : public Aircraft {

    private:
        std::string airline;
        std::string flightNumber;

    public:
        CommercialAircraft(std::string model, std::string cs, AircraftStatus stat, int alt, double spd, double weight, double wingspan, double height, int passengers, std::string al, std::string fn) : Aircraft(model, cs, stat, alt, spd, weight, wingspan, height, passengers) {
            airline = al;
            flightNumber = fn;
        }
        void emergencyProtocol() override {}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class AirbusA350 : public CommercialAircraft {

    public:
        AirbusA350(std::string cs) : CommercialAircraft("Airbus A350-1000", cs, GROUNDED, 0, 0.0, 703274, 212.43, 56.04, 369, "Airbus", "SV-001") {}

        void emergencyProtocol() override {
            std::cout << "\n[Airbus - " << getCallSign() << "] Dumping fuel and re-directing to nearest landing strip.\n";
        }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------

class Dreamliner787 : public CommercialAircraft {

    public:
        Dreamliner787(std::string cs) : CommercialAircraft("Boeing 787-9 Dreamliner", cs, GROUNDED, 0, 0.0, 559998, 197.41, 55.84, 296, "Boeing", "BN-787") {}
        
        void emergencyProtocol() override {
            std::cout << "\n[Dreamliner - " << getCallSign() << "] Dumping fuel and re-directing to nearest landing strip.\n";
        }
};

#endif