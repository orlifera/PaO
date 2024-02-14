#pragma once
#include "sensorvisitor.h"

// classe che rappresenta le informazioni contenute nei sensori visualizzabili tramite visitor
class SensorInfo : public SensorVisitor
{
private:
    QWidget *widget; // puntatore ad un widget contenitore di informazioni sui sensori
    bool ismust;     // attributo booleano per individuare un sensore di temperatura del mosto

public:
    // ritorna il widget
    QWidget *getWidget();
    void visitAir();
    void visitAtm();
    void visitBarrel();
    void visitMust(MustTemperatureSensor &);
    void visitSoil();
    void visitVines();
    void visitWinery();
    // ritorna il valore booleano
    bool isMust();
};