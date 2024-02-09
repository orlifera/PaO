#pragma once
#include "sensor.h"
class PressureSensor : public Sensor
{
public:
    PressureSensor(string, double, double);
    string getIcon() const;
    string getUnit() const;
};