#include "include.h"

Time::Time(unsigned int h, unsigned int m, unsigned int s) {
    if (h > 23 || m > 59 || s > 59) sec = 0;
    else sec = h * 3600 + m * 60 + s;
}
unsigned int Time::Hour() const { return sec / 3600; }
unsigned int Time::Mins() const { return (sec / 60) % 60; }
unsigned int Time::Secs() const { return sec % 60; }
//Time::operator int() { return sec; }
ostream& operator<<(ostream& os, const Time& t) {
    return os << t.Hour() << ":" << t.Mins() << ":" << t.Secs();
}