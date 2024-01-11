#include "../headers/winery.h"

//tutti i sensori di temperatura di una cantina non sono a contatto
WineryTemperatureSensor::WineryTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, false, temp, th) {}
double WineryTemperatureSensor::range = 0.5;
//funzione che genera dati seocndo una distribuzione uniforme
void WineryTemperatureSensor::generate() {
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> distribution(getExpValue() - range / 2.0, getExpValue() + range / 2.0);
    unsigned int h,m;
    //misurazione ogni mezzora (48 totali)
    for (double i = 0.0; i < 24.0; i += 0.5) {
        h = int(i);
        m = int((i - h)*6);
        Data d;
        d.setTime(h,m);
        double temperature = distribution(generator);
        d.setValue(temperature);
        push(d);
    }
}