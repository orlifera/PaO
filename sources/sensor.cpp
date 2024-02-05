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
void Sensor::rename(string n) { name = n; }
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
// string Sensor::stringSensor() const {
//     string jsonString = "";
//     jsonString += "\"sensorName\": \"" + getName() + "\",\n";
//     jsonString += "\"expectedValue\": \"" + to_string(getExpValue()) + "\",\n";
//     jsonString += "\"threshold\": \"" + to_string(getThreshold()) + "\",\n";
//     jsonString += classSensor();
//     jsonString += "\"data\": [\n";
//     for (auto it = infoArray.begin(); it != infoArray.end(); ++it) {
//         jsonString += "{\n";
//         jsonString += "\"value\": \"" + to_string(it->getValue()) + "\",\n";
//         jsonString += "\"time\": \"" + it->getTime().printTime() + "\"\n}";
//         if (it != infoArray.end()-1) jsonString += ",";
//         jsonString += "\n";
//     }
//     jsonString += "]\n";
// }
QJsonObject Sensor::saveSensor() const {
    QJsonObject sensor;
    // gets sensor's name
    sensor["sensorName"] = QString::fromStdString(getName());
    // gets sensor's expected value
    sensor["expected value"] = getExpValue();
    // gets sensor's threshold
    sensor["threshold"] = getThreshold();
    // gets sensor's class
    QJsonObject classObj = classSensor();
    for (auto it = classObj.begin(); it != classObj.end(); ++it) {
        sensor.insert(it.key(), it.value());
    }
    // creates an infoArray
    QJsonArray info;
    // for each data in infoArray
    for (const auto &data : getArray())
    {
        QJsonObject infoData;
        // gets info's time
        infoData["time"] = QString::fromStdString(data.getTime());
        // gets info's value
        infoData["value"] = data.getValue();
        // pushes the data in the array
        info.append(infoData);
    }
    // assigns infoArray as sensor's info
    sensor["info"] = info;
    return sensor;
}

void Sensor::save(string filename) const {
    if (exists(filename)) remove(filename);
    // new file "filename"
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        QJsonObject sensor = saveSensor();
        // pushes the group in the jsonDocument
        QJsonDocument jsonDoc(sensor);
        //insert data in file
        outFile << jsonDoc.toJson().toStdString();
        outFile.close();
    }
    else {
        cerr << "Error on saving the sensor" << endl;
    }
}
// void Sensor::saveSensor(string name) const {
//     ofstream outputfile(name+".json");
//     if(outputfile.is_open())
//     {
//         string jsonString = "{\n";
//         jsonString += stringSensor();
//         jsonString += "}";
//         outputfile << jsonString;
//     }
//     cerr << "Error on saving the sensor" << endl;;
// }