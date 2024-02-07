#pragma once
#include "include.h"
#include "qtHeader.h"
#include "group.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

private:
    QTabWidget *tabs;

public:
    MainWindow(QWidget *parent = 0);
    // public slots:
    //     void filterList(const QString &query);
private slots:
    void openGroup();
    void newGroup();
    void closeApp();
    // void deleteGroup(Group *);
};
