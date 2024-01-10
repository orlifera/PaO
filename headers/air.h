#pragma once
#include "include.h"
class AirHumiditySensor : public HumiditySensor
{
private:
    static double airThreshold;

public:
    AirHumiditySensor(string, vector<Data>, double);
    int isInThreshold() const override;
};