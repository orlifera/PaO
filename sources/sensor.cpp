#include "../headers/sensor.h"
#include "../headers/group.h"

Sensor::Sensor(string n, /*string c*/ double ex, double th) : name(n), expectedValue(ex), threshold(th) {}

string Sensor::getName() const { return name; }

vector<Data> Sensor::getArray() const { return infoArray; }

void Sensor::clear()
{
    vector<Data>().swap(infoArray); // effettua uno swap con un vettore vuoto
}

Data Sensor::getInfo(int i) const { return infoArray[i]; }

double Sensor::getExpValue() const { return expectedValue; }

double Sensor::getThreshold() const { return threshold; }

void Sensor::setExpValue(double val)
{
    expectedValue = val;
}

void Sensor::setThreshold(double th)
{
    threshold = th;
}

void Sensor::rename(string n)
{
    name = n;
}

void Sensor::push(Data &d) { infoArray.push_back(d); }

void Sensor::push(vector<Data> v) { infoArray = v; }

// funzione che conta numero di picchi che sono superiori e quelli inferiori al valore atteso oltre la soglia
// se non ce ne sono ritorna 0
// se ce ne sono e i picchi positivi sono maggiori di quelli negativi ritorna 1
// se ce ne sono e i picchi negativi sono maggiori di quelli positivi ritorna -1
// se ce ne sono e sono uguali allora ritorna 1 se il picco piu grande positivo supera quello negativo e -1 altrimenti
int Sensor::isInThreshold() const
{
    int countPos = 0, countNeg = 0;
    double exepP = expectedValue;
    double exepN = expectedValue;
    for (auto it = infoArray.begin(); it != infoArray.end(); ++it)
    {
        double current = it->getValue();
        if (current > expectedValue + threshold)
        {
            countPos++;
            if (exepP < current)
                exepP = current;
        }
        else if (current < expectedValue - threshold)
        {
            countNeg++;
            if (exepN > current)
                exepN = current;
        }
    }
    if (countPos > countNeg)
        return 1;
    else if (countPos < countNeg)
        return -1;
    else if (countPos != 0 && countNeg != 0 && countPos == countNeg)
        return abs(exepP - expectedValue) > abs(exepN - expectedValue) ? 1 : -1;
    return 0;
}

QJsonObject Sensor::writeSensor() const
{
    QJsonObject sensor;
    // nome del sensore
    sensor["sensorName"] = QString::fromStdString(getName());
    // valore atteso
    sensor["expected value"] = getExpValue();
    // soglia
    sensor["threshold"] = getThreshold();
    // classe
    QJsonObject classObj = classSensor();
    for (auto it = classObj.begin(); it != classObj.end(); ++it)
    {
        sensor.insert(it.key(), it.value());
    }
    // crea infoArray
    QJsonArray info;
    // per ogni dato in infoArray
    for (const auto &data : getArray())
    {
        QJsonObject infoData;
        // tempo
        infoData["time"] = data.getTime();
        // valore effettivo
        infoData["value"] = data.getValue();
        // push dei dati nel vettore
        info.append(infoData);
    }
    // assegna le info all'array
    sensor["info"] = info;
    return sensor;
}

void Sensor::save(string filename) const
{
    if (exists(filename))
        remove(filename);
    if (filename.find(".json") == string::npos)
        filename += ".json";
    // nuovo file "filename"
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        QJsonObject sensor = writeSensor();
        // push del gruppo nel jsonDocument
        QJsonDocument jsonDoc(sensor);
        // inserimento dati nel file
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
            // ottenimento nome
            string name = sensorObj["sensorName"].toString().toStdString();
            // ottenimento del valore atteso
            double expected = sensorObj["expected value"].toDouble();
            // ottenimento della soglia
            double thr = sensorObj["threshold"].toDouble();
            // ottenimento della classe
            string className = sensorObj["class"].toString().toStdString();
            vector<Data> v;
            // ottenimento dell'array dati
            QJsonArray dataArray = sensorObj["info"].toArray();
            // per ogni dato
            for (auto entry : dataArray)
            {
                QJsonObject dataObj = entry.toObject();
                // ottenimento del tempo
                Time t;
                t.setTime(dataObj["time"].toInt());
                // ottenimento del valore effettivo
                double val = dataObj["value"].toDouble();
                v.push_back(Data(val, t));
            }
            // chiusura file
            inFile.close();
            // creazione dello specifico sensore
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