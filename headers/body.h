#pragma once
#include "include.h"
#include "qtHeader.h"
#include "tab.h"

class BodyWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;
    QWidget *left;
    QListWidget *listWidget;
    QWidget *right;

public:
    BodyWidget(Tab *, QWidget *parent = 0);
    void createLeft();
    void createRight();
    void showRight(Sensor *);
    void filterList(const QString &);
    void populate(vector<Sensor *>);
};