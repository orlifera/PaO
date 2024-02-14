#pragma once
#include "include.h"
#include "qtHeader.h"
#include "tab.h"

// classe che rappresenta l'intestazione di una tab
class HeadWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;               // puntatore alla tab che contiene l'head
    QLabel *title;          // puntatore al titolo del gruppo
    QPushButton *saveBtn;   // puntatore al bottone di salvataggio del gruppo
    QPushButton *renameBtn; // puntatore al bottone di modifica del gruppo
    QPushButton *deleteBtn; // puntatore al bottone di eliminazione del gruppo

public:
    HeadWidget(QString, Tab *, QWidget *parent = 0);
    // refresh dell'intero head
    void refresh(QString);
};