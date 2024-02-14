#pragma once
#include "qtHeader.h"

// definizione incompleta
class MustTemperatureSensor;

// classe che rappresenta un visitor al sensore
class SensorVisitor
{
public:
    // funzioni per visitare ogni sottoclasse concreta di sensore
    virtual void visitAir() = 0;
    virtual void visitAtm() = 0;
    virtual void visitBarrel() = 0;
    virtual void visitMust(MustTemperatureSensor &) = 0;
    virtual void visitSoil() = 0;
    virtual void visitVines() = 0;
    virtual void visitWinery() = 0;
    // distruttore virtuale
    virtual ~SensorVisitor() = default;
};