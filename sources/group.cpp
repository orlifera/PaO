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
    for (auto it = sensors.begin(); it != sensors.end(); it++)
    {
        if ((*it)->getName() == n)
            it = sensors.erase(it);
    }
}
void Group::removeSensor(int pos)
{
    string n = sensors[pos]->getName();
    removeSensor(n);
}
Sensor *Group::find(string n) const
{
    for (auto it = sensors.begin(); it != sensors.end(); it++)
    {
        if ((*it)->getName() == n)
            return *it;
    }
    return 0;
}
void Group::rename(string n) { groupName = n; }
void Group::save(string path) const
{
    if (exists(path))
        remove(path);
    if (path.find(".json") == string::npos)
        path += ".json";
    // new file "filename"
    ofstream outFile(path);
    if (outFile.is_open())
    {
        QJsonObject group;
        group["groupName"] = QString::fromStdString(getGroupName());
        QJsonArray sensorArray;
        for (auto it = sensors.begin(); it != sensors.end(); ++it)
        {
            QJsonObject sensor = (*it)->writeSensor();
            sensorArray.append(sensor);
        }
        group["sensors"] = sensorArray;
        // pushes the group in the jsonDocument
        QJsonDocument jsonDoc(group);
        // insert data in file
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
            string groupName = groupObj["groupName"].toString().toStdString();
            Group *g = new Group(groupName);
            QJsonArray sensorArray = groupObj["sensors"].toArray();
            for (auto s : sensorArray)
            {
                QJsonObject sensorObj = s.toObject();
                string sensorName = sensorObj["sensorName"].toString().toStdString();
                double expected = sensorObj["expected value"].toDouble();
                double thr = sensorObj["threshold"].toDouble();
                string className = sensorObj["class"].toString().toStdString();
                vector<Data> sensorV;
                QJsonArray dataArray = sensorObj["info"].toArray();
                for (const auto &entry : dataArray)
                {
                    QJsonObject dataObj = entry.toObject();
                    Time t(dataObj["time"].toInt());
                    double val = dataObj["value"].toDouble();
                    sensorV.push_back(Data(val, t));
                }
                inFile.close();
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
Sensor *Group::loadSensor()
{
    cout << "Name of the file: ";
    string filename;
    cin >> filename;
    Sensor *s = Sensor::load(filename);
    addSensor(s);
    return s;
}
Sensor *Group::newSensor(string n, double e, double t, string c)
{
    Sensor *s = Sensor::newSensor(n, e, t, c);
    addSensor(s);
    return s;
}