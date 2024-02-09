#include "../headers/mainWindow.h"
#include "../headers/tab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    checked = false;
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    tabs = new QTabWidget(mainWidget);
    tabs->setTabsClosable(true);
    connect(tabs->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(tabs);

    welcome = new QLabel(mainWidget);
    welcome->setText("There are no open groups");
    welcome->setStyleSheet("font-size: 16pt;");
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
    Group *g = Group::load("C:\\Users\\david\\OneDrive\\Desktop\\PaO\\fss.json");
    Tab *t = new Tab(g, tabs, "../ffs.json");
    tabs->addTab(t, QString::fromStdString(g->getGroupName()));
    tabs->setCurrentWidget(t);
    firstView();
}

void MainWindow::closeTab(int index)
{
    QWidget *widget = tabs->widget(index);
    QDialog dialog(this);

    QGridLayout *layout = new QGridLayout(&dialog);
    dialog.setWindowTitle("Confirmation");
    QLabel *warning = new QLabel(&dialog);
    warning->setText("Make sure to save this group.\nBy closing this tab without saving\nyou'll lose all current changes.\nDo you want to close the tab?");
    QPushButton *yesBtn = new QPushButton("YES", &dialog);
    QPushButton *noBtn = new QPushButton("NO", &dialog);
    QCheckBox *checkBtn = new QCheckBox("Don't ask this again", &dialog);

    warning->setAlignment(Qt::AlignCenter);
    warning->setFixedWidth(300);
    yesBtn->setFixedWidth(50);
    noBtn->setFixedWidth(50);

    QSpacerItem *spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addWidget(warning, 0, 0, 1, 5);
    layout->addItem(spacer, 1, 0, 1, 5);
    layout->addWidget(yesBtn, 2, 1);
    layout->addWidget(noBtn, 2, 3);
    layout->addWidget(checkBtn, 3, 0, 1, 5);

    connect(yesBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(noBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(checkBtn, &QPushButton::clicked, [this]()
            { checked = true; });

    if (checked || dialog.exec() == QDialog::Accepted)
    {
        tabs->removeTab(index);
        firstView();
        delete widget;
    }
    return;
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