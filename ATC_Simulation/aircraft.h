#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <iostream>

// -----------------------------------------------------------------------------------

enum AircraftStatus {
    GROUNDED,
    TAKEOFF,
    AIRBORNE,
    LANDING,
    EMERGENCY
};

class Aircraft {

    private:
        std::string aircraftModel;
        std::string callSign;
        AircraftStatus status;
        int altitude;
        double speed;
        double aircraftWeight;
        double aircraftWingspan;
        double aircraftHeight;
        int currentPassengers;

    public:
        Aircraft(std::string model, std::string cs, AircraftStatus stat, int alt, double spd, double weight, double wingspan, double height, int passengers) {
            aircraftModel = model;
            callSign = cs;
            status = stat;
            altitude = alt;
            speed = spd;
            aircraftWeight = weight;
            aircraftWingspan = wingspan;
            aircraftHeight = height;
            currentPassengers = passengers; 
        }
    
    // --- GETTERS ---
    std::string getModel() { return aircraftModel; }
    std::string getCallSign() { return callSign; }
    AircraftStatus getStatus() { return status; }
    int getAltitude() { return altitude; }
    double getSpeed() { return speed; }
    double getWeight() { return aircraftWeight; }
    double getWingspan() { return aircraftWingspan; }
    double getHeight() { return aircraftHeight; }
    int getPassengers() { return currentPassengers; }

    // --- SETTERS ---
    void setStatus(AircraftStatus s) { status = s; }

    // --- EMERGENCY PROTOCOL --- 
    virtual void emergencyProtocol() {}

    // --- PRINT INFO ---
    void printInfo() {
        std::cout << "\n--- " << aircraftModel << "'s Information ---\n";
        std:: cout << "\nCall Sign:----" << callSign;
        std:: cout << "\nAltitude:-----" << altitude;
        std:: cout << "\nSpeed:--------" << speed;
        std:: cout << "\nWeight:-------" << aircraftWeight;
        std:: cout << "\nWingspan:-----" << aircraftWingspan;
        std:: cout << "\nHeight:-------" << aircraftHeight;
        std:: cout << "\nPassengers:---" << currentPassengers;
        std:: cout << "\nStatus:-------" << status;
    }
};

#endif