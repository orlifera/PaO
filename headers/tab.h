#pragma once
#include "group.h"
#include "include.h"
#include "qtHeader.h"

class HeadWidget;
class BodyWidget;

class Tab : public QWidget
{

    Q_OBJECT;

private:
    HeadWidget *head;
    BodyWidget *body;
    QTabWidget *tabs;
    Group *group;

public:
    Tab(Group *, QTabWidget *, QWidget *parent = 0);
public slots:
    void save();
    void rename();
    void deleteGroup();
    void generate(Sensor *);
};