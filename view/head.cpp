#include "../headers/head.h"
#include "../headers/tab.h"

HeadWidget::HeadWidget(QString t, Tab *tb, QWidget *parent) : QWidget(parent), tab(tb)
{
    title = new QLabel(this);
    title->setText(t);
    saveBtn = new QPushButton("Save", this);
    renameBtn = new QPushButton("Rename", this);
    deleteBtn = new QPushButton("Delete", this);
    title->setStyleSheet("font-size: 20pt; text-transform: uppercase; font-weight: bold; padding-left: 95px;");
    saveBtn->setFixedWidth(100);
    renameBtn->setFixedWidth(100);
    deleteBtn->setFixedWidth(100);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addSpacing(10);
    layout->addWidget(title, 2);
    layout->addWidget(saveBtn);
    layout->addWidget(renameBtn);
    layout->addWidget(deleteBtn);

    this->setLayout(layout);

    connect(saveBtn, &QPushButton::pressed, tab, &Tab::save);
    connect(renameBtn, &QPushButton::pressed, tab, &Tab::rename);
    connect(deleteBtn, &QPushButton::pressed, tab, &Tab::deleteGroup);
}

void HeadWidget::refresh(QString t) { title->setText(t); }