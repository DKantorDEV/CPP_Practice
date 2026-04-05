#include <iostream>

class Sensor {
    private:
        std::string name;

    public:
        Sensor(std::string sensorName) {
            name = sensorName;
        }
        virtual ~Sensor() {
            std::cout << "Sensor: " << name << " is offline." << std::endl;
        }
    virtual void report() {
        std::cout << "Sensor: " << name << std::endl;
    }

    std::string getName() {
        return name;
    }
};

class TemperatureSensor : public Sensor {
    private:
        double temperature;

    public:
        TemperatureSensor(std::string sensorName, double temp) : Sensor(sensorName) {
            temperature = temp;
        }
        void report() override {
            std::cout << "Sensor: " << getName() << std::endl;
            std::cout << "Temp: " << temperature << std::endl;
        }
};

class PressureSensor : public Sensor {
    private:
        double pressure;
    
    public:
        PressureSensor(std::string sensorName, double psi) : Sensor(sensorName) {
            pressure = psi;
        }
        void report() override {
            std::cout << "Sensor: " << getName() << std::endl;
            std::cout << "Pressure: " << pressure << std::endl;
        }
};

int main() {

    Sensor* sensors[2];
    sensors[0] = new TemperatureSensor("Engine", 350.5);
    sensors[1] = new PressureSensor("Fuel Line", 14.7);

    for (int i = 0; i < 2; i++) {
        sensors[i]->report();
    }

    delete sensors[0];
    delete sensors[1];
}