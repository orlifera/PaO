#pragma once
#include "sensor.h"
class Group
{
private:
    string groupName;
    vector<Sensor *> sensors;
public:
    Group(string, vector<Sensor *>);
    string getGroupName() const;
    vector<Sensor *> getSensors() const;
    void addSensor(Sensor *);
    void removeSensor(Sensor*);
    void removeSensor(string);
    void removeSensor(int);
    Sensor* find(string) const;
    void renameGroup(string);
    // Group& operator=(const Group&);
};