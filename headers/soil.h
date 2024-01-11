#pragma once
#include "humidity.h"
//sensore per l'umidità del terreno derivato da sensore per l'umidità generico
class SoilHumiditySensor : public HumiditySensor {
    private:
    static double logStdDeviation; //logaritmo della deviazione standard
    public:
    SoilHumiditySensor(string, vector<Data>, double, double =0);
    void generate() override;
};