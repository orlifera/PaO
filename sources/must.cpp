#include "../headers/must.h"

//tutti i sensori di temperatura del mosto sono a contatto
MustTemperatureSensor::MustTemperatureSensor(string n, vector<Data> v, double temp, double t, double th) : TemperatureSensor(n, v, true, temp, th), timer(t) {
    if (t < 0) timer = 0.0;
    if (t > 24) timer = 24.0;
}
double MustTemperatureSensor::range = 3;
//funzione che genera dati secondo una distribuzione uniforme
void MustTemperatureSensor::generate() {
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> distribution(getExpValue() - range / 2.0, getExpValue() + range / 2.0);
    unsigned int h, m;
    //misurazioni ogni mezzora da 0 alla fine del timer
    for (double i = 0.0; i < timer; i += 0.5) {
        h = int(i);
        m = int((i - h)*6);
        Data d;
        d.setTime(h,m);
        double temperature = distribution(generator);
        d.setValue(temperature);
        push(d);
    }
}