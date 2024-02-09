#pragma once
#include "include.h"
#include "qtHeader.h"
#include "group.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

private:
    QTabWidget *tabs;
    QLabel *welcome;
    bool checked;

public:
    MainWindow(QWidget *parent = 0);
    void firstView();
    // public slots:
    //     void filterList(const QString &query);
private slots:
    void openGroup();
    void newGroup();
    void closeApp();
    void closeTab(int);
    // void deleteGroup(Group *);
};
