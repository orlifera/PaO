#include "../headers/barrel.h"

BarrelPressureSensor::BarrelPressureSensor(string n, double pressure, double th) : PressureSensor(n,pressure,th) {}
double BarrelPressureSensor::stdDeviation = 0.5;
//funzione che genera dati secondo una distribuzione normale
//questi dati vengono sommati al valore della pressione attesa
//cioè dati che devono rimanere intorno al valore desiderato
void BarrelPressureSensor::generate() {
    random_device rd;
    default_random_engine generator(rd());
    normal_distribution<double> distribution(0.0,stdDeviation);
    //misurazine ogni 3 ore
    for (unsigned int hour = 0; hour < 24; hour += 3) {
        Data d;
        d.setTime(hour);
        double pressureChange = distribution(generator);
        double pressure = getExpValue() + pressureChange;
        d.setValue(pressure);
        push(d);
    }
}
string BarrelPressureSensor::classSensor() const { return "\"class\": \"barrel-pressure\",\n"; }