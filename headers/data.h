#pragma once
#include "time.h"
class Data {
    private:
    double value;
    Time time;
    public:
    Data(double, Time);
    double getValue() const;
    Time getTime() const;
};