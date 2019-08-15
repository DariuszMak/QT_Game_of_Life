#-------------------------------------------------
#
# Project created by QtCreator 2015-01-01T10:40:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projekt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    conwayalg.cpp \
    help.cpp \
    settingwindow.cpp

HEADERS  += mainwindow.h \
    conwayalg.h \
    help.h \
    settingwindow.h

FORMS    += mainwindow.ui \
    help.ui \
    settingwindow.ui
