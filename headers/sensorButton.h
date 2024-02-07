#pragma once
#include "sensor.h"
#include "include.h"
#include "qtHeader.h"

class SensorBtn : public QPushButton
{
    Q_OBJECT
private:
    // QLabel *sensorIcon;
    Sensor *sensor;
    QLabel *sensorName;
    // QLabel *sensorCategory;
    // QIcon getSensorIcon(const Sensor &sensor);

public:
    explicit SensorBtn(Sensor *, QWidget *parent = nullptr);
    void setSensor(Sensor *);
};