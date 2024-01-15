#include "../headers/vines.h"

//tutti i sensori per la temperatura nelle vigne non sono a contatto
VinesTemperatureSensor::VinesTemperatureSensor(string n, double temp, double th) : TemperatureSensor(n, false, temp, th) {}
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
    normal_distribution<double> distribution(getExpValue(), stdDeviation);
    //una misurazione all'ora
    for (unsigned int hour = 0; hour < 24; ++hour) {
        Data d;
        d.setTime(hour);
        double temperature = getExpValue() + amplitude * sin(2 * pi * hour / 24.0);
        temperature += distribution(generator);
        d.setValue(temperature);
        push(d);
    }
}
string VinesTemperatureSensor::classSensor() const {
    string jsonString = "\"class\": \"vines-temperature\",\n";
    jsonString += "\"contact\": \"false\",\n";
    return jsonString; 
}