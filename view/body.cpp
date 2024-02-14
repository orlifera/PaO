#include "../headers/body.h"
#include "../headers/tab.h"
#include "../headers/sensorinfo.h"

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
    // per ogni sensore creo un bottone che connette parte destra con sinistra
    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        connection(*it);
    }

    connect(searchBar, &QLineEdit::textChanged, this, &BodyWidget::filterList);
    layout->addWidget(searchBar);

    QPushButton *addBtn = new QPushButton("Add", listWidget);
    addBtn->setFixedHeight(40);
    QPushButton *loadBtn = new QPushButton("Load", listWidget);
    loadBtn->setFixedHeight(40);

    layout->addWidget(listWidget);

    QWidget *btnContainer = new QWidget(left);
    QHBoxLayout *layoutBtn = new QHBoxLayout(btnContainer);

    layoutBtn->addWidget(addBtn);
    layoutBtn->addWidget(loadBtn);
    btnContainer->setLayout(layoutBtn);

    layout->addWidget(btnContainer);
    left->setLayout(layout);

    connect(addBtn, &QPushButton::pressed, this, &BodyWidget::newSensor);
    connect(loadBtn, &QPushButton::pressed, this, &BodyWidget::loadSensor);
}

void BodyWidget::connection(Sensor *sensor)
{
    QPushButton *btn = new QPushButton(QString::fromStdString(sensor->getName()), listWidget);
    btn->setFixedHeight(40);
    btn->setStyleSheet("font-weight: bold;");
    // colorazione del bottone in base alla threshold:
    // rosso = troppo caldo, troppo umido o pressione troppo alta
    // blu = troppo freddo, troppo poco umido o pressione troppo bassa
    // nessun colore = regolare
    if (!(sensor->getArray().empty()))
    {
        if (sensor->isInThreshold() == 1)
            btn->setStyleSheet("background-color: red; font-weight: bold;");
        if (sensor->isInThreshold() == -1)
            btn->setStyleSheet("background-color: dodgerblue; font-weight: bold;");
    }
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(100, 40));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, btn);
    // connessione del bottone con la parte destra
    connect(btn, &QPushButton::pressed, [this, sensor]()
            { viewRight(sensor); });
}

void BodyWidget::viewRight(Sensor *sensor)
{
    QLayoutItem *item;
    // controllo che la parte destra sia vuota
    while ((item = rightlayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    createRight(sensor);
}

void BodyWidget::createRight(Sensor *sensor)
{
    QWidget *container = new QWidget(right);
    QVBoxLayout *container_layout = new QVBoxLayout(container);
    container_layout->setAlignment(Qt::AlignTop);

    QWidget *subcontainer1 = new QWidget(container);
    QWidget *subcontainer2 = new QWidget(container);
    QWidget *subcontainer3 = new QWidget(container);
    QWidget *subcontainer4 = new QWidget(container);

    QHBoxLayout *subcont1_layout = new QHBoxLayout(subcontainer1);
    QHBoxLayout *subcont2_layout = new QHBoxLayout(subcontainer2);
    QHBoxLayout *subcont3_layout = new QHBoxLayout(subcontainer3);
    QHBoxLayout *subcont4_layout = new QHBoxLayout(subcontainer4);

    // icona
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QPixmap *icon = new QPixmap("../icons/" + QString::fromStdString(sensor->getIcon()));
    *icon = icon->scaled(QSize(25, 25), Qt::KeepAspectRatio);
    QLabel *iconLabel = new QLabel(subcontainer1);
    iconLabel->setPixmap(*icon);

    // nome del sensore
    QLabel *subtitle = new QLabel(subcontainer1);
    subtitle->setText(QString::fromStdString(sensor->getName()));
    subtitle->setFont(QFont("Arial", 14, QFont::Bold));
    subtitle->setStyleSheet("text-transform: uppercase");
    subtitle->setFixedWidth(300);

    subcont1_layout->addWidget(iconLabel);
    subcont1_layout->addWidget(subtitle);

    // valore atteso
    QLabel *exp = new QLabel(subcontainer2);
    exp->setText("Expected Value: " + QString::number(sensor->getExpValue(), 'f', 2));
    exp->setFont(QFont("Arial", 12));
    exp->setFixedWidth(200);

    subcont2_layout->addWidget(exp);

    // soglia
    QLabel *thr = new QLabel(subcontainer2);
    thr->setText("Threshold: " + QString::number(sensor->getThreshold(), 'f', 2));
    thr->setFont(QFont("Arial", 12));
    thr->setFixedWidth(200);
    thr->setStyleSheet("padding-left: 20px;");

    subcont2_layout->addWidget(thr);

    // visitor per informazioni specifiche
    SensorInfo *visitor = new SensorInfo();
    sensor->accept(*visitor);
    subcont2_layout->addWidget(visitor->getWidget());

    // bottoni per azioni sul sensore
    QPushButton *generateBtn = new QPushButton("Generate", subcontainer4);
    generateBtn->setFixedWidth(100);
    QPushButton *saveBtn = new QPushButton("Save Sensor", subcontainer4);
    saveBtn->setFixedWidth(100);
    QPushButton *deleteBtn = new QPushButton("Delete Sensor", subcontainer4);
    deleteBtn->setFixedWidth(100);
    QPushButton *modifyBtn = new QPushButton("Modify Sensor", subcontainer4);
    modifyBtn->setFixedWidth(100);

    connect(generateBtn, &QPushButton::pressed, [this, sensor]()
            { generate(sensor); });
    connect(saveBtn, &QPushButton::pressed, [this, sensor]()
            { saveSensor(sensor); });
    connect(deleteBtn, &QPushButton::pressed, [this, sensor]()
            { deleteSensor(sensor); });
    connect(modifyBtn, &QPushButton::pressed, [this, sensor, visitor]()
            { modifySensor(sensor, visitor); });

    // creazione del chart
    QWidget *chartView = createChart(sensor);

    subcont3_layout->addWidget(chartView, 0, Qt::AlignLeft);

    subcont4_layout->addWidget(generateBtn);
    subcont4_layout->addWidget(saveBtn);
    subcont4_layout->addWidget(deleteBtn);
    subcont4_layout->addWidget(modifyBtn);

    subcontainer1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    subcontainer1->setFixedWidth(200);
    subcontainer2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    subcontainer1->setLayout(subcont1_layout);
    subcontainer2->setLayout(subcont2_layout);
    subcontainer3->setLayout(subcont3_layout);
    subcontainer4->setLayout(subcont4_layout);

    container_layout->addWidget(subcontainer1);
    container_layout->addWidget(subcontainer2);
    container_layout->addWidget(subcontainer3);
    container_layout->addWidget(subcontainer4);

    rightlayout->addWidget(container);
    right->setLayout(rightlayout);
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

    // form per ottenimento dei dati per la creazione del sensore
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

        // Sensor *s = tab->getGroup()->Group::newSensor(name, exp, thr, selectedClass);
        Sensor *s = Sensor::newSensor(name, exp, thr, selectedClass);
        tab->getGroup()->addSensor(s);
        connection(s); // colleamento del sensore alla listwidget e alla parte destra
    }
}

void BodyWidget::loadSensor()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Sensor"), "C://");
    if (path.isEmpty())
    {
        qDebug() << "No file selected.";
        return;
    }

    qDebug() << "Loading sensor from path: " << path;

    if (!tab)
    {
        qDebug() << "Error: 'tab' pointer is null.";
        return;
    }

    // Group *group = tab->getGroup();
    // if (!group)
    // {
    //     qDebug() << "Error: 'group' pointer is null.";
    //     return;
    // }
    // Sensor *s = group->loadSensor(path.toStdString());
    Sensor *s = Sensor::load(path.toStdString());
    tab->getGroup()->addSensor(s);

    if (s)
    {
        qDebug() << "Sensor loaded successfully: " << QString::fromStdString(s->getName());
        connection(s);
    }
    else
    {
        qDebug() << "Failed to load sensor.";
    }
}

void BodyWidget::generate(Sensor *sensor)
{
    sensor->clear();
    sensor->generate();
    refresh();
    createRight(sensor);
}

void BodyWidget::saveSensor(Sensor *sensor)
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setWindowTitle("Save Sensor");
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString directoryPath = dialog.selectedFiles().first();

        QString fileName = QString::fromStdString(sensor->getName());
        QString filePath = QDir(directoryPath).filePath(fileName);
        string path = filePath.toStdString();
        if (exists(path))
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "The file already exists, by continuing you are going to replace it.\nDo you want to continue?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::No)
            {
                return;
            }
        }
        sensor->save(path);
    }
}

void BodyWidget::deleteSensor(Sensor *sensor)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "This sensor in this group is going to be deleted.\nAre you sure you want to delete this sensor?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        string name = sensor->getName();
        for (int i = 0; i < listWidget->count(); ++i)
        {
            QListWidgetItem *item = listWidget->item(i);
            QWidget *widget = listWidget->itemWidget(item);
            QPushButton *sensorBtn = qobject_cast<QPushButton *>(widget);

            if (sensorBtn && sensorBtn->text() == QString::fromStdString(name))
            {
                listWidget->removeItemWidget(item);
                break;
            }
        }

        if (sensor)
        {
            if (tab->getGroup()->find(name))
                tab->getGroup()->removeSensor(sensor);
            refresh();
        }
    }
}

void BodyWidget::modifySensor(Sensor *sensor, SensorInfo *visitor)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Select an Option");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QButtonGroup *buttonGroup = new QButtonGroup(&dialog);

    QRadioButton *renameBtn = new QRadioButton("Rename", &dialog);
    QRadioButton *changeExpBtn = new QRadioButton("Change Expected Value", &dialog);
    QRadioButton *changeThrBtn = new QRadioButton("Change Threshold", &dialog);

    layout->addWidget(renameBtn);
    layout->addWidget(changeExpBtn);
    layout->addWidget(changeThrBtn);

    buttonGroup->addButton(renameBtn);
    buttonGroup->addButton(changeExpBtn);
    buttonGroup->addButton(changeThrBtn);

    // possibilità di modificare il timer solo per i sensori di temperatura del mosto
    QRadioButton *changeTimer = new QRadioButton("Change Timer", &dialog);
    if (visitor->isMust())
    {
        layout->addWidget(changeTimer);
        buttonGroup->addButton(changeTimer);
    }
    else
    {
        delete changeTimer;
    }

    QPushButton *okBtn = new QPushButton("OK", &dialog);
    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout->addWidget(okBtn);

    if (dialog.exec() == QDialog::Accepted)
    {
        QAbstractButton *selectedBtn = buttonGroup->checkedButton();
        if (selectedBtn == renameBtn)
        {
            bool ok;
            QString text = QInputDialog::getText(this, tr("Rename Sensor"), tr("Sensor name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                sensor->rename(text.toStdString());
            }
        }
        else if (selectedBtn == changeExpBtn)
        {
            bool ok;
            QString text = QInputDialog::getText(this, tr("Change Expected Value"), tr("Expected Value:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                sensor->setExpValue(text.toDouble());
            }
        }
        else if (selectedBtn == changeThrBtn)
        {
            bool ok;
            QString text = QInputDialog::getText(this, tr("Change Threshold"), tr("Threshold:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                sensor->setThreshold(text.toDouble());
            }
        }
        else if (visitor->isMust() && selectedBtn == changeTimer)
        {
            bool ok;
            QString text = QInputDialog::getText(this, tr("Change Timer"), tr("Timer:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                MustTemperatureSensor *must = dynamic_cast<MustTemperatureSensor *>(sensor);
                must->setTimer(text.toDouble());
            }
        }
        refresh();
        createRight(sensor);
    }
}

void BodyWidget::refresh()
{
    listWidget->clear();
    QLayoutItem *item;
    while ((item = rightlayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    vector<Sensor *> sensors = tab->getVector();
    for (auto it = sensors.begin(); it != sensors.end(); ++it)
    {
        connection(*it);
    }
}

QWidget *BodyWidget::createChart(Sensor *sensor)
{
    QChart *chart = new QChart();
    chart->setTitle(QString::fromStdString(sensor->getName()) + " Chart");
    chart->legend()->setVisible(false);

    QLineSeries *series = new QLineSeries();
    // minimo e massimo double per il confronto
    double minY = numeric_limits<double>::max();
    double maxY = numeric_limits<double>::lowest();
    // per ogni dato nel vettore
    for (const Data &d : sensor->getArray())
    {
        double value = d.getValue();
        // aggiungo il dato al grafico
        series->append(d.getTime(), value);
        // trovo minimo e massimo
        minY = min(minY, value);
        maxY = max(maxY, value);
    }

    // allargo la visualizzazione del grafico
    double expectedValue = sensor->getExpValue();
    double upperThresholdValue = expectedValue + sensor->getThreshold();
    double lowerThresholdValue = expectedValue - sensor->getThreshold();
    minY = min(minY, lowerThresholdValue);
    maxY = max(maxY, upperThresholdValue);
    minY--;
    maxY++;

    chart->addSeries(series);

    // asse x
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Time (sec)");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // asse y
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(QString::fromStdString(sensor->getUnit()));
    // set del minimo e del massimo
    axisY->setMin(minY);
    axisY->setMax(maxY);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // colorazione della linea dei valori ottenuti
    series->setPen(QPen(QColor(Qt::red), 2));
    series->setPointsVisible(true);
    series->setPointLabelsFormat("@yPoint");
    series->setPointLabelsVisible(true);
    series->setPointLabelsFormat("%.2f");
    series->setUseOpenGL(true);

    if (!series->points().isEmpty())
    {

        // linea che identifica la soglia superiore
        QLineSeries *upperThreshold = new QLineSeries();
        upperThreshold->append(series->points().first().x(), upperThresholdValue);
        upperThreshold->append(series->points().last().x(), upperThresholdValue);
        chart->addSeries(upperThreshold);

        // linea che identifica la soglia inferiore
        QLineSeries *lowerThreshold = new QLineSeries();
        lowerThreshold->append(series->points().first().x(), lowerThresholdValue);
        lowerThreshold->append(series->points().last().x(), lowerThresholdValue);
        chart->addSeries(lowerThreshold);

        upperThreshold->attachAxis(axisX);
        upperThreshold->attachAxis(axisY);
        lowerThreshold->attachAxis(axisX);
        lowerThreshold->attachAxis(axisY);

        upperThreshold->setPen(QPen(QColor(Qt::green), 2, Qt::DashLine));
        lowerThreshold->setPen(QPen(QColor(Qt::green), 2, Qt::DashLine));
    }

    // visualizzazione del grafico e delle sue dimensioni
    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumSize(800, 400);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}