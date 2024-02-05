#include "../headers/tabHandler.h"

int TabHandler::tabCount = 0;

TabHandler::TabHandler(QWidget *parent) : QTabWidget(parent)
{
    // Create a tab widget
    QWidget *widget1 = new QWidget();
    QWidget *widget2 = new QWidget();
    // set colors for the tab widgets
    widget1->setStyleSheet("background-color: #000000;");
    widget2->setStyleSheet("background-color: #ffffff;");

    this->addTab(widget1, "Tab 1");
    this->addTab(widget2, "Tab 2");
    this->setTabsClosable(true); // Enable closable tabs
    connect(this, &QTabWidget::tabCloseRequested, this, &TabHandler::closeTab);
}

void TabHandler::closeTab(int index)
{
    QWidget *tabItem = this->widget(index);
    this->removeTab(index);
    delete tabItem;
}