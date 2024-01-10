#pragma once
#include "temperature.h"
class WineryTemperatureSensor : public TemperatureSensor {
    public:
    WineryTemperatureSensor(string, vector<Data>, double, double =0);
};