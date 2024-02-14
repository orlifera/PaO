#include "../headers/sensorinfo.h"
#include "../headers/air.h"
#include "../headers/atm.h"
#include "../headers/barrel.h"
#include "../headers/must.h"
#include "../headers/soil.h"
#include "../headers/vines.h"
#include "../headers/winery.h"

QWidget *SensorInfo::getWidget()
{
    return widget;
}

void SensorInfo::visitAir()
{
    widget = new QLabel("Class: air humidity sensor");
    widget->setFont(QFont("Arial", 12));
    widget->setFixedWidth(500);
    ismust = false;
}

void SensorInfo::visitAtm()
{
    widget = new QLabel("Class: atm pressure sensor");
    widget->setFont(QFont("Arial", 12));
    widget->setFixedWidth(500);
    ismust = false;
}

void SensorInfo::visitBarrel()
{
    widget = new QLabel("Class: barrel pressure sensor");
    widget->setFont(QFont("Arial", 12));
    widget->setFixedWidth(500);
    ismust = false;
}

void SensorInfo::visitMust(MustTemperatureSensor &must)
{
    QLabel *t = new QLabel("Timer: " + QString::number(must.getTimer(), 'f', 2));
    t->setFont(QFont("Arial", 12));
    t->setFixedWidth(150);
    QLabel *c = new QLabel("Class: must temperature sensor");
    c->setFont(QFont("Arial", 12));
    c->setStyleSheet("padding-left: -20px;");
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(t);
    layout->addWidget(c);
    widget = new QWidget();
    widget->setLayout(layout);
    ismust = true;
}

void SensorInfo::visitSoil()
{
    widget = new QLabel("Class: soil humidity sensor");
    widget->setFont(QFont("Arial", 12));
    widget->setFixedWidth(500);
    ismust = false;
}

void SensorInfo::visitVines()
{
    widget = new QLabel("Class: vines temperature sensor");
    widget->setFont(QFont("Arial", 12));
    widget->setFixedWidth(500);
    ismust = false;
}

void SensorInfo::visitWinery()
{
    widget = new QLabel("Class: winery temperature sensor");
    widget->setFont(QFont("Arial", 12));
    widget->setFixedWidth(500);
    ismust = false;
}

bool SensorInfo::isMust()
{
    return ismust;
}