#pragma once
#include "include.h"
#include "qtHeader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QListWidget *sensors;
    QTextEdit *sensorDisplay;
    QMenuBar *topMenu;
    QGridLayout *layout;
    // QtChartView *chartView;

    void SetGUI();
};
