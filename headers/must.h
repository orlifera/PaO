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
    // ritorna il valore del timer
    double getTimer() const; 
    // imposta il valore del timer
    void setTimer(double);   
    QJsonObject classSensor() const;
    void accept(SensorVisitor &);
};