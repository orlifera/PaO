#include "../headers/temperature.h"

TemperatureSensor::TemperatureSensor(string n, bool c, double temp, double th) : Sensor(n, temp, th), contact(c) {}
bool TemperatureSensor::isContact() const { return contact; }