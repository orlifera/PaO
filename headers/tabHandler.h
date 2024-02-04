#pragma once
#include "sensor.h"
#include "include.h"
#include "qtHeader.h"

class TabHandler : public QTabWidget
{
    Q_OBJECT
private:
    static int tabCount;

public:
    TabHandler(QWidget *parent = 0);
};