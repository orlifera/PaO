#pragma once
#include "humidity.h"
//sensore per l'umidità dell'aria derivato da un sensore per l'umidità generico
class AirHumiditySensor : public HumiditySensor {
    private:
    static double alpha; //parametro per la distribuzione beta
    static double beta;  //parametro per la distribuzione beta
    public:
    AirHumiditySensor(string, vector<Data>, double, double =0);
    void generate() override;
    //funzione statica che crea distribuzione beta
    static double beta_distribution(double, double, default_random_engine&);
};