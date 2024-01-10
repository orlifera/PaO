#include "../headers/winery.h"

WineryTemperatureSensor::WineryTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, false, temp, th) {}