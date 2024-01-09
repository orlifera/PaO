#pragma once
#include "data.h"
class Sensor {
    private:
    string name;
    vector<Data> infoArray; //valori effettivi
    double expectedValue; //valore che mi aspetto
    double threshold; //soglia
    public:
    Sensor(string, vector<Data>, double, double =0);
    Data getInfo(int) const;
    string getName() const;
    vector<Data> getArray() const;
    double getExpValue() const;
    double getThreshold() const;
    void setExpValue(double);
    void setThreshold(double);
    virtual void generate(string);
    void renameSensor(string);
    int isInThreshold() const;
    virtual ~Sensor() = 0;
};