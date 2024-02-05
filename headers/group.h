#pragma once
#include "sensor.h"
#include "atm.h"
#include "air.h"
#include "barrel.h"
#include "must.h"
#include "soil.h"
#include "vines.h"
#include "winery.h"
class Group
{
private:
    string groupName;
    vector<Sensor *> sensors;

public:
    Group(string);
    string getGroupName() const;
    vector<Sensor *> getSensors() const;
    void addSensor(Sensor *);
    void removeSensor(Sensor *);
    void removeSensor(string);
    void removeSensor(int);
    Sensor *find(string) const;
    void rename(string);
    void save(string) const;
    static Group load(string);
    // Group& operator=(const Group&);
};