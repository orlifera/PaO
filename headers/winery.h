#pragma once
#include "temperature.h"

// sensore per la temperatura della cantina derivato da sensore per la temperatura generico
class WineryTemperatureSensor : public TemperatureSensor
{
private:
    static double range; // deviazione standard
public:
    WineryTemperatureSensor(string, double, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};