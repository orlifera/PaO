#include "../headers/pressure.h"

PressureSensor::PressureSensor(string n, double pressure, double th) : Sensor(n, pressure, th) {}

string PressureSensor::getIcon() const { return "pressure.png"; }

string PressureSensor::getUnit() const { return "Pressure (atm)"; }