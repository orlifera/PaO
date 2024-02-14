#pragma once
#include "group.h"
#include "include.h"
#include "qtHeader.h"

// definizioni incomplete
class HeadWidget;
class BodyWidget;

// classe che rapppresenta una tab nel tabwidget
class Tab : public QWidget
{

    Q_OBJECT;

private:
    HeadWidget *head; // puntatore all'intestazione contenuta nella tab
    BodyWidget *body; // puntatore al corpo della tab
    QTabWidget *tabs; // puntatore al tabwidget che contiene la tab
    string path;      // path di salvataggio del gruppo associato alla tab
    Group *group;     // gruppo associato alla tab

public:
    Tab(Group *, QTabWidget *, string = "", QWidget *parent = 0);
    // ritorna il vettore dei puntatori a sensore del gruppo associato alla tab
    vector<Sensor *> getVector() const;
    // ritorna il puntatore al gruppo
    Group *getGroup() const;
public slots:
    // salvataggio del gruppo
    void save();
    // modifica del gruppo
    void rename();
    // eliminazione del gruppo
    void deleteGroup();
};