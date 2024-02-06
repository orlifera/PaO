#pragma once
#include "include.h"
#include "qtHeader.h"
#include "sensor.h"

class SideWidget : public QWidget
{
    Q_OBJECT;

private:
    QLineEdit *searchbar;
    QListWidget *list;
    vector<Sensor *> sensors;

public:
    SideWidget(vector<Sensor *>, QWidget *parent = 0);
};