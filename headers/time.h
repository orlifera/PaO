#pragma once
class Time {
    private:
    unsigned int sec;
    public:
    Time(unsigned int =0, unsigned int =0, unsigned int =0);
    unsigned int Hour() const;
    unsigned int Mins() const;
    unsigned int Secs() const;
    //operator int();
};