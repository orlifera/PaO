#pragma once
#include "atm.h"
#include "air.h"
#include "barrel.h"
#include "must.h"
#include "soil.h"
#include "vines.h"
#include "winery.h"

// classe che identifica un gruppo di sensori dotato di funzione per la loro gestione
class Group
{
private:
    string groupName;         // nome del gruppo
    vector<Sensor *> sensors; // vettore di puntatori ai sensori contenuti nel gruppo

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
    bool find(string) const;
    // rinomina gruppo
    void rename(string);
    // salva gruppo
    void save(string) const;
    // carica grupppo
    static Group *load(string);
    // carica sensore nel gruppo
    Sensor *loadSensor(string);
    // crea nuovo sensore nel gruppo
    Sensor *newSensor(string, double, double, string);
};