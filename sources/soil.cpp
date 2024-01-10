#include "../headers/soil.h"

SoilHumiditySensor::SoilHumiditySensor(string n, vector<Data> v, double humidity, double th) : HumiditySensor(n, v, false, humidity, th) {}