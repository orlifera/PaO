#include "../headers/group.h"

Group::Group(string n, vector<Sensor *> s) : groupName(n), sensors(s) {}
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
void Group::renameGroup(string n) { groupName = n; }