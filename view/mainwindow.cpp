#include "../headers/mainwindow.h"
#include "../headers/sensorButton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SetGUI();

    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::filterList);
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
    // QListWidget *sensors = new QListWidget(this);
    sensors = new QListWidget(this);

    searchBar = new QLineEdit(sideMenu);
    searchBar->setPlaceholderText("Search...");
    searchBar->setStyleSheet("QLineEdit { height: 20px; }");

    // Create a separator
    QFrame *line = new QFrame(sideMenu);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #c0c0c0;"); // Adjust color as needed

    QLabel *Title = new QLabel(sideMenu);
    Title->setText("Sensors"); // add groupName

    sideMenuLayout->addWidget(searchBar);
    sideMenuLayout->addWidget(line);
    sideMenuLayout->addWidget(Title);

    // Create a tab widget
    QWidget *widget1 = new QWidget();
    QWidget *widget2 = new QWidget();
    // set colors for the tab widgets
    widget1->setStyleSheet("background-color: #000000;");
    widget2->setStyleSheet("background-color: #ffffff;");

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(widget1, "Tab 1");
    tabWidget->addTab(widget2, "Tab 2");
    tabWidget->setTabsClosable(true); // Enable closable tabs
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

    sideMenuLayout->addWidget(sensors);

    // Sensor display (right side)
    QWidget *dataView = new QWidget(mainWidget);
    QVBoxLayout *dataViewLayout = new QVBoxLayout(dataView);

    // QTextEdit *sensorDisplay = new QTextEdit(this);
    dataViewLayout->addWidget(tabWidget);

    mainLayout->addWidget(sideMenu, 0, 0); // Add left column at row 0, column 0
    mainLayout->addWidget(dataView, 0, 1); // Add right column at row 0, column 1

    // Create a menu bar
    QMenuBar *topMenu = new QMenuBar(this);
    QMenu *file = topMenu->addMenu(tr("&New"));

    // Add actions to the file menu
    file->addAction(tr("New Sensor"), this, SLOT(newSensor()));
    file->addAction(tr("New Group"), this, SLOT(newGroup()));

    QMenu *open = topMenu->addMenu(tr("&Open"));
    open->addAction(tr("Open Sensor"), this, SLOT(openSensor()));
    open->addAction(tr("Open Group"), this, SLOT(openGroup()));

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
        // connect(sensorBtn, &QPushButton::clicked, this, [this, i]()
        //         {
        //             // when the sensor button is clicked it should remove the display of the group and add teh display of the sensor clicked in the same place as the group info were displayed before
        //         });
    }

    // Set the layout for the central widget
    mainWidget->setLayout(mainLayout);
}

void MainWindow::addTab()
{
    QTabWidget *tabWidget = findChild<QTabWidget *>();
    if (tabWidget)
    {
        QWidget *newTab = new QWidget();
        newTab->setStyleSheet("background-color: #cccccc;"); // Set a default color or style
        tabWidget->addTab(newTab, tr("New Tab"));
    }
}

void MainWindow::closeTab(int index)
{
    QTabWidget *tabWidget = findChild<QTabWidget *>();
    if (tabWidget)
    {
        QWidget *tabItem = tabWidget->widget(index);
        tabWidget->removeTab(index);
        delete tabItem;
    }
}

void MainWindow::filterList(const QString &query)
{
    for (int i = 0; i < sensors->count(); ++i)
    {
        QListWidgetItem *item = sensors->item(i);
        QWidget *widget = sensors->itemWidget(item);
        SensorBtn *sensorBtn = qobject_cast<SensorBtn *>(widget);

        if (sensorBtn)
        {
            bool match = sensorBtn->text().contains(query, Qt::CaseInsensitive);
            item->setHidden(!match);
        }
    }
}