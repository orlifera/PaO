#include "../headers/air.h"

//tutti i sensori per l'umidità dell'aria sono capacitativi
AirHumiditySensor::AirHumiditySensor(string n, vector<Data> v, double humidity, double th) : HumiditySensor(n, v, true, humidity, th) {}
double AirHumiditySensor::alpha = 5.0;
double AirHumiditySensor::beta = 2.0;
//funzione che riceve alpha, beta e un generatore randomico
//utilizzando una distribuzione reale uniforme
//restituisce un valore secondo una distribuzione beta
double AirHumiditySensor::beta_distribution(double a, double b, default_random_engine& gen) {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double u1 = distribution(gen);
    double u2 = distribution(gen);
    double x = pow(u1, 1.0/a);
    double y = pow(u2, 1.0/b);
    return x / (x + y);
}
//generatore dei dati che utilizza una distribuzione beta
//questo perché è la distribuzione tra valore 0.0 e 1.0 che meglio
//descrive e rappresenta i dati e le variazioni di umidità nell'aria
void AirHumiditySensor::generate() {
    random_device rd;
    default_random_engine generator(rd());
    //4 misurazioni al giorno
    for (unsigned int hour = 0; hour < 24; hour += 6) {
        Data d;
        d.setTime(hour);
        double humidity = beta_distribution(alpha, beta, generator) * 100.0;
        humidity = max(0.0, min(100.0, humidity));
        d.setValue(humidity);
        push(d);
    }
}