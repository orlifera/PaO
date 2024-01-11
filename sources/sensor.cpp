#include "../headers/sensor.h"

Sensor::Sensor(string n, vector<Data> v, double ex, double th) : name(n), infoArray(v), expectedValue(ex), threshold(th) {}
string Sensor::getName() const { return name; }
vector<Data> Sensor::getArray() const { return infoArray; }
Data Sensor::getInfo(int i) const { return infoArray[i]; }
double Sensor::getExpValue() const { return expectedValue; }
double Sensor::getThreshold() const { return threshold; }
void Sensor::setExpValue(double val) { expectedValue = val; }
void Sensor::setThreshold(double th) { threshold = th; }
void Sensor::renameSensor(string n) { name = n; }
void Sensor::push(Data& d) { infoArray.push_back(d); }
//funzione che ritorna:
//1 se l'ultimo valore è superiore del valore atteso, di una certa soglia
//-1 se l'ultimo valore è inferiore del valore atteso, di una certa soglia
//0 se l'ultimo valore è compreso nel range della soglia
int Sensor::isInThreshold() const {
    if (infoArray[infoArray.size()-1].getValue() > expectedValue+threshold) return 1;
    else if (infoArray[infoArray.size()-1].getValue() < expectedValue-threshold) return -1;
    return 0;
}