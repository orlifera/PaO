#include"functions.h"

Time::Time(unsigned int h, unsigned int m, unsigned int s) {
    if (h > 23 || m > 59 || s > 59) sec = 0;
    else sec = h * 3600 + m * 60 + s;
}
unsigned int Time::Hour() const { return sec / 3600; }
unsigned int Time::Mins() const { return (sec / 60) % 60; }
unsigned int Time::Secs() const { return sec % 60; }
//Time::operator int() { return sec; }
ostream& operator<<(ostream& os, const Time& t) {
    return os << t.Hour() << ":" << t.Mins() << ":" << t.Secs();
}

Data::Data(double val, Time t) : value(val), time(t) {}
double Data::getValue() const { return value; }
Time Data::getTime() const { return time; }

Sensor::Sensor(string n, vector<Data> v) : name(n), infoArray(v) {}
string Sensor::getName() const { return name; }
vector<Data> Sensor::getArray() const { return infoArray; }
Data Sensor::getInfo(int i) const { return infoArray[i]; }
void Sensor::addData(Data d) { infoArray.push_back(d); }
void Sensor::removeData() { infoArray.pop_back(); }
void Sensor::renameSensor(string n) { name = n; } 

TemperatureSensor::TemperatureSensor(string n, vector<Data> v, bool c, double t) : Sensor(n,v), contact(c), temp(t) {}
bool TemperatureSensor::isContact() const { return contact; }
double TemperatureSensor::getTemp() const { return temp; }
void TemperatureSensor::setTemp(double t) { temp = t; }

VinesTemperatureSensor::VinesTemperatureSensor(string n, vector<Data> v, double t) : TemperatureSensor(n,v,false,t) {}
int VinesTemperatureSensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > vineThreshold+getTemp()) return 1;
    else if (last < getTemp()-vineThreshold) return -1;
    else return 0;
}
double VinesTemperatureSensor::vineThreshold = 0;

MustTemperatureSensor::MustTemperatureSensor(string n, vector<Data> v, double t) : TemperatureSensor(n,v,true,t) {}
int MustTemperatureSensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > mustThreshold+getTemp()) return 1;
    else if (last < getTemp()-mustThreshold) return -1;
    else return 0;
}
double MustTemperatureSensor::mustThreshold = 0;

HumiditySensor::HumiditySensor(string n, vector<Data> v, bool c, double h) : Sensor(n,v), capacity(c), humidity(h) {}
bool HumiditySensor::isCapacity() const { return capacity; }
double HumiditySensor::getHumidity() const { return humidity; }
void HumiditySensor::setHumidity(double h) { humidity = h; }

AirHumiditySensor::AirHumiditySensor(string n, vector<Data> v, double h) : HumiditySensor(n,v,true,h) {}
int AirHumiditySensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > airThreshold+getHumidity()) return 1;
    else if (last < getHumidity()-airThreshold) return -1;
    else return 0;
}
double AirHumiditySensor::airThreshold = 0;

SoilHumiditySensor::SoilHumiditySensor(string n, vector<Data> v, double h) : HumiditySensor(n,v,false,h) {}
int SoilHumiditySensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > soilThreshold+getHumidity()) return 1;
    else if (last < getHumidity()-soilThreshold) return -1;
    else return 0;
}
double SoilHumiditySensor::soilThreshold = 0;

PressureSensor::PressureSensor(string n, vector<Data> v, double p) : Sensor(n,v), pressure(p) {}
double PressureSensor::getPressure() const { return pressure; }
void PressureSensor::setPressure(double p) { pressure = p; }

AtmPressureSensor::AtmPressureSensor(string n, vector<Data> v) : PressureSensor(n,v,1.0) {}
int AtmPressureSensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > atmThreshold+getPressure()) return 1;
    else if (last < getPressure()-atmThreshold) return -1;
    else return 0;
}
double AtmPressureSensor::atmThreshold = 0;

int BarrelSensor::isInThreshold() const {
    double last = getInfo(getArray().size()-1).getValue();
    if (last > barrelThreshold+getPressure()) return 1;
    else if (last < getPressure()-barrelThreshold) return -1;
    else return 0;
}
double BarrelSensor::barrelThreshold = 0;

Group::Group(string n, vector<Sensor*> s) : groupName(n), sensors(s) {}
string Group::getGroupName() const { return groupName; }
vector<Sensor*> Group::getSensors() const { return sensors; }
void Group::addSensor(Sensor* s) { sensors.push_back(s); }
void Group::removeSensor() { sensors.pop_back(); }
Sensor* Group::find(string n) const {
    for (auto it = sensors.begin(); it != sensors.end(); it++) {
        //if ((it*).getName() == n) return it*;
    }
}
void Group::renameGroup(string n) { groupName == n; }
//no fucking clue