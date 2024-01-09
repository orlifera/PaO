#pragma once
#include "sensor.h"
class HumiditySensor : public Sensor {
    private:
    const bool capacity;
    double humidity;
    public:
    HumiditySensor(string, vector<Data>, bool, double);
    bool isCapacity() const;
    double getHumidity() const;
    void setHumidity(double);
};