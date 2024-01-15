######################################################################
# Automatically generated by qmake (3.1) Fri Jan 12 19:36:55 2024
######################################################################

TEMPLATE = app
TARGET = Progetto
INCLUDEPATH += .
QT += widgets
QT += charts


# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += headers/air.h \
           headers/atm.h \
           headers/barrel.h \
           headers/data.h \
           headers/functions.h \
           headers/group.h \
           headers/humidity.h \
           headers/include.h \
           headers/mainwindow.h \
           headers/must.h \
           headers/pressure.h \
           headers/qtHeader.h \
           headers/sensor.h \
           headers/sensorButton.h \
           headers/soil.h \
           headers/temperature.h \
           headers/time.h \
           headers/vines.h \
           headers/winery.h
SOURCES += main.cpp \
           sources/air.cpp \
           sources/atm.cpp \
           sources/barrel.cpp \
           sources/data.cpp \
           sources/functions.cpp \
           sources/group.cpp \
           sources/humidity.cpp \
           sources/must.cpp \
           sources/pressure.cpp \
           sources/sensor.cpp \
           sources/soil.cpp \
           sources/temperature.cpp \
           sources/time.cpp \
           sources/vines.cpp \
           sources/winery.cpp \
           view/mainwindow.cpp \
           view/sensorButton.cpp