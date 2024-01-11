#include "headers/group.h"
#include "headers/mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1280, 720);
    window.show();

    return app.exec();
}