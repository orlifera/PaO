#include "../headers/mainWindow.h"
#include "../headers/sensorButton.h"
#include "../headers/tab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    tabs = new QTabWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(tabs);
    mainWidget->setLayout(mainLayout);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menu = menuBar->addMenu("Menu");
    QAction *actionNewGroup = menu->addAction("New Group");
    QAction *actionOpenGroup = menu->addAction("Open Group");

    connect(actionOpenGroup, &QAction::triggered, this, &MainWindow::openGroup);
    connect(actionNewGroup, &QAction::triggered, this, &MainWindow::newGroup);

    setMenuBar(menuBar);
}

void MainWindow::newGroup()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("New Group"), tr("Group name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
        Group *g = new Group(text.toStdString());
        Tab *t = new Tab(g, tabs);
        tabs->addTab(t, text);
    }
}

void MainWindow::openGroup()
{
    bool ok;
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Group"), "C://");
    Group g = Group::load(filename.toStdString());
    Tab *t = new Tab(&g, tabs);
    tabs->addTab(t, filename);
}

// connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::filterList);
// void MainWindow::SetGUI()
// {
// QWidget *sideMenu = new QWidget(mainWidget);
// QVBoxLayout *sideMenuLayout = new QVBoxLayout(sideMenu);
// Sensor list for lateral panel (left side)
// QListWidget *sensors = new QListWidget(this);
// sensors = new QListWidget(this);

// searchBar = new QLineEdit(sideMenu);
// searchBar->setPlaceholderText("Search...");

// Create a separator
//     QFrame *line = new QFrame(sideMenu);
//     line->setFrameShape(QFrame::HLine);
//     line->setFrameShadow(QFrame::Sunken);
//     line->setStyleSheet("color: #c0c0c0;"); // Adjust color as needed

//     QLabel *Title = new QLabel(sideMenu);
//     Title->setText("Sensors"); // add groupName

//     sideMenuLayout->addWidget(searchBar);
//     sideMenuLayout->addWidget(line);
//     sideMenuLayout->addWidget(Title);

//     tabWidget = new TabHandler(this);
//     connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

//     sideMenuLayout->addWidget(sensors);

//     // Sensor display (right side)
//     QWidget *dataView = new QWidget(mainWidget);
//     QVBoxLayout *dataViewLayout = new QVBoxLayout(dataView);

//     // QTextEdit *sensorDisplay = new QTextEdit(this);
//     dataViewLayout->addWidget(tabWidget);

//     mainLayout->addWidget(sideMenu, 0, 0); // Add left column at row 0, column 0
//     mainLayout->addWidget(dataView, 0, 1); // Add right column at row 0, column 1

//     // Create a menu bar
//     QMenuBar *topMenu = new QMenuBar(this);
//     QMenu *file = topMenu->addMenu(tr("&New"));

//     // Add actions to the file menu
//     file->addAction(tr("New Group"), this, SLOT(Group::newGroup()));

//     QMenu *open = topMenu->addMenu(tr("&Open"));
//     file->addAction(tr("Open Group"), this, SLOT(Group::load()));

//     // Set the menu bar
//     // setMenuBar(topMenu);
//     mainLayout->setColumnStretch(0, 20); // Set the stretch factor for the first column to 20
//     mainLayout->setColumnStretch(1, 80); // Set the stretch factor for the second column to 80

//     // for (int i = 0; i < 30; ++i)
//     // {
//     //     // Create a QListWidgetItem with a fixed size
//     //     QListWidgetItem *item = new QListWidgetItem();
//     //     item->setSizeHint(QSize(100, 40)); // Adjust the size hint as needed

//     //     // Create the custom SensorBtn
//     //     SensorBtn *sensorBtn = new SensorBtn();

//     //     // Set placeholder text
//     //     sensorBtn->setText(QString("Placeholder %1").arg(i + 1));

//     //     // Set a default icon for the button
//     //     // Replace ":/path/to/icon.png" with the actual path to your icon resource
//     //     QIcon icon(":/path/to/icon.png");
//     //     sensorBtn->setIcon(icon);
//     //     sensorBtn->setIconSize(QSize(20, 20)); // Adjust size as needed

//     //     // Add the button to the list
//     //     sensors->addItem(item);
//     //     sensors->setItemWidget(item, sensorBtn);

//     //     // Connect the button's clicked signal to a slot, if needed
//     //     // connect(sensorBtn, &QPushButton::clicked, this, [this, i]()
//     //     //         {
//     //     //             // when the sensor button is clicked it should remove the display of the group and add teh display of the sensor clicked in the same place as the group info were displayed before
//     //     //         });
//     // }

//     // Set the layout for the central widget
//     mainWidget->setLayout(mainLayout);
// }

// void MainWindow::tabChanged(int index)
// {
//     // Clear the existing list of buttons
//     sensors->clear();

//     // Add new buttons based on the current tab
//     switch (index)
//     {
//     case 0:
//         // Code to add buttons for Tab 1
//         // Example:
//         addButton("Button 1.1");
//         addButton("Button 1.2");
//         break;

//     case 1:
//         // Code to add buttons for Tab 2
//         // Example:
//         addButton("Button 2.1");
//         addButton("Button 2.2");
//         break;

//         // Add more cases for additional tabs as needed

//     default:
//         break;
//     }
// }

// void MainWindow::addButton(const QString &text)
// {
//     // Create a QListWidgetItem with a fixed size
//     QListWidgetItem *item = new QListWidgetItem();
//     item->setSizeHint(QSize(100, 40));

//     // Create the custom SensorBtn
//     SensorBtn *sensorBtn = new SensorBtn();
//     sensorBtn->setText(text);

//     // Set a default icon for the button
//     QIcon icon(":/path/to/icon.png");
//     sensorBtn->setIcon(icon);
//     sensorBtn->setIconSize(QSize(20, 20));

//     // Add the button to the list
//     sensors->addItem(item);
//     sensors->setItemWidget(item, sensorBtn);
// }

// void MainWindow::addTab()
// {
//     QTabWidget *tabWidget = findChild<QTabWidget *>();
//     if (tabWidget)
//     {
//         QWidget *newTab = new QWidget();
//         newTab->setStyleSheet("background-color: #cccccc;"); // Set a default color or style
//         tabWidget->addTab(newTab, tr("New Tab"));
//     }
// }

// void MainWindow::closeTab(int index)
// {
//     QTabWidget *tabWidget = findChild<QTabWidget *>();
//     if (tabWidget)
//     {
//         QWidget *tabItem = tabWidget->widget(index);
//         tabWidget->removeTab(index);
//         delete tabItem;
//     }
// }

// void MainWindow::filterList(const QString &query)
// {
//     for (int i = 0; i < sensors->count(); ++i)
//     {
//         QListWidgetItem *item = sensors->item(i);
//         QWidget *widget = sensors->itemWidget(item);
//         SensorBtn *sensorBtn = qobject_cast<SensorBtn *>(widget);

//         if (sensorBtn)
//         {
//             bool match = sensorBtn->text().contains(query, Qt::CaseInsensitive);
//             item->setHidden(!match);
//         }
//     }
// }