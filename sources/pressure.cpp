#include "include.h"

PressureSensor::PressureSensor(string n, vector<Data> v, double p) : Sensor(n,v), pressure(p) {}
double PressureSensor::getPressure() const { return pressure; }
void PressureSensor::setPressure(double p) { pressure = p; }