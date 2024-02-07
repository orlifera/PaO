#include "../headers/tab.h"
#include "../headers/head.h"
#include "../headers/body.h"

Tab::Tab(Group *g, QTabWidget *t, QWidget *parent) : QWidget(parent), tabs(t), group(g)
{
    head = new HeadWidget(QString::fromStdString(group->getGroupName()), this);
    body = new BodyWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(head);
    layout->addWidget(body);
    this->setLayout(layout);
}

void Tab::save()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);

    dialog.setWindowTitle("Save Group");
    dialog.setNameFilter("JSON files (*.json)");

    dialog.selectFile("untitled");

    if (dialog.exec() == QDialog::Accepted)
    {
        QString filePath = dialog.selectedFiles().first();

        group->save(filePath.toStdString());
    }
}

void Tab::rename()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Rename Group"), tr("Group name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
        group->Group::rename(text.toStdString());
        head->refresh(text);
        int tabIndex = tabs->indexOf(this);
        tabs->setTabText(tabIndex, text);
    }
}

void Tab::deleteGroup()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete this group?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        string filename = group->getGroupName();
        if (exists(filename))
            remove(filename);
        delete group;
        int tabIndex = tabs->indexOf(this);
        if (tabIndex != -1)
        {
            tabs->removeTab(tabIndex);
        }
        delete this;
    }
}

void Tab::generate(Sensor *sensor)
{
    sensor->generate();
}