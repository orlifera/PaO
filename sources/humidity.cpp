#include "../headers/humidity.h"

HumiditySensor::HumiditySensor(string n, bool c, double humidity, double th) : Sensor(n, humidity, th), capacity(c) {}
bool HumiditySensor::isCapacity() const { return capacity; }
string HumiditySensor::getIcon() const { return "humidity.png"; }
