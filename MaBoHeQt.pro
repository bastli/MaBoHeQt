#-------------------------------------------------
#
# Project created by QtCreator 2014-06-01T13:48:54
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MaBoHeQt
TEMPLATE = app


SOURCES += main.cpp\
        MaBoHeMain.cpp \
    Heater.cpp \
    HeaterCommand.cpp \
    qcustomplot.cpp \
    HeaterResponse.cpp

HEADERS  += MaBoHeMain.hpp \
    Heater.hpp \
    HeaterCommand.hpp \
    qcustomplot.h \
    HeaterResponse.hpp

FORMS    += MaBoHeMain.ui

RESOURCES += \
    images.qrc
