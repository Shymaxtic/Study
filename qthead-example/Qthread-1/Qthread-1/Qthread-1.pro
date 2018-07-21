#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T21:55:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qthread-1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp \
    myworker.cpp

HEADERS  += mainwindow.h \
    mythread.h \
    myworker.h

FORMS    += mainwindow.ui
