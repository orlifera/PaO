#pragma once
#include "sensor.h"
class TemperatureSensor : public Sensor {
    private:
    const bool contact;
    public: 
    TemperatureSensor(string, vector<Data>, bool, double, double =0);
    bool isContact() const;
};