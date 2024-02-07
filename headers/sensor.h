#pragma once
#include "data.h"
// sensore generico
class Sensor
{
private:
    string name; // nome che lo identifica
    // string category;
    vector<Data> infoArray; // valori effettivi - dati misurati
    double expectedValue;   // valore atteso dallo specifico sensore
    double threshold;       // soglia
public:
    Sensor(string, /*string,*/ double, double);
    // ritorna dato fornendo la posizione
    Data getInfo(int) const;
    // ritorna nome
    string getName() const;
    // ritorna il vettore dati
    vector<Data> getArray() const;
    // ritorna il valore atteso
    double getExpValue() const;
    // ritorna la soglia
    double getThreshold() const;
    // assegna nuovo valore atteso
    void setExpValue(double);
    // assegna nuova soglia
    void setThreshold(double);
    // metodo astratto per la generazione dei dati
    virtual void generate() = 0;
    // rinomina il sensore
    void rename(string);
    // controlla che l'ultimo dato del sensore sia all'interno della soglia
    int isInThreshold() const;
    // permette il push di un Data in infoArray (privato)
    void push(Data &);
    // permette il push di un vettore di dati ovvero l'assegnazione
    void push(vector<Data>);
    // string stringSensor() const;   // ritorna campi dati sensori
    // ritorna il nome della classe polimorficamente
    virtual QJsonObject classSensor() const = 0;
    // scrive su un oggetto json le caratteristiche del sensore
    QJsonObject writeSensor() const;
    // salva sensore
    void save(string) const;
    // carica sensore
    static Sensor *load(string);
    // crea nuovo sensore
    static Sensor *newSensor();
    // distruttore di default virtuale
    virtual ~Sensor() = default;
};