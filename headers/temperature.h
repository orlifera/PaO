#pragma once
#include "sensor.h"
class TemperatureSensor : public Sensor {
    private:
    const bool contact; //chiedere
    double temp;
    public: 
    TemperatureSensor(string, vector<Data>, bool, double);
    bool isContact() const;
    double getTemp() const;
    void setTemp(double); 
};