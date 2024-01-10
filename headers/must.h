#pragma once
#include "temperature.h"
class MustTemperatureSensor : public TemperatureSensor {
    public:
    MustTemperatureSensor(string, vector<Data>, double, double =0);
};