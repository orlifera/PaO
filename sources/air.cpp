#include "../headers/air.h"

AirHumiditySensor::AirHumiditySensor(string n, vector<Data> v, double humidity, double th) : HumiditySensor(n, v, true, humidity, th) {}