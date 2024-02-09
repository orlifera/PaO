#pragma once
#include "sensor.h"
// sensore di umidità generico derivato da sensore generico
class HumiditySensor : public Sensor
{
private:
    const bool capacity; // tipologia di sensore (costante e definito alla creazione)
public:
    HumiditySensor(string, bool, double, double);
    bool isCapacity() const; // check se sensore è capacitativo o meno
    string getIcon() const;
    string getUnit() const;
};