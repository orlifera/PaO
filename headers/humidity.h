#pragma once
#include "sensor.h"
class HumiditySensor : public Sensor {
    private:
    const bool capacity;
    public:
    HumiditySensor(string, vector<Data>, bool, double, double =0);
    bool isCapacity() const;
};