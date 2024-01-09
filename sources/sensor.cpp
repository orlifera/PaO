#include "../headers/include.h"
#include "../headers/sensor.h"

Sensor::Sensor(string n, vector<Data> v) : name(n), infoArray(v) {}
string Sensor::getName() const { return name; }
vector<Data> Sensor::getArray() const { return infoArray; }
Data Sensor::getInfo(int i) const { return infoArray[i]; }
void Sensor::addData(Data d) { infoArray.push_back(d); }
void Sensor::removeData() { infoArray.pop_back(); }
void Sensor::renameSensor(string n) { name = n; }