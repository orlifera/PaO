#pragma once
#include "include.h"

// orario identificativo per i dati misurati dai sensori
class Time
{
private:
    unsigned int sec;

public:
    Time(unsigned int = 0, unsigned int = 0, unsigned int = 0);
    // ritorna le ore
    unsigned int Hour() const;
    // ritorna i minuti
    unsigned int Mins() const;
    // ritorna i secondi
    unsigned int Secs() const;
    // ritorna una stringa con l'orario
    string printTime() const;
};