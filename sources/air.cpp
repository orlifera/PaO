#include "../headers/include.h"
#include "../headers/air.h"

AirHumiditySensor::AirHumiditySensor(string n, vector<Data> v, double h) : HumiditySensor(n, v, true, h) {}
int AirHumiditySensor::isInThreshold() const
{
    double last = getInfo(getArray().size() - 1).getValue();
    if (last > airThreshold + getHumidity())
        return 1;
    else if (last < getHumidity() - airThreshold)
        return -1;
    else
        return 0;
}
double AirHumiditySensor::airThreshold = 0;