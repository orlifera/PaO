#pragma once
#include "pressure.h"
//sensore per la pressione in una botte derivato da sensore per la pressione generico
class BarrelSensor : public PressureSensor {
    private:
    static double stdDeviation;    //deviazione standard
    public:
    BarrelSensor(string, vector<Data>, double, double =0);
    void generate() override;
};