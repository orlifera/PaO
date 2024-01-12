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
    Sensor(string, /*string,*/ vector<Data>, double, double = 0);
    Data getInfo(int) const;       // ritorna dato fornendo la posizione
    string getName() const;        // ritorna nome
    string getCategory() const;    // ritorna categoria
    vector<Data> getArray() const; // ritorna il vettore dati
    double getExpValue() const;    // ritorna il valore atteso
    double getThreshold() const;   // ritorna la soglia
    void setExpValue(double);      // assegna nuovo valore atteso
    void setThreshold(double);     // assegna nuova soglia
    virtual void generate() = 0;   // metodo astratto per la generazione dei dati
    void renameSensor(string);     // rinomina il sensore
    // controlla che l'ultimo dato del sensore sia all'interno della soglia
    int isInThreshold() const;
    void push(Data &);           // permette il push di un Data in infoArray (privato)
    virtual ~Sensor() = default; // distruttore di default virtuale
};