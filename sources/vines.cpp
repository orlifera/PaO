#include "../headers/vines.h"
#include "../headers/sensorvisitor.h"

// tutti i sensori per la temperatura nelle vigne non sono a contatto
VinesTemperatureSensor::VinesTemperatureSensor(string n, double temp, double th) : TemperatureSensor(n, false, temp, th) {}

double VinesTemperatureSensor::amplitude = 2.0;
double VinesTemperatureSensor::stdDeviation = 0.8;

// funzione che genera dati secondo una distribuzione sinusoidale
// che viene calcolata usando una distribuzione normale (gauss)
// questo perché la variazione di temperatura in una giornata segue
// un andamento periodico
void VinesTemperatureSensor::generate()
{
    const double pi = acos(-1);
    random_device rd;
    default_random_engine generator(rd());
    normal_distribution<double> distribution(getExpValue(), stdDeviation);
    // una misurazione all'ora
    for (unsigned int hour = 0; hour < 24; ++hour)
    {
        Data d;
        d.setTime(hour);
        double temperature = amplitude * sin(2 * pi * hour / 24.0);
        temperature += distribution(generator);
        d.setValue(temperature);
        push(d);
    }
}

QJsonObject VinesTemperatureSensor::classSensor() const
{
    QString className = "vines-temperature";
    QString classInfo = "false";
    QJsonObject classObj;
    classObj["class"] = className;
    classObj["contact"] = classInfo;
    return classObj;
}

void VinesTemperatureSensor::accept(SensorVisitor &visitor)
{
    visitor.visitVines();
}