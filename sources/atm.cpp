#include "../headers/include.h"
#include "../headers/atm.h"

AtmPressureSensor::AtmPressureSensor(string n, vector<Data> v) : PressureSensor(n, v, 1.0) {}
int AtmPressureSensor::isInThreshold() const
{
    double last = getInfo(getArray().size() - 1).getValue();
    if (last > atmThreshold + getPressure())
        return 1;
    else if (last < getPressure() - atmThreshold)
        return -1;
    else
        return 0;
}
double AtmPressureSensor::atmThreshold = 0;