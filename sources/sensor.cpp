#include "../headers/sensor.h"
#include "../headers/group.h"

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
void Sensor::push(vector<Data> v) { infoArray = v; }
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
QJsonObject Sensor::writeSensor() const
{
    QJsonObject sensor;
    // gets sensor's name
    sensor["sensorName"] = QString::fromStdString(getName());
    // gets sensor's expected value
    sensor["expected value"] = getExpValue();
    // gets sensor's threshold
    sensor["threshold"] = getThreshold();
    // gets sensor's class
    QJsonObject classObj = classSensor();
    for (auto it = classObj.begin(); it != classObj.end(); ++it)
    {
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

void Sensor::save(string filename) const
{
    if (exists(filename))
        remove(filename);
    if (filename.find(".json") == string::npos)
        filename += ".json";
    // new file "filename"
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        QJsonObject sensor = writeSensor();
        // pushes the group in the jsonDocument
        QJsonDocument jsonDoc(sensor);
        // insert data in file
        outFile << jsonDoc.toJson().toStdString();
        outFile.close();
    }
    else
    {
        cerr << "Error on saving the sensor" << endl;
    }
}
Sensor *Sensor::load(string filename)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        string content;
        char ch;
        while (inFile.get(ch))
        {
            content.push_back(ch);
        }
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(content));
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject sensorObj = jsonDoc.object();
            string name = sensorObj["sensorName"].toString().toStdString();
            double expected = sensorObj["expected value"].toDouble();
            double thr = sensorObj["threshold"].toDouble();
            string className = sensorObj["class"].toString().toStdString();
            vector<Data> v;
            QJsonArray dataArray = sensorObj["info"].toArray();
            for (auto entry : dataArray)
            {
                QJsonObject dataObj = entry.toObject();
                Time t(dataObj["time"].toInt());
                double val = dataObj["value"].toDouble();
                v.push_back(Data(val, t));
            }
            inFile.close();
            if (className == "air-humidity")
            {
                AirHumiditySensor *a = new AirHumiditySensor(name, expected, thr);
                a->push(v);
                return a;
            }
            if (className == "atm-pressure")
            {
                AtmPressureSensor *a = new AtmPressureSensor(name, thr);
                a->push(v);
                return a;
            }
            if (className == "barrel-pressure")
            {
                BarrelPressureSensor *a = new BarrelPressureSensor(name, expected, thr);
                a->push(v);
                return a;
            }
            if (className == "must-temperature")
            {
                double timer = sensorObj["timer"].toDouble();
                MustTemperatureSensor *a = new MustTemperatureSensor(name, expected, thr);
                a->setTimer(timer);
                a->push(v);
                return a;
            }
            if (className == "soil-humidity")
            {
                SoilHumiditySensor *a = new SoilHumiditySensor(name, expected, thr);
                a->push(v);
                return a;
            }
            if (className == "vines-temperature")
            {
                VinesTemperatureSensor *a = new VinesTemperatureSensor(name, expected, thr);
                a->push(v);
                return a;
            }
            if (className == "winery-temperature")
            {
                WineryTemperatureSensor *a = new WineryTemperatureSensor(name, expected, thr);
                a->push(v);
                return a;
            }
        }
        else
        {
            cerr << "Error: unable to parse JSON file" << endl;
        }
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
    return 0;
}
Sensor *Sensor::newSensor(string name, double expected, double thr, string sensorclass)
{
    if (sensorclass == "air-humidity")
    {
        return new AirHumiditySensor(name, expected, thr);
    }
    if (sensorclass == "atm-pressure")
    {
        return new AtmPressureSensor(name, thr);
    }
    if (sensorclass == "barrel-pressure")
    {
        return new BarrelPressureSensor(name, expected, thr);
    }
    if (sensorclass == "must-temperature")
    {
        return new MustTemperatureSensor(name, expected, thr);
    }
    if (sensorclass == "soil-humidity")
    {
        return new SoilHumiditySensor(name, expected, thr);
    }
    if (sensorclass == "vines-temperature")
    {
        return new VinesTemperatureSensor(name, expected, thr);
    }
    if (sensorclass == "winery-temperature")
    {
        return new WineryTemperatureSensor(name, expected, thr);
    }
    return 0;
}