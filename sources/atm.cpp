#include "../headers/atm.h"

AtmPressureSensor::AtmPressureSensor(string n, vector<Data> v, double th) : PressureSensor(n, v, 1.0, th) {}