#pragma once
#include "humidity.h"
class SoilHumiditySensor : public HumiditySensor {
    private:
    static double soilThreshold;
    public:
    SoilHumiditySensor(string, vector<Data>, double);
    int isInThreshold() const override;
};