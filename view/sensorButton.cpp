#include "../headers/sensorButton.h"

void SensorBtn::setSensor(const Sensor &sensor)
{
    // Set the sensor name
    sensorName->setText(QString::fromStdString(sensor.getName()));

    // Set the sensor category
    // sensorCategory->setText(QString::fromStdString(sensor.getCategory()));

    getSensorIcon(sensor);
}

QIcon SensorBtn::getSensorIcon(const Sensor &sensor)
{
    QString iconPath;

    iconPath = ":../icons/temp.png";
    // if (sensor.getCategory() == "temperature")
    //     iconPath = ":/icons/temperature_icon.png";

    // else if (sensor.getCategory() == "humidity")
    // {
    //     iconPath = ":/icons/humidity_icon.png";
    // }
    // else if (sensor.getCategory() == "pressure")
    // {
    //     iconPath = ":/icons/pressure_icon.png";
    // }
    // else
    // {
    //     iconPath = ":../icons/unknown.png";
    // }

    if (!iconPath.isEmpty())
    {
        QIcon buttonIcon(iconPath);
        this->setIcon(buttonIcon);
        this->setIconSize(QSize(20, 20)); // Adjust size as needed
    }
}