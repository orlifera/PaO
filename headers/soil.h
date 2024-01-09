#pragma once
#include "humidity.h"
class SoilHumiditySensor : public HumiditySensor {
    public:
    SoilHumiditySensor(string, vector<Data>, double, double =0);
};