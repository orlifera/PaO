#pragma once
#include "pressure.h"
class BarrelSensor : public PressureSensor {
    public:
    BarrelSensor(string, vector<Data>, double, double =0);
};