#include "../headers/humidity.h"

HumiditySensor::HumiditySensor(string n, vector<Data> v, bool c, double humidity, double th) : Sensor(n, v, humidity, th), capacity(c) {}
bool HumiditySensor::isCapacity() const { return capacity; }