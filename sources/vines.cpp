#include "../headers/vines.h"

VinesTemperatureSensor::VinesTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, false, temp, th) {}