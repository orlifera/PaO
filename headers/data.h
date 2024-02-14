#pragma once
#include "time.h"

// dato di misurazione di un sensore
class Data
{
private:
    double value; // valore dato
    Time time;    // orario nella quale viene misurato
public:
    Data(double = 0.0, Time = 0);
    // ritorna il valore del dato
    double getValue() const;
    // assegna un nuovo valore (misurazione)
    void setValue(double);
    // ritorna l'orario  in secondi come stringa
    int getTime() const;
    // assegna l'orario
    void setTime(unsigned int = 0, unsigned int = 0, unsigned int = 0);
};