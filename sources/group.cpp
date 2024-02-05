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
}
void Group::rename(string n) { groupName = n; }
void Group::save(string filename) const {
    if (exists(filename)) remove(filename);
    // new file "filename"
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        QJsonObject group;
        group["groupName"] = QString::fromStdString(getGroupName());
        QJsonArray sensorArray;
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            QJsonObject sensor = (*it)->writeSensor();
            sensorArray.append(sensor);
        }
        group["sensors"] = sensorArray;
        // pushes the group in the jsonDocument
        QJsonDocument jsonDoc(group);
        //insert data in file
        outFile << jsonDoc.toJson().toStdString();
        outFile.close();
    }
    else {
        cerr << "Error on saving the sensor" << endl;
    }
}
Group Group::load(string filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string content;
        char ch;
        while (inFile.get(ch)) {
            content.push_back(ch);
        }
        QJsonDocument jsonDoc =QJsonDocument::fromJson(QByteArray::fromStdString(content));
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject groupObj = jsonDoc.object();
            string groupName = groupObj["groupName"].toString().toStdString();
            Group g(groupName);
            QJsonArray sensorArray = groupObj["sensors"].toArray();
            for (auto s: sensorArray) {
                QJsonObject sensorObj = s.toObject();
                string sensorName = sensorObj["sensorName"].toString().toStdString();
                double expected = sensorObj["expected value"].toDouble();
                double thr = sensorObj["threshold"].toDouble();
                string className = sensorObj["class"].toString().toStdString();
                vector<Data> sensorV;
                QJsonArray dataArray = sensorObj["info"].toArray();
                for (auto entry: dataArray) {
                    QJsonObject dataObj = entry.toObject();
                    Time t(dataObj["time"].toInt());
                    double val = dataObj["value"].toDouble();
                    sensorV.push_back(Data(val,t));
                }
                inFile.close();
                if (className == "air-humidity") {
                    AirHumiditySensor a(sensorName,expected,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
                if (className == "atm-pressure") {
                    AtmPressureSensor a(sensorName,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
                if (className == "barrel-pressure") {
                    BarrelPressureSensor a(sensorName,expected,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
                if (className == "must-temperature") {
                    double timer = sensorObj["timer"].toDouble();
                    MustTemperatureSensor a(sensorName,expected,timer,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
                if (className == "soil-humidity") {
                    SoilHumiditySensor a(sensorName,expected,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
                if (className == "vines-temperature") {
                    VinesTemperatureSensor a(sensorName,expected,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
                if (className == "winery-temperature") {
                    WineryTemperatureSensor a(sensorName,expected,thr);
                    a.push(sensorV);
                    g.sensors.push_back(&a);
                }
            }
            return g;
        }
        else {
            cerr << "Error: unable to parse JSON file" << endl;
        }
    }
    else {
        cerr << "Unable to open file" << endl;
    }
}
// void Group::saveGroup(const string &filename) const {
//     string file = filename + ".json";
//     if (exists(file)) remove(file);
//     ofstream outputFile(file);
//     if (outputFile.is_open()) {
//         string jsonString = "{\n";
//         jsonString += "\"groupName\": \"" + getGroupName() + "\",\n";
//         jsonString += "\"sensors\": [\n";
//         for (auto git = sensors.begin(); git != sensors.end(); ++git)
//         {
//             jsonString += "{\n" + (*git)->stringSensor() + "}";
//             if (git != sensors.end()-1) jsonString += ",\n";
//             jsonString += "\n";
//         }
//         jsonString += "]\n}";
//         outputFile << jsonString;
//         outputFile.close();
//     } else {
//         cerr << "Failed to save the file." << endl;
//     }
// }

// bool Group::loadGroup() {
//     ifstream inputFile("./data.json");
//     if (inputFile.is_open()) {
//         stringstream filecontent;
//         filecontent << inputFile.rdbuf();
//         string jsonString = filecontent.str();
//         size_t groupPos = jsonString.find("\"groupName\":");
//         if (groupPos != string::npos)
//         {
//             size_t groupStartPos = jsonString.find("\"", groupPos+1)+1;
//             size_t groupEndPos = jsonString.find("\"", groupStartPos);
//             groupName = jsonString.substr(groupStartPos, groupEndPos-groupStartPos);
//             while (true) {
//                 size_t sensorPos = jsonString.find("\"sensorName\":");
//                 size_t expectedPos = jsonString.find("\"expextedValue\":");
//                 size_t thresholdPos = jsonString.find("\"threshold\":");
//                 size_t classPos = jsonString.find("\"class\":");
//                 if (sensorPos != string::npos && expectedPos != string::npos && thresholdPos != string::npos && classPos != string::npos) {
//                     size_t sensorStartPos = jsonString.find("\"", sensorPos+1)+1;
//                     size_t sensorEndPos = jsonString.find("\"", sensorStartPos);
//                     string sensorName = jsonString.substr(sensorStartPos, sensorEndPos-sensorStartPos);
//                     size_t expectedStartPos = jsonString.find("\"", expectedPos+1)+1;
//                     size_t expectedEndPos = jsonString.find("\"", expectedStartPos);
//                     double expV = stod(jsonString.substr(expectedStartPos, expectedEndPos-expectedStartPos));
//                     size_t thresholdStartPos = jsonString.find("\"", thresholdPos+1)+1;
//                     size_t thresholdEndPos = jsonString.find("\"", thresholdStartPos);
//                     double thr = stod(jsonString.substr(thresholdStartPos, thresholdEndPos-thresholdStartPos));
//                     size_t classStartPos = jsonString.find("\"", classPos+1)+1;
//                     size_t classEndPos = jsonString.find("\"", classStartPos);
//                     string className = jsonString.substr(classStartPos, classEndPos-classStartPos);
//                     if (className == "air-humidity") sensors.push_back(&AirHumiditySensor(sensorName,expV,thr));
//                     else if (className == "atm-pressure") sensors.push_back(&AtmPressureSensor(sensorName,thr));
//                     else if (className == "barrel-pressure") sensors.push_back(&BarrelPressureSensor(sensorName,expV,thr));
//                     else if (className == "must-temperature") sensors.push_back(&MustTemperatureSensor(sensorName,expV,thr));
//                     else if (className == "soil-humidity") sensors.push_back(&SoilHumiditySensor(sensorName,expV,thr));
//                     else if (className == "vines-temperature") sensors.push_back(&VinesTemperatureSensor(sensorName,expV,thr));
//                     else if (className == "winery-temperature") sensors.push_back(&WineryTemperatureSensor(sensorName,expV,thr)); 
//                     size_t valuePos = jsonString.find("\"value\":");
//                     size_t valueStartPos = jsonString.find("\"", valuePos+1)+1;
//                     size_t valueEndPos = jsonString.find("\"", valueStartPos);
//                     double value = stod(jsonString.substr(valueStartPos, valueEndPos-valueStartPos));
//                     size_t timePos = jsonString.find("\"time\":");
//                     size_t timeStartPos = jsonString.find("\"", timePos+1)+1;
//                     size_t timeHourPos = jsonString.find(":", timeStartPos+1);
//                     size_t timeMinPos = jsonString.find(":", timeHourPos+1);
//                     size_t timeEndPos = jsonString.find("\"", timeStartPos);
//                     unsigned int h = stoi(jsonString.substr(timeStartPos, timeHourPos-timeStartPos)); 
//                     unsigned int m = stoi(jsonString.substr(timeHourPos, timeMinPos-timeHourPos)); 
//                     unsigned int s = stoi(jsonString.substr(timeMinPos, timeEndPos-timeMinPos));
//                     sensors->infoArray.setValue(value);
//                     sensors->infoArray.setTime(h,m,s);        
//                 }
//             }
//         }
//         return true;
//     } else return false;
// }