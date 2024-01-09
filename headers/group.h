#pragma once
#include "include.h"
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
    void removeSensor();
    Sensor *find(string) const;
    void renameGroup(string);
    // Group& operator=(const Group&);
};