#include "../headers/vines.h"

//tutti i sensori per la temperatura nelle vigne non sono a contatto
VinesTemperatureSensor::VinesTemperatureSensor(string n, vector<Data> v, double temp, double th) : TemperatureSensor(n, v, false, temp, th) {}
double VinesTemperatureSensor::amplitude = 5.0;
double VinesTemperatureSensor::stdDeviation = 3.0;
//funzione che genera dati secondo una distribuzione sinusoidale
//che viene calcolata usando una distribuzione normale (gauss)
//questo perché la variazione di temperatura in una giornata segue
//un andamento periodico
void VinesTemperatureSensor::generate() {
    const double pi = acos(-1);
    random_device rd;
    default_random_engine generator(rd());
    normal_distribution<double> gauss(getExpValue(), stdDeviation);
    //una misurazione all'ora
    auto it = getArray().begin();
    for (unsigned int hour; hour < 24 || it != getArray().end(); ++hour, ++it) {
        it->setTime(hour);
        double temperature = getExpValue() + amplitude * sin(2 * pi * hour / 24.0);
        temperature += gauss(generator);
        it->setValue(temperature);
    }
}