#include "../headers/must.h"

MustTemperatureSensor::MustTemperatureSensor(string n, vector<Data> v, double t) : TemperatureSensor(n, v, true, t) {}
int MustTemperatureSensor::isInThreshold() const
{
    double last = getInfo(getArray().size() - 1).getValue();
    if (last > mustThreshold + getTemp())
        return 1;
    else if (last < getTemp() - mustThreshold)
        return -1;
    else
        return 0;
}
double MustTemperatureSensor::mustThreshold = 0;