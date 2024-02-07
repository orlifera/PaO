#include "../headers/sensorButton.h"
SensorBtn::SensorBtn(Sensor *s, QListWidget *l, QWidget *parent = nullptr) : QPushButton(parent), list(l), sensor(s)
{
    // Create labels
    // sensorIcon = new QLabel(this);
    sensorName = new QLabel(this);
    // sensorCategory = new QLabel(this);
    setSensor(sensor);
    // Set up the layout for the button
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sensorName);
    // layout->addWidget(sensorCategory);

    this->setLayout(layout);
}

void SensorBtn::setSensor(Sensor *sensor)
{
    // Set the sensor name
    sensorName->setText(QString::fromStdString(sensor->getName()));

    // Set the sensor category
    // sensorCategory->setText(QString::fromStdString(sensor.getCategory()));

    // getSensorIcon(sensor);
}

// QIcon SensorBtn::getSensorIcon(const Sensor &sensor)
// {
//     QString iconPath;

//     iconPath = ":../icons/temp.png";
//     // if (sensor.getCategory() == "temperature")
//     //     iconPath = ":/icons/temperature_icon.png";

//     // else if (sensor.getCategory() == "humidity")
//     // {
//     //     iconPath = ":/icons/humidity_icon.png";
//     // }
//     // else if (sensor.getCategory() == "pressure")
//     // {
//     //     iconPath = ":/icons/pressure_icon.png";
//     // }
//     // else
//     // {
//     //     iconPath = ":../icons/unknown.png";
//     // }

//     if (!iconPath.isEmpty())
//     {
//         QIcon buttonIcon(iconPath);
//         this->setIcon(buttonIcon);
//         this->setIconSize(QSize(20, 20)); // Adjust size as needed
//     }
// }