#pragma once
#include "temperature.h"
//sensore di temperatura del mosto derivato da sensore di temperatura generico
class MustTemperatureSensor : public TemperatureSensor {
    private:
    double timer;               //timer di femrentazione
    static double stdDeviation; //deviazione standard
    public:
    MustTemperatureSensor(string, vector<Data>, double, double =0);
    void generate() override;
};