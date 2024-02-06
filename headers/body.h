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
    QWidget *right;

public:
    BodyWidget(Tab *, QWidget *parent = 0);
};