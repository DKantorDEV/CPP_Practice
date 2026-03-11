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
        int cruisingAltitude;
        double speed;
        double cruisingSpeed;
        double aircraftWeight;
        double aircraftWingspan;
        double aircraftHeight;
        int currentPassengers;

    public:
        Aircraft(std::string model, std::string cs, AircraftStatus stat, int alt, int calt, double spd, double cspd, double weight, double wingspan, double height, int passengers) {
            aircraftModel = model;
            callSign = cs;
            status = stat;
            altitude = alt;
            cruisingAltitude = calt;
            speed = spd;
            cruisingSpeed = cspd;
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
    int getCruisingAltitude() { return cruisingAltitude;}
    double getSpeed() { return speed; }
    double getCruisingSpeed() { return cruisingSpeed; }
    double getWeight() { return aircraftWeight; }
    double getWingspan() { return aircraftWingspan; }
    double getHeight() { return aircraftHeight; }
    int getPassengers() { return currentPassengers; }

    // --- SETTERS ---
    void setStatus(AircraftStatus s) { status = s; }
    void setAltitude(int alt) { altitude = alt; }
    void setSpeed(double spd) { speed = spd; }

    // --- EMERGENCY PROTOCOL --- 
    virtual void emergencyProtocol() {}

    // --- PRINT INFO ---
    void printInfo() {
        std::cout << "\n--- " << aircraftModel << "'s Information ---";
        std:: cout << "\nCall Sign:----" << callSign;
        std:: cout << "\nAltitude:-----" << altitude << " ft";
        std:: cout << "\nSpeed:--------" << speed << " mph";
        std:: cout << "\nWeight:-------" << aircraftWeight << " lbs";
        std:: cout << "\nWingspan:-----" << aircraftWingspan << " ft";
        std:: cout << "\nHeight:-------" << aircraftHeight << " ft";
        std:: cout << "\nPassengers:---" << currentPassengers;
        std:: cout << "\nStatus:-------" << statusToString() << "\n";
    }

    // --- UPDATES PLANE INFO ---
    void update() {
        switch(status) {
            case GROUNDED:
                altitude = 0;
                speed += 0;
                break;
            case TAKEOFF:
                altitude += 200;
                speed += 70;
                if (altitude > cruisingAltitude) altitude = cruisingAltitude;
                if (speed > cruisingSpeed) speed = cruisingSpeed;
                if (altitude >= cruisingAltitude && speed >= cruisingSpeed) { setStatus(AIRBORNE); }
                break;
            case AIRBORNE:
                altitude = cruisingAltitude;
                speed = cruisingSpeed;
                break;
            case LANDING:
                altitude -= 200;
                speed -= 20;
                if (altitude <= 0 || speed <= 0) { speed = 0, altitude = 0; setStatus(GROUNDED); }
                break;
            case EMERGENCY:
                altitude -= 200;
                speed -= 30;
                if (altitude <= 0 || speed <= 0) { speed = 0; altitude = 0; setStatus(GROUNDED); }
                break;
        }
    }

    // Prints correct status from ENUM
    std::string statusToString() {
        if (status == GROUNDED) return "GROUNDED";
        if (status == TAKEOFF) return "TAKEOFF";
        if (status == AIRBORNE) return "AIRBORNE";
        if (status == LANDING) return "LANDING";
        if (status == EMERGENCY) return "EMERGENCY";
        return "UNKNOWN";
    };

};

#endif