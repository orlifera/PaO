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

    // Create a grid layout
    QGridLayout *layout = new QGridLayout(mainWidget);

    // Sensor list for lateral panel (left side)
    QListWidget *sensors = new QListWidget(this);
    layout->addWidget(sensors, 0, 0); // Row 0, Column 0

    // Sensor display (right side)
    QTextEdit *sensorDisplay = new QTextEdit(this);
    layout->addWidget(sensorDisplay, 0, 1); // Row 0, Column 1

    // Create a menu bar
    QMenuBar *topMenu = new QMenuBar(this);
    QMenu *file = topMenu->addMenu(tr("&File"));

    // Add actions to the file menu
    file->addAction(tr("Save"), this, SLOT(saveData()));
    file->addAction(tr("Load"), this, SLOT(loadData()));

    // Set the menu bar
    setMenuBar(topMenu);
    layout->setColumnStretch(0, 20); // Set the stretch factor for the first column to 30
    layout->setColumnStretch(1, 80); // Set the stretch factor for the second column to 70

    // Set the layout for the central widget
    centralWidget()->setLayout(layout);
}
