#pragma once
#include "atm.h"
#include "air.h"
#include "barrel.h"
#include "must.h"
#include "soil.h"
#include "vines.h"
#include "winery.h"
class Group
{
private:
    string groupName;
    vector<Sensor *> sensors;

public:
    Group(string);
    // ritorna il nome del gruppo
    string getGroupName() const;
    // ritorna il vettore dei puntatori ai sensori
    vector<Sensor *> getSensors() const;
    // aggiunge un sensore
    void addSensor(Sensor *);
    // rimuove un sensore
    void removeSensor(Sensor *);
    // rimuove un sensore dato il nome
    void removeSensor(string);
    // rimuove un senore data la posizione
    void removeSensor(int);
    // trova un sensore dal nome
    Sensor *find(string) const;
    // rinomina gruppo
    void rename(string);
    // salva gruppo
    void save(string) const;
    // carica grupppo
    static Group *load(string);
    // carica sensore nel gruppo
    void loadSensor();
    // crea nuovo gruppo
    // static Group newGroup();
    // crea nuovo sensore nel gruppo
    void newSensor();
    // Group& operator=(const Group&);
};