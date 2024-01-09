#include "../headers/temperature.h"

TemperatureSensor::TemperatureSensor(string n, vector<Data> v, bool c, double temp, double th) : Sensor(n, v, temp, th), contact(c) {}
bool TemperatureSensor::isContact() const { return contact; }