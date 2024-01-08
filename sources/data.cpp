#include "include.h"

Data::Data(double val, Time t) : value(val), time(t) {}
double Data::getValue() const { return value; }
Time Data::getTime() const { return time; }