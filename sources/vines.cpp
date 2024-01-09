#include "../headers/include.h"
#include "../headers/vines.h"

VinesTemperatureSensor::VinesTemperatureSensor(string n, vector<Data> v, double t) : TemperatureSensor(n, v, false, t) {}
int VinesTemperatureSensor::isInThreshold() const
{
    double last = getInfo(getArray().size() - 1).getValue();
    if (last > vineThreshold + getTemp())
        return 1;
    else if (last < getTemp() - vineThreshold)
        return -1;
    else
        return 0;
}
double VinesTemperatureSensor::vineThreshold = 0;