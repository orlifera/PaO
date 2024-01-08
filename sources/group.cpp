#include "include.h"

Group::Group(string n, vector<Sensor*> s) : groupName(n), sensors(s) {}
string Group::getGroupName() const { return groupName; }
vector<Sensor*> Group::getSensors() const { return sensors; }
void Group::addSensor(Sensor* s) { sensors.push_back(s); }
void Group::removeSensor() { sensors.pop_back(); }
Sensor* Group::find(string n) const {
    for (auto it = sensors.begin(); it != sensors.end(); it++) {
        //if ((it*).getName() == n) return it*;
    }
}
void Group::renameGroup(string n) { groupName == n; }