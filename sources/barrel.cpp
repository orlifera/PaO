#include "include.h"

int BarrelSensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > barrelThreshold+getPressure()) return 1;
    else if (last < getPressure()-barrelThreshold) return -1;
    else return 0;
}
double BarrelSensor::barrelThreshold = 0;