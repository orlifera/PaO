#pragma once
#include "include.h"
#include "qtHeader.h"
#include "sensorinfo.h"
#include "tab.h"

// classe per la rappresentazione del corpo principale della GUI
// rappresenta un'unica unità logica nonostante sia suddivisibile in sottoparti
class BodyWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;                 // puntatore alla tab che contiene questo body
    QWidget *left;            // puntatore alla parte sinistra contenuta in body
    QListWidget *listWidget;  // puntatore alla lista di widget nella parte sinistra
    QWidget *right;           // puntatore alla parte destra contenuta nel body
    QVBoxLayout *rightlayout; // puntatore al layout della parte sinistra

public:
    BodyWidget(Tab *, QWidget *parent = 0);
    // creazione di left
    void createLeft();
    // creazione di right
    void createRight(Sensor *);
    // funzione di filtraggio per la ricerca di sensori nella listWidget
    void filterList(const QString &);
    // funzione di creazione dei bottoni nella listWidget e il loro collegamento a right
    void connection(Sensor *);
    // refresh di tutto il body per aggiornare i cambiamenti avvenuti
    void refresh();
    // creazione del chart del sensore
    QWidget *createChart(Sensor *);
private slots:
    // creazione nuovo sensore
    void newSensor();
    // caricamento nuovo sensore
    void loadSensor();
    // effettivo collegamento tra il bottone in listWidget e la creazione di right
    void viewRight(Sensor *);
    // generazione dati
    void generate(Sensor *);
    // salvataggio del singolo sensore puntato
    void saveSensor(Sensor *);
    // eliminazione del sensore dal gruppo selezionato (non elimina file salvati)
    void deleteSensor(Sensor *);
    // modifica dinamica del sensore
    void modifySensor(Sensor *, SensorInfo *);
};