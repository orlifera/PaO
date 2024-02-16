#pragma once
#include "include.h"
#include "qtHeader.h"
#include "group.h"

// classe che rappresnta la finestra principale della GUI dell'applicazione
class MainWindow : public QMainWindow
{
    Q_OBJECT;

private:
    QTabWidget *tabs; // puntatore al widget che gestisce le tabs
    QWidget *welcome;  // label di benvenuto inizale
    bool checked;     // attributo booleano per la chiusura delle tabs

public:
    MainWindow(QWidget *parent = 0);
    // impone la visione o meno della label di benvenuto in base alla presenza di tabs
    void firstView();
private slots:
    // apre un gruppo salvato
    void openGroup();
    // crea un nuovo gruppo
    void newGroup();
    // chiude l'app
    void closeApp();
    // gestione della chiusura di una tab
    void closeTab(int);
};
