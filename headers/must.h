#pragma once
#include "include.h"
class MustTemperatureSensor : public TemperatureSensor {
    private:
    static double mustThreshold;
    public:
    MustTemperatureSensor(string, vector<Data>, double);
    int isInThreshold() const override;
};