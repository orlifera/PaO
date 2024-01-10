#include "../headers/mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QLabel *label = new QLabel("Hello World");
    label->setAlignment(Qt::AlignCenter);
    // setCentralWidget(label);
}

MainWindow::~MainWindow()
{
    // Cleanup if needed
}