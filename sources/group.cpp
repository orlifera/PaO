#include "../headers/group.h"

Group::Group(string n) : groupName(n) {}

string Group::getGroupName() const { return groupName; }

vector<Sensor *> Group::getSensors() const { return sensors; }

void Group::addSensor(Sensor *s) { sensors.push_back(s); }

void Group::removeSensor(Sensor *s)
{
    string n = s->getName();
    removeSensor(n);
}

void Group::removeSensor(string n)
{
    auto it = sensors.begin();
    while (it != sensors.end())
    {
        if ((*it)->getName() == n)
        {
            it = sensors.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Group::removeSensor(int pos)
{
    string n = sensors[pos]->getName();
    removeSensor(n);
}

bool Group::find(string n) const
{
    for (auto it = sensors.begin(); it != sensors.end(); it++)
    {
        if ((*it)->getName() == n)
            return true;
    }
    return 0;
}

void Group::rename(string n) { groupName = n; }

void Group::save(string path) const
{
    // elimino se presente
    if (exists(path))
        remove(path);
    // aggiugno .json se assente
    if (path.find(".json") == string::npos)
        path += ".json";
    // nuovo file "filename"
    ofstream outFile(path);
    if (outFile.is_open())
    {
        QJsonObject group;
        // nome
        group["groupName"] = QString::fromStdString(getGroupName());
        QJsonArray sensorArray;
        // per ogni sensore
        for (auto it = sensors.begin(); it != sensors.end(); ++it)
        {
            // info del sensore
            QJsonObject sensor = (*it)->writeSensor();
            sensorArray.append(sensor);
        }
        // assegno all'array le info dei sensori
        group["sensors"] = sensorArray;
        // pushe del gruppo in jsonDocument
        QJsonDocument jsonDoc(group);
        // inserimento dati nel file
        outFile << jsonDoc.toJson().toStdString();
        outFile.close();
    }
    else
    {
        cerr << "Error on saving the sensor" << endl;
    }
}

Group *Group::load(string filename)
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
            QJsonObject groupObj = jsonDoc.object();
            // ottenimento del nome del gruppo
            string groupName = groupObj["groupName"].toString().toStdString();
            Group *g = new Group(groupName);
            // ottenimento del vettore dei puntatori ai sensori
            QJsonArray sensorArray = groupObj["sensors"].toArray();
            // per ogni sensore
            for (auto s : sensorArray)
            {
                QJsonObject sensorObj = s.toObject();
                // ottenimento del nome del sensore
                string sensorName = sensorObj["sensorName"].toString().toStdString();
                // ottenimento del valore atteso
                double expected = sensorObj["expected value"].toDouble();
                // ottenimento della soglia
                double thr = sensorObj["threshold"].toDouble();
                // ottenimento della classe
                string className = sensorObj["class"].toString().toStdString();
                vector<Data> sensorV;
                // ottenimento del vettore dei dati
                QJsonArray dataArray = sensorObj["info"].toArray();
                // per ogni dato
                for (const auto &entry : dataArray)
                {
                    QJsonObject dataObj = entry.toObject();
                    // ottenimento del tempo
                    Time t(dataObj["time"].toInt());
                    // ottenimento del valore
                    double val = dataObj["value"].toDouble();
                    sensorV.push_back(Data(val, t));
                }
                // chiusura del file
                inFile.close();
                // creazione dello specifico sensore
                if (className == "air-humidity")
                {
                    AirHumiditySensor *a = new AirHumiditySensor(sensorName, expected, thr);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
                if (className == "atm-pressure")
                {
                    AtmPressureSensor *a = new AtmPressureSensor(sensorName, thr);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
                if (className == "barrel-pressure")
                {
                    BarrelPressureSensor *a = new BarrelPressureSensor(sensorName, expected, thr);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
                if (className == "must-temperature")
                {
                    double timer = sensorObj["timer"].toDouble();
                    MustTemperatureSensor *a = new MustTemperatureSensor(sensorName, expected, thr);
                    a->setTimer(timer);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
                if (className == "soil-humidity")
                {
                    SoilHumiditySensor *a = new SoilHumiditySensor(sensorName, expected, thr);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
                if (className == "vines-temperature")
                {
                    VinesTemperatureSensor *a = new VinesTemperatureSensor(sensorName, expected, thr);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
                if (className == "winery-temperature")
                {
                    WineryTemperatureSensor *a = new WineryTemperatureSensor(sensorName, expected, thr);
                    a->push(sensorV);
                    g->sensors.push_back(a);
                }
            }
            return g;
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

Sensor *Group::loadSensor(string filename)
{
    Sensor *s = Sensor::load(filename);
    addSensor(s); // aggiunge il nuovo sensore al gruppo
    return s;
}

Sensor *Group::newSensor(string n, double e, double t, string c)
{
    Sensor *s = Sensor::newSensor(n, e, t, c);
    addSensor(s); // aggiunge il nuovo sensore al gruppo
    return s;
}