#include "../headers/head.h"
#include "../headers/tab.h"

HeadWidget::HeadWidget(QString t, Tab *tb, QWidget *parent) : QWidget(parent), tab(tb)
{
    title = new QLabel(this);
    title->setText(t);
    saveBtn = new QPushButton("Save", this);
    renameBtn = new QPushButton("Rename", this);
    deleteBtn = new QPushButton("Delete", this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(saveBtn);
    layout->addWidget(renameBtn);
    layout->addWidget(deleteBtn);

    this->setLayout(layout);

    connect(saveBtn, &QPushButton::pressed, tab, &Tab::save);
    connect(renameBtn, &QPushButton::pressed, tab, &Tab::rename);
    connect(deleteBtn, &QPushButton::pressed, tab, &Tab::deleteGroup);
}

void HeadWidget::refresh(QString t) { title->setText(t); }