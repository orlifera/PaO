#include "../headers/mainWindow.h"
#include "../headers/sensorButton.h"
#include "../headers/tab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    tabs = new QTabWidget(mainWidget);
    tabs->setTabsClosable(true);
    connect(tabs->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(tabs);

    welcome = new QLabel(mainWidget);
    welcome->setText("There are no open groups");
    welcome->setStyleSheet("font-size: 16pt; text-transform: uppercase");
    mainLayout->addWidget(welcome, 0, Qt::AlignCenter);
    mainWidget->setLayout(mainLayout);

    firstView();

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->setFixedHeight(30);
    QMenu *menu = menuBar->addMenu("Menu");
    QAction *actionNewGroup = menu->addAction(tr("New Group"));
    QAction *actionOpenGroup = menu->addAction(tr("Open Group"));
    QAction *actionQuit = menu->addAction(tr("Quit"));

    QFont menuBarFont = menuBar->font();
    menuBarFont.setPointSize(12);
    menuBar->setFont(menuBarFont);

    QFont menuFont = menu->font();
    menuFont.setPointSize(12);
    menu->setFont(menuFont);

    connect(actionOpenGroup, &QAction::triggered, this, &MainWindow::openGroup);
    connect(actionNewGroup, &QAction::triggered, this, &MainWindow::newGroup);
    connect(actionQuit, &QAction::triggered, this, &MainWindow::closeApp);

    setMenuBar(menuBar);
}

void MainWindow::closeTab(int index)
{
    QWidget *widget = tabs->widget(index);
    tabs->removeTab(index);
    firstView();
    delete widget;
}

void MainWindow::firstView()
{
    if (tabs->currentIndex() == -1)
    {
        tabs->setVisible(false);
        welcome->setVisible(true);
    }
    else
    {
        tabs->setVisible(true);
        welcome->setVisible(false);
    }
}

void MainWindow::closeApp()
{
    qApp->quit();
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
        tabs->setCurrentWidget(t);
        firstView();
    }
}

void MainWindow::openGroup()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Group"), "C://");
    if (!path.isEmpty())
    {
        Group *g = Group::load(path.toStdString());
        Tab *t = new Tab(g, tabs, path.toStdString());
        tabs->addTab(t, QString::fromStdString(g->getGroupName()));
        tabs->setCurrentWidget(t);
        firstView();
    }
}