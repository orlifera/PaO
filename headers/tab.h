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
    string path;
    Group *group;

public:
    Tab(Group *, QTabWidget *, string = "", QWidget *parent = 0);
    vector<Sensor *> getVector() const;
    Group *getGroup() const;
public slots:
    void save();
    void rename();
    void deleteGroup();
};