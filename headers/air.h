#pragma once
#include "humidity.h"
class AirHumiditySensor : public HumiditySensor
{
public:
    AirHumiditySensor(string, vector<Data>, double, double = 0);
};