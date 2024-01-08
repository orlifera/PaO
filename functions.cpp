#include"functions.h"

Data::Data(double val, string dat) : value(val), date(dat) {}
double Data::getValue() const { return value; }
string Data::getDate() const { return date; }

//Sensor::Sensor(string n, vector<Data> v) : name(n), infoArray(new vector<Data>(v)) {}
//Sensor::Sensor(const Sensor& s) { name = s.getName(); infoArray = new vector<Data>(s.getArray()) }
string Sensor::getName() const { return name; }
vector<Data> Sensor::getArray() const { return infoArray; }
Data Sensor::getInfo(int i) const { return infoArray[i]; }
void Sensor::addData(Data d, int pos) { /*rivedere funzionamento di [] nei vettori*/ }
virtual void Sensor::removeData(Data d, int pos) { /*same*/ }
//virtual Sensor::~Sensor() { delete infoArray; }

//costruttore, copia e distruttore di temp e derivati
bool TemperatureSensor::isContact() const { return contact; }
double TemperatureSensor::getTemp() const { return temp; }
void TemperatureSensor::setTemp(double t) { temp = t; }

int VinesTemperatureSensor::isInThreshold() const override {
    double last = infoArray[infoArray.size()-1];
    if (last > vineThreshold+temp) return 1;
    else if (last < temp-vineThreshold) return -1;
    else return 0;
}

int WineryTemperatureSensor::isInThreshold() const override {
    double last = infoArray[infoArray.size()-1];
    if (last > wineryThreshold+temp) return 1;
    else if (last < temp-wineThreshold) return -1;
    else return 0;
}

int MustTemperatureSensor::isInThreshold() const override {
    double last = infoArray[infoArray.size()-1];
    if (last > mustThreshold+temp) return 1;
    else if (last < temp-mustThreshold) return -1;
    else return 0;
}

//costruttore, copia e distruttore di humid e derivati
bool HumiditySensor::isCapacity() const { return capacity; }
double HumiditySensor::getHumidity() const { return humidity; }
void HumiditySensor::setHumidity(double h) { humidity = h; }



//costruttore, copia e distruttore di pressure e derivati
double PressureSensor::getPressure() const { return pressure; }
void PressureSensor::setPressure(double p) { pressure = p; }

//Group::Group(string n, vector<Sensor*> s) : groupName(n), sensors(new vector<Sensor*>(s)) {}
//Group::Group(const Group& g) { groupName = g.getGroupName(); sensors = new vector<Sensor*>(g.getSensors()) }
string Group::getGroupName() const { return groupName; }
vector<Sensor*> Group::getSensors() const { return sensors; }
void Group::addSensor(Sensor* s, int pos) { /*no idea*/ }
void Group::removeSensor(Sensor* s, int pos) { /*no idea*/ }
Sensor Group::find(string n) const {
    for (auto it = sensors.begin(); it != sensors.end(); it++) {
        if (it*->getName() == n) return it**;
    }
}
void Group::rename(string n) { groupName == n; }
//no fucking clue
//Group& Group::operator=() {}
//Group& Group::operator+() {}
//Group& Group::operator-() {}
//Group::~Group() { delete sensors; }