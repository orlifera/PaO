#include "../headers/temperature.h"

TemperatureSensor::TemperatureSensor(string n, vector<Data> v, bool c, double t) : Sensor(n, v), contact(c), temp(t) {}
bool TemperatureSensor::isContact() const { return contact; }
double TemperatureSensor::getTemp() const { return temp; }
void TemperatureSensor::setTemp(double t) { temp = t; }