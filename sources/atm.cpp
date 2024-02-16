#include "../headers/atm.h"
#include "../headers/sensorvisitor.h"

// tutti i sensori per la pressione atmosferica hanno come valore atteso 1.0
AtmPressureSensor::AtmPressureSensor(string n, double th) : PressureSensor(n, 1.0, th) {}

double AtmPressureSensor::stdDeviation = 0.5;
double AtmPressureSensor::meanPoisson = 0.1;

// funzione che genera dati secondo una distribuzione mista
// viene utilizzata una distribuzione normale nella quale
// alcuni valori vengono modificati da eventi improvvisi
// dovuti alla distribuzione di poisson
// questo per simulare cambi di pressione (alta o bassa)
void AtmPressureSensor::generate()
{
    random_device rd;
    default_random_engine generator(rd());
    normal_distribution<double> gauss(getExpValue(), stdDeviation);
    poisson_distribution<int> poisson(meanPoisson);
    unsigned int h, m;
    // misurazine ogni ora e mezza
    for (double i = 0.0; i < 24.0; i += 1.5)
    {
        h = int(i);
        m = int(abs((i - h)) * 6);
        Data d;
        d.setTime(h, m);
        double pressure = gauss(generator);
        int events = poisson(generator);
        if (events > 0)
        {
            if (pressure >= 0.7 && pressure <= 1.2)
            {
                pressure += (events % 2 == 0) ? 0.2 : -0.2;
            }
            // Limita il risultato all'intervallo [0, 2]
            pressure = max(0.5, min(1.5, pressure));
            pressure += (events % 2 == 0) ? 0.2 : -0.2;
            d.setValue(pressure);
            push(d);
        }
    }
}

QJsonObject AtmPressureSensor::classSensor() const
{
    QString className = "atm-pressure";
    QJsonObject classObj;
    classObj["class"] = className;
    return classObj;
}

void AtmPressureSensor::accept(SensorVisitor &visitor)
{
    visitor.visitAtm();
}