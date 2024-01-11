#include "../headers/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SetGUI();
}

MainWindow::~MainWindow()
{
    // Cleanup if needed
}

void MainWindow::SetGUI()
{
    // Creates main widget
    QWidget *mainWidget = new QWidget(this);
    this->setCentralWidget(mainWidget);

    layout = new QGridLayout(mainWidget);

    // sensor list for laterl panel
    sensors = new QListWidget(this);
    layout->addWidget(sensors);
}