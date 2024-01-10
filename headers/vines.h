#pragma once
#include "temperature.h"
class VinesTemperatureSensor : public TemperatureSensor {
    public:
    VinesTemperatureSensor(string, vector<Data>, double, double =0);
};