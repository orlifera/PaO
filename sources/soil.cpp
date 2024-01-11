#include "../headers/soil.h"

//tutti i sensori per l'umidità del terreno non sono capacitativi
SoilHumiditySensor::SoilHumiditySensor(string n, vector<Data> v, double humidity, double th) : HumiditySensor(n, v, false, humidity, th) {}
double SoilHumiditySensor::logStdDeviation = 0.5;
//funzione che genera dati secondo una distribuzione log-normale
//questo perché la distribuzione log-normale descrive bene
//la variazione dell'umidità del terreno che dipende da un gran numero
//di fattori indipendenti come il tipo di irrigazione, la locazione, la flora ecc..
void SoilHumiditySensor::generate() {
    random_device rd;
    default_random_engine generator(rd());
    lognormal_distribution<double> lognormal(getExpValue(), logStdDeviation);
    auto it = getArray().begin();
    //8 misurazioni al giorno
    for (unsigned int hour; hour < 24 || it != getArray().end(); hour += 3, ++it) {
        it->setTime(hour);
        double humidity = lognormal(generator) * 100.0;
        humidity = max(0.0, min(100.0, humidity));
        it->setValue(humidity);
    }
}