#pragma once
#include "temperature.h"
//sensore per la temperatura della cantina derivato da sensore per la temperatura generico
class WineryTemperatureSensor : public TemperatureSensor {
    private:
    static double stdDeviation; //deviazione standard
    public:
    WineryTemperatureSensor(string, vector<Data>, double, double =0);
    void generate() override;
};