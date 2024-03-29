#pragma once
#include "humidity.h"

// sensore per l'umidità del terreno derivato da sensore per l'umidità generico
class SoilHumiditySensor : public HumiditySensor
{
private:
    static double stdDeviation; // logaritmo della deviazione standard
public:
    SoilHumiditySensor(string, double, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};