#include "../headers/sensor.h"

Sensor::Sensor(string n, /*string c*/ double ex, double th) : name(n), expectedValue(ex), threshold(th) {}
string Sensor::getName() const { return name; }
// string Sensor::getCategory() const { return category; }
vector<Data> Sensor::getArray() const { return infoArray; }
Data Sensor::getInfo(int i) const { return infoArray[i]; }
double Sensor::getExpValue() const { return expectedValue; }
double Sensor::getThreshold() const { return threshold; }
void Sensor::setExpValue(double val) { expectedValue = val; }
void Sensor::setThreshold(double th) { threshold = th; }
void Sensor::renameSensor(string n) { name = n; }
void Sensor::push(Data &d) { infoArray.push_back(d); }
// funzione che ritorna:
// 1 se l'ultimo valore è superiore del valore atteso, di una certa soglia
//-1 se l'ultimo valore è inferiore del valore atteso, di una certa soglia
// 0 se l'ultimo valore è compreso nel range della soglia
int Sensor::isInThreshold() const
{
    if (infoArray[infoArray.size() - 1].getValue() > expectedValue + threshold)
        return 1;
    else if (infoArray[infoArray.size() - 1].getValue() < expectedValue - threshold)
        return -1;
    return 0;
}
string Sensor::stringSensor() const {
    string jsonString = "";
    jsonString += "\"sensorName\": \"" + getName() + "\",\n";
    jsonString += "\"expectedValue\": \"" + to_string(getExpValue()) + "\",\n";
    jsonString += "\"threshold\": \"" + to_string(getThreshold()) + "\",\n";
    jsonString += classSensor();
    jsonString += "\"data\": [\n";
    for (auto it = infoArray.begin(); it != infoArray.end(); ++it) {
        jsonString += "{\n";
        jsonString += "\"value\": \"" + to_string(it->getValue()) + "\",\n";
        jsonString += "\"time\": \"" + it->getTime().printTime() + "\"\n}";
        if (it != infoArray.end()-1) jsonString += ",";
        jsonString += "\n";
    }
    jsonString += "]\n";
}
void Sensor::saveSensor(string name) const {
    ofstream outputfile(name+".json");
    if(outputfile.is_open())
    {
        string jsonString = "{\n";
        jsonString += stringSensor();
        jsonString += "}";
        outputfile << jsonString;
    }
    cerr << "Error on saving the sensor" << endl;;
}