#pragma once
#include "time.h"
//dato di misurazione di un sensore
class Data {
    private:
    double value;   //valore dato
    Time time;      //orario nella quale viene misurato
    public:
    Data(double, Time);
    double getValue() const;   //ritorna il valore del dato
    void setValue(double);     //assegna un nuovo valore (misurazione)
    Time getTime() const;      //ritorna l'orario
    void setTime(unsigned int =0, unsigned int =0, unsigned int =0); //assegna l'orario
};