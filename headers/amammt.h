#pragma once
#include "sensor.h"
#include "include.h"
#include "qtHeader.h"

class amammt : public QPushButton
{
    Q_OBJECT
private:
    // QLabel *sensorIcon;
    QListWidget *list;
    Sensor *sensor;
    QLabel *sensorName;
    // QLabel *sensorCategory;
    // QIcon getSensorIcon(const Sensor &sensor);

public:
    amammt(Sensor *, QListWidget *, QWidget *parent = nullptr);
    void setSensor(Sensor *);
};