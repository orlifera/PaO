#pragma once
#include "sensor.h"
class PressureSensor : public Sensor {
    private:
    double pressure;
    public:
    PressureSensor(string, vector<Data>, double);
    double getPressure() const;
    void setPressure(double);
};