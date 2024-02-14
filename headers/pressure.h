#pragma once
#include "sensor.h"

// sensore di pressione generico derivato da sensore generico
class PressureSensor : public Sensor
{
public:
    PressureSensor(string, double, double);
    string getIcon() const;
    string getUnit() const;
};