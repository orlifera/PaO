#pragma once
#include "sensor.h"
class PressureSensor : public Sensor {
    public:
    PressureSensor(string, vector<Data>, double, double);
};