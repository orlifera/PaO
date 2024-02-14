#pragma once
#include "pressure.h"

// sensore per la pressione atmosferica derivato da sensore per la pressione generico
class AtmPressureSensor : public PressureSensor
{
private:
    static double stdDeviation; // deviazione standard
    static double meanPoisson;  // numero medio di eventi improvvisi per unità di tempo
public:
    AtmPressureSensor(string, double = 0);
    void generate();
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};