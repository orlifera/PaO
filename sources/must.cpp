#include "../headers/must.h"
// tutti i sensori di temperatura del mosto sono a contatto
MustTemperatureSensor::MustTemperatureSensor(string n, double temp, double th) : TemperatureSensor(n, true, temp, th) {}
double MustTemperatureSensor::range = 3;
double MustTemperatureSensor::timer = 24.0;
// funzione che genera dati secondo una distribuzione uniforme
void MustTemperatureSensor::generate()
{
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> distribution(getExpValue() - range / 2.0, getExpValue() + range / 2.0);
    unsigned int h, m;
    // misurazioni ogni mezzora da 0 alla fine del timer
    for (double i = 0.0; i < timer; i += 0.5)
    {
        h = int(i);
        m = int((i - h) * 6);
        Data d;
        d.setTime(h, m);
        double temperature = distribution(generator);
        d.setValue(temperature);
        push(d);
    }
}
void MustTemperatureSensor::setTimer(double t)
{
    if (t <= 24.0 || t >= 0.0)
        timer = t;
}
QJsonObject MustTemperatureSensor::classSensor() const
{
    QString className = "must-temperature";
    QString classInfo = "true";
    QJsonObject classObj;
    classObj["class"] = className;
    classObj["contact"] = classInfo;
    classObj["timer"] = timer;
    return classObj;
}