#pragma once
#include "include.h"
class Sensor {
    private:
    string name;
    vector<Data> infoArray;
    public:
    //Da controllare il costruttore e costruttore di copia.
    Sensor(string, vector<Data>);
    Data getInfo(int) const;
    string getName() const;
    vector<Data> getArray() const;
    void addData(Data);
    void removeData();
    void renameSensor(string);
    virtual int isInThreshold() const = 0;
    virtual ~Sensor() = default;
};