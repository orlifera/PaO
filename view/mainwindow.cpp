#include "../headers/mainwindow.h"
#include "../headers/sensorButton.h"

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
    QGridLayout *mainLayout = new QGridLayout(mainWidget);

    QWidget *sideMenu = new QWidget(mainWidget);
    QVBoxLayout *sideMenuLayout = new QVBoxLayout(sideMenu);
    // Sensor list for lateral panel (left side)
    QListWidget *sensors = new QListWidget(this);

    sideMenuLayout->addWidget(sensors);

    // Sensor display (right side)
    QWidget *dataView = new QWidget(mainWidget);
    QVBoxLayout *dataViewLayout = new QVBoxLayout(dataView);

    QTextEdit *sensorDisplay = new QTextEdit(this);
    dataViewLayout->addWidget(sensorDisplay);

    mainLayout->addWidget(sideMenu, 0, 0); // Add left column at row 0, column 0
    mainLayout->addWidget(dataView, 0, 1); // Add right column at row 0, column 1

    // Create a menu bar
    QMenuBar *topMenu = new QMenuBar(this);
    QMenu *file = topMenu->addMenu(tr("&File"));

    // Add actions to the file menu
    file->addAction(tr("Save"), this, SLOT(saveData()));
    file->addAction(tr("Load"), this, SLOT(loadData()));
    file->addAction(tr("New Sensor"), this, SLOT(newSensor()));

    // Set the menu bar
    setMenuBar(topMenu);
    mainLayout->setColumnStretch(0, 20); // Set the stretch factor for the first column to 30
    mainLayout->setColumnStretch(1, 80); // Set the stretch factor for the second column to 70

    // vector<Sensor> sensorArray = {Sensor("Dio Bosco", "temperature", {Data(1, 2)}, 1, 2),
    //                               Sensor("Dio Bosco", "temperature", {Data(1, 2)}, 1, 2),
    //                               Sensor("Dio Bosco", "temperature", {Data(1, 2)}, 1, 2)};

    for (int i = 0; i < 30; ++i)
    {
        // Create a QListWidgetItem with a fixed size
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(100, 40)); // Adjust the size hint as needed

        // Create the custom SensorBtn
        SensorBtn *sensorBtn = new SensorBtn();

        // Set placeholder text
        sensorBtn->setText(QString("Placeholder %1").arg(i + 1));

        // Set a default icon for the button
        // Replace ":/path/to/icon.png" with the actual path to your icon resource
        QIcon icon(":/path/to/icon.png");
        sensorBtn->setIcon(icon);
        sensorBtn->setIconSize(QSize(20, 20)); // Adjust size as needed

        // Add the button to the list
        sensors->addItem(item);
        sensors->setItemWidget(item, sensorBtn);

        // Connect the button's clicked signal to a slot, if needed
        connect(sensorBtn, &QPushButton::clicked, this, [this, i]()
                {
                    // Define what should happen when a placeholder button is clicked
                    // This can be empty if no action is required
                });
    }

    // Set the layout for the central widget
    mainWidget->setLayout(mainLayout);
}
