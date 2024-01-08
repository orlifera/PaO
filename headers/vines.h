#pragma once
#include "include.h"
class VinesTemperatureSensor : public TemperatureSensor {
    private:
    static double vineThreshold;
    public:
    VinesTemperatureSensor(string, vector<Data>, double);
    int isInThreshold() const override;
};