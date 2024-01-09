#include "../headers/include.h"
#include "../headers/humidity.h"

HumiditySensor::HumiditySensor(string n, vector<Data> v, bool c, double h) : Sensor(n, v), capacity(c), humidity(h) {}
bool HumiditySensor::isCapacity() const { return capacity; }
double HumiditySensor::getHumidity() const { return humidity; }
void HumiditySensor::setHumidity(double h) { humidity = h; }