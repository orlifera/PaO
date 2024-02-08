#pragma once
#include "temperature.h"
// sensore di temperatura del mosto derivato da sensore di temperatura generico
class MustTemperatureSensor : public TemperatureSensor
{
private:
    static double timer; // timer di fermentazione
    static double range; // deviazione standard
public:
    MustTemperatureSensor(string, double, double);
    void generate();
    void setTimer(double);
    QJsonObject classSensor() const;
};