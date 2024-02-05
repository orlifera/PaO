#pragma once
#include "temperature.h"
//sensore di temperatura del mosto derivato da sensore di temperatura generico
class MustTemperatureSensor : public TemperatureSensor {
    private:
    double timer;        //timer di fermentazione
    static double range; //deviazione standard
    public:
    MustTemperatureSensor(string, double, double, double =0);
    void generate() override;
    QJsonObject classSensor() const override;
};