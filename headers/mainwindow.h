#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "include.h"
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QGridLayout>
#include <QLabel>
// #include <QtCharts>

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
    // QChartView *chartView;

    void SetGUI();
};

#endif // MAINWINDOW_H
