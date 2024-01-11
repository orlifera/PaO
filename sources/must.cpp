#include "../headers/must.h"

//tutti i sensori di temperatura del mosto sono a contatto
MustTemperatureSensor::MustTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, true, temp, th), timer(0) {}
double MustTemperatureSensor::stdDeviation = 3.0;
//funzione che genera dati secondo una distribuzione uniforme
void MustTemperatureSensor::generate() {
    auto it = getArray().begin();
    double min = getExpValue() - stdDeviation;
    double max = getExpValue() + stdDeviation;
    unsigned int h, m;
    //misurazioni ogni mezzora da 0 alla fine del timer
    for (double i; i < timer; i += 0.5, ++it) {
        h = int(i);
        m = int((i - h)*6);
        it->setTime(h,m);
        double temperature = min * (2 * stdDeviation) * rand() / max;
        it->setValue(temperature);
    }
}