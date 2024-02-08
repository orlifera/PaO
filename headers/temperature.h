#pragma once
#include "sensor.h"
// sensore di temperatura generico derivato da sensore generico
class TemperatureSensor : public Sensor
{
private:
    const bool contact; // tipologia di sensore di temperatura (costante e definito alla creazione)
public:
    TemperatureSensor(string, bool, double, double);
    bool isContact() const; // check se il sensore è a contatto o meno
    string getIcon() const;
};