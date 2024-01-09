#include "../headers/soil.h"

SoilHumiditySensor::SoilHumiditySensor(string n, vector<Data> v, double h) : HumiditySensor(n, v, false, h) {}
int SoilHumiditySensor::isInThreshold() const
{
    double last = getInfo(getArray().size() - 1).getValue();
    if (last > soilThreshold + getHumidity())
        return 1;
    else if (last < getHumidity() - soilThreshold)
        return -1;
    else
        return 0;
}
double SoilHumiditySensor::soilThreshold = 0;