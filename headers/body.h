#pragma once
#include "include.h"
#include "qtHeader.h"
#include "tab.h"

class BodyWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;
    QWidget *left;
    QListWidget *listWidget;
    QWidget *right;
    QVBoxLayout * rightlayout;

public:
    BodyWidget(Tab *, QWidget *parent = 0);
    void createLeft();
    void createRight(Sensor *);
    void filterList(const QString &);
    void connection(Sensor *);
private slots:
    void newSensor();
    void viewRight(Sensor *);
};