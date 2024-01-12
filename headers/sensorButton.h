#pragma once
#include "sensor.h"
#include "include.h"
#include "qtHeader.h"

class SensorBtn : public QPushButton
{
    Q_OBJECT
private:
    QLabel *sensorIcon;
    QLabel *sensorName;
    // QLabel *sensorCategory;
    QIcon getSensorIcon(const Sensor &sensor);

public:
    explicit SensorBtn(QWidget *parent = nullptr) : QPushButton(parent)
    {
        // Create labels
        sensorIcon = new QLabel(this);
        sensorName = new QLabel(this);
        // sensorCategory = new QLabel(this);

        // Set up the layout for the button
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(sensorName);
        // layout->addWidget(sensorCategory);

        this->setLayout(layout);
    }

    void setSensor(const Sensor &sensor);
};