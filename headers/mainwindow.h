#pragma once
#include "include.h"
#include "qtHeader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void filterList(const QString &query);
private slots:
    void tabChanged(int index);

private:
    QListWidget *sensors;
    QTextEdit *sensorDisplay;
    QMenuBar *topMenu;
    QGridLayout *layout;
    QTabWidget *tabWidget;
    QLineEdit *searchBar;
    // QtChartView *chartView;

    void SetGUI();
    void addButton(const QString &text);
    void addTab();
    void closeTab(int index);
    // void filterList(const QString &query);
};
