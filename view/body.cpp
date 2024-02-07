#include "../headers/body.h"
#include "../headers/tab.h"

BodyWidget::BodyWidget(Tab *t, QWidget *parent) : QWidget(parent), tab(t)
{
    left = new QWidget(this);
    right = new QWidget(this);
    createLeft();
    createRight();

    left->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(left, 1);
    layout->addWidget(right, 4);

    this->setLayout(layout);
}

void BodyWidget::createLeft()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLineEdit *searchBar = new QLineEdit(left);
    searchBar->setPlaceholderText("Search...");
    searchBar->setFixedHeight(40);
    listWidget = new QListWidget(left);
    vector<Sensor *> sensors = tab->getVector();
    populate(sensors);
    connect(searchBar, &QLineEdit::textChanged, this, &BodyWidget::filterList);
    layout->addWidget(searchBar);
    layout->addWidget(listWidget);

    left->setLayout(layout);
}

void BodyWidget::createRight()
{
    QVBoxLayout *external_layout = new QVBoxLayout(right);
    QWidget *container = new QWidget(right);
    QVBoxLayout *container_layout = new QVBoxLayout(container);
    QLabel *subtitle = new QLabel(container);
    QPushButton *generateBtn = new QPushButton("generate", container);
    generateBtn->setFixedWidth(100);
    container_layout->addWidget(subtitle);
    container_layout->addWidget(generateBtn, 0, Qt::AlignCenter);
    container->setLayout(container_layout);
    external_layout->addWidget(container);
    right->setLayout(external_layout);
}

// void BodyWidget::showRight(Sensor *sensor)
// {

//     subtitle->setText(QString::fromStdString(sensor->getName()));
//     // QCharts
// }

void BodyWidget::populate(vector<Sensor *> sensors)
{
    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        QPushButton *btn = new QPushButton(QString::fromStdString((*it)->getName()), listWidget);
        btn->setFixedHeight(40);
        QListWidgetItem *item = new QListWidgetItem();
        listWidget->addItem(item);
        listWidget->setItemWidget(item, btn);
        // connect(btn, &QPushButton::clicked, right, [this, it]()
        //         { showRight(*it); });
    }
}
void BodyWidget::filterList(const QString &query)
{
    for (int i = 0; i < listWidget->count(); ++i)
    {
        QListWidgetItem *item = listWidget->item(i);
        QWidget *widget = listWidget->itemWidget(item);
        QPushButton *sensorBtn = qobject_cast<QPushButton *>(widget);

        if (sensorBtn)
        {
            bool match = sensorBtn->text().contains(query, Qt::CaseInsensitive);
            item->setHidden(!match);
        }
    }
}