#include "../headers/winery.h"
#include "../headers/sensorvisitor.h"

// tutti i sensori di temperatura di una cantina non sono a contatto
WineryTemperatureSensor::WineryTemperatureSensor(string n, double temp, double th) : TemperatureSensor(n, false, temp, th) {}

double WineryTemperatureSensor::range = 0.5;

// funzione che genera dati seocndo una distribuzione uniforme
void WineryTemperatureSensor::generate()
{
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> distribution(getExpValue() - range / 2.0, getExpValue() + range / 2.0);
    unsigned int h, m;
    // misurazione ogni mezzora (48 totali)
    for (double i = 0.0; i < 24.0; i += 0.5)
    {
        h = int(i);
        m = int(abs((i - h)) * 60);
        Data d;
        d.setTime(h, m);
        double temperature = distribution(generator);
        d.setValue(temperature);
        push(d);
    }
}

QJsonObject WineryTemperatureSensor::classSensor() const
{
    QString className = "winery-temperature";
    QString classInfo = "false";
    QJsonObject classObj;
    classObj["class"] = className;
    classObj["contact"] = classInfo;
    return classObj; //
}

void WineryTemperatureSensor::accept(SensorVisitor &visitor)
{
    visitor.visitWinery();
}