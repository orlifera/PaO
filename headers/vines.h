#pragma once
#include "temperature.h"
//sensore per la temperatura nelle vigne derivato da sensore per la temperatura generico
class VinesTemperatureSensor : public TemperatureSensor {
    private:
    static double stdDeviation; //deviazione standard
    static double amplitude;    //ampiezza per la distribuzione sinusoidale
    public:
    VinesTemperatureSensor(string, double, double =0);
    void generate() override;
    QJsonObject classSensor() const override;
};