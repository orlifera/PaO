#include "../headers/body.h"
#include "../headers/tab.h"

BodyWidget::BodyWidget(Tab *t, QWidget *parent) : QWidget(parent), tab(t)
{
    left = new QWidget(this);
    right = new QWidget(this);
    rightlayout = new QVBoxLayout(right);
    createLeft();

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
    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        connection(*it);
    }
    connect(searchBar, &QLineEdit::textChanged, this, &BodyWidget::filterList);
    layout->addWidget(searchBar);
    QPushButton *add = new QPushButton("+", listWidget);
    add->setFixedHeight(40);
    layout->addWidget(listWidget);
    layout->addWidget(add);
    left->setLayout(layout);

    connect(add, &QPushButton::pressed, this, &BodyWidget::newSensor);
}

void BodyWidget::createRight(Sensor *sensor)
{
    QWidget *container = new QWidget(right);
    QVBoxLayout *container_layout = new QVBoxLayout(container);
    QWidget *subcontainer1 = new QWidget(container);
    QWidget *subcontainer2 = new QWidget(container);
    QWidget *subcontainer3 = new QWidget(container);
    QHBoxLayout *subcont1_layout = new QHBoxLayout(subcontainer1);
    QHBoxLayout *subcont2_layout = new QHBoxLayout(subcontainer2);
    QHBoxLayout *subcont3_layout = new QHBoxLayout(subcontainer3);
    QLabel *subtitle = new QLabel(subcontainer1);
    QLabel *subtitle_value = new QLabel(subcontainer1);
    subtitle->setText("Sensor Name: ");
    subtitle_value->setText(QString::fromStdString(sensor->getName()));
    subtitle->setFont(QFont("Arial", 11, QFont::Bold));
    subtitle_value->setFont(QFont("Arial", 10));
    subtitle->setFixedWidth(150);
    subtitle_value->setFixedWidth(150);
    QPixmap *icon = new QPixmap("../icons/" + QString::fromStdString(sensor->getIcon()));
    QLabel *iconLabel = new QLabel;
    iconLabel->setPixmap(*icon);
    QLabel *exp = new QLabel(subcontainer2);
    QLabel *exp_value = new QLabel(subcontainer2);
    exp->setText("Expected Value: ");
    exp_value->setText(QString::number(sensor->getExpValue(), 'f', 2));
    exp->setFont(QFont("Arial", 11, QFont::Bold));
    exp_value->setFont(QFont("Arial", 10));
    exp->setFixedWidth(150);
    exp_value->setFixedWidth(150);
    QLabel *thr = new QLabel(subcontainer2);
    QLabel *thr_value = new QLabel(subcontainer2);
    thr->setText("Threshold: ");
    thr_value->setText(QString::number(sensor->getThreshold(), 'f', 2));
    thr->setFont(QFont("Arial", 11, QFont::Bold));
    thr_value->setFont(QFont("Arial", 10));
    thr->setFixedWidth(150);
    thr_value->setFixedWidth(150);
    QPushButton *generateBtn = new QPushButton("Generate", subcontainer3);
    generateBtn->setFixedWidth(100);
    QPushButton *saveBtn = new QPushButton("Save Sensor", subcontainer3);
    saveBtn->setFixedWidth(100);
    QPushButton *deleteBtn = new QPushButton("Delete Sensor", subcontainer3);
    deleteBtn->setFixedWidth(100);
    QPushButton *modifyBtn = new QPushButton("Modify Sensor", subcontainer3);
    modifyBtn->setFixedWidth(100);
    subcont1_layout->addWidget(subtitle);
    subcont1_layout->addWidget(subtitle_value);
    subcont1_layout->addWidget(iconLabel);
    subcont2_layout->addWidget(exp);
    subcont2_layout->addWidget(exp_value);
    subcont2_layout->addWidget(thr);
    subcont2_layout->addWidget(thr_value);
    subcontainer1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    subcontainer2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    subcont3_layout->addWidget(generateBtn);
    subcont3_layout->addWidget(saveBtn);
    subcont3_layout->addWidget(deleteBtn);
    subcont3_layout->addWidget(modifyBtn);
    subcontainer1->setLayout(subcont1_layout);
    subcontainer2->setLayout(subcont2_layout);
    subcontainer3->setLayout(subcont3_layout);
    container_layout->addWidget(subcontainer1);
    container_layout->addWidget(subcontainer2);
    container_layout->addWidget(subcontainer3);
    rightlayout->addWidget(container);
    right->setLayout(rightlayout);
}

// void BodyWidget::showRight(Sensor *sensor)
// {

//     subtitle->setText(QString::fromStdString(sensor->getName()));
//     // QCharts
// }
void BodyWidget::connection(Sensor *sensor)
{
    QPushButton *btn = new QPushButton(QString::fromStdString(sensor->getName()), listWidget);
    btn->setFixedHeight(40);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(100, 40));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, btn);
    connect(btn, &QPushButton::pressed, [this, sensor]()
            { viewRight(sensor); });
}

void BodyWidget::viewRight(Sensor *sensor)
{
    QLayoutItem *item;
    while ((item = rightlayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    createRight(sensor);
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

void BodyWidget::newSensor()
{
    QDialog dialog;
    dialog.setWindowTitle("New Sensor");

    QFormLayout formLayout(&dialog);

    QLineEdit *sensorName = new QLineEdit(&dialog);
    QLineEdit *sensorExp = new QLineEdit(&dialog);
    QLineEdit *sensorThr = new QLineEdit(&dialog);

    QComboBox *classBox = new QComboBox(&dialog);
    classBox->addItem("air-humidity");
    classBox->addItem("soil-humidity");
    classBox->addItem("atm-pressure");
    classBox->addItem("barrel-pressure");
    classBox->addItem("must-temperature");
    classBox->addItem("vines-temperature");
    classBox->addItem("winery-temperature");

    formLayout.addRow("Sensor Name:", sensorName);
    formLayout.addRow("Expected Value:", sensorExp);
    formLayout.addRow("Threshold:", sensorThr);
    formLayout.addRow("Sensor Class:", classBox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    formLayout.addRow(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        string name = sensorName->text().toStdString();
        double exp = sensorExp->text().toDouble();
        double thr = sensorThr->text().toDouble();
        string selectedClass = classBox->currentText().toStdString();

        Sensor *s = tab->getGroup()->Group::newSensor(name, exp, thr, selectedClass);
        connection(s);
    }
}