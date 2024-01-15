#pragma once
#include "pressure.h"
//sensore per la pressione in una botte derivato da sensore per la pressione generico
class BarrelPressureSensor : public PressureSensor {
    private:
    static double stdDeviation;    //deviazione standard
    public:
    BarrelPressureSensor(string, double, double =0);
    void generate() override;
    string classSensor() const override;
};