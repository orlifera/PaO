#include "../headers/winery.h"

//tutti i sensori di temperatura di una cantina non sono a contatto
WineryTemperatureSensor::WineryTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, false, temp, th) {}
double WineryTemperatureSensor::stdDeviation = 1.0;
//funzione che genera dati seocndo una distribuzione uniforme
void WineryTemperatureSensor::generate() {
    auto it = getArray().begin();
    double min = getExpValue() - stdDeviation;
    double max = getExpValue() + stdDeviation;
    //misurazione ogni mezzora (48 totali)
    for (unsigned int i; i < 86400; i += 1800, ++it) {
        it->setTime(i/3600, (i / 60) % 60, i % 60);
        double temperature = min * (2 * stdDeviation) * rand() / max;
        it->setValue(temperature);
    }
}