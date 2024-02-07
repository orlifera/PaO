#include "../headers/body.h"
#include "../headers/tab.h"

BodyWidget::BodyWidget(Tab *t, QWidget *parent) : QWidget(parent), tab(t)
{
    left = new QWidget(this);
    right = new QWidget(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(left);
    layout->addWidget(right);

    this->setLayout(layout);
}