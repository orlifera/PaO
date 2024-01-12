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

    sensorDisplay = new QTextEdit(this);
    layout->addWidget(sensorDisplay);

    topMenu = new QMenuBar(this);
    QMenu *file = topMenu->addMenu(tr("&File"));

    file->addAction(tr("Save"), this, SLOT(saveData()));
    file->addAction(tr("Load"), this, SLOT(loadData()));

    setMenuBar(topMenu);

    layout->setMenuBar(topMenu);
    centralWidget()->setLayout(layout);
}
