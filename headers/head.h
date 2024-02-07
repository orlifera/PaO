#pragma once
#include "include.h"
#include "qtHeader.h"
#include "tab.h"

class HeadWidget : public QWidget
{
    Q_OBJECT;

private:
    Tab *tab;
    QLabel *title;
    QPushButton *saveBtn;
    QPushButton *renameBtn;
    QPushButton *deleteBtn;

public:
    HeadWidget(QString, Tab *, QWidget *parent = 0);
    void refresh(QString);
};