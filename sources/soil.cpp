#include "../headers/soil.h"
#include "../headers/sensorvisitor.h"

// tutti i sensori per l'umidità del terreno non sono capacitativi
SoilHumiditySensor::SoilHumiditySensor(string n, double humidity, double th) : HumiditySensor(n, false, humidity, th) {}

double SoilHumiditySensor::logStdDeviation = 0.5;

// funzione che genera dati secondo una distribuzione log-normale
// questo perché la distribuzione log-normale descrive bene
// la variazione dell'umidità del terreno che dipende da un gran numero
// di fattori indipendenti come il tipo di irrigazione, la locazione, la flora ecc..
void SoilHumiditySensor::generate()
{
    random_device rd;
    default_random_engine generator(rd());
    lognormal_distribution<double> distribution(getExpValue(), logStdDeviation);
    // 8 misurazioni al giorno
    for (unsigned int hour = 0; hour < 24; hour += 3)
    {
        Data d;
        d.setTime(hour);
        double humidity = distribution(generator) * 100.0;
        humidity = max(0.0, min(100.0, humidity));
        d.setValue(humidity);
        push(d);
    }
}

QJsonObject SoilHumiditySensor::classSensor() const
{
    QString className = "soil-humidity";
    QString classInfo = "false";
    QJsonObject classObj;
    classObj["class"] = className;
    classObj["capacitative"] = classInfo;
    return classObj;
}

void SoilHumiditySensor::accept(SensorVisitor &visitor)
{
    visitor.visitSoil();
}