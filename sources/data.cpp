#include "../headers/data.h"

Data::Data(double val, Time t) : value(val), time(t) {}
double Data::getValue() const { return value; }
void Data::setValue(double d) { value = d; }
Time Data::getTime() const { return time; }
void Data::setTime(unsigned int h, unsigned int m, unsigned int s) { time = Time(h, m, s); }