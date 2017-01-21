#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T22:24:37
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DMF_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    layout.cpp \
    electrode.cpp \
    PathHandler.cpp \
    NewLayout.cpp \
    ClickHandler.cpp \
    Arduino.cpp \
    LayoutDesign.cpp \
    Droplet.cpp \
    DropletSelector.cpp \
    Time.cpp \
    table.cpp

HEADERS  += mainwindow.h \
    electrode.h \
    layout.h \
    PathHandler.h \
    NewLayout.h \
    ClickHandler.h \
    Arduino.h \
    LayoutDesign.h \
    Droplet.h \
    DropletSelector.h \
    Time.h \
    table.h

FORMS    += mainwindow.ui \
    NewLayout.ui \
    LayoutDesign.ui \
    DropletSelector.ui
