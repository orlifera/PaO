#pragma once
#include "item.h"
#include "sensor.h"
#include "atm.h"
#include "air.h"
#include "barrel.h"
#include "must.h"
#include "soil.h"
#include "vines.h"
#include "winery.h"
class Group : public Item
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
    void rename(string) override;
    void save(string) const override;
    bool loadGroup();
    // Group& operator=(const Group&);
};