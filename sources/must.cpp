#include "../headers/must.h"

MustTemperatureSensor::MustTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, true, temp, th) {}