#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T21:28:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qplot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotscene.cpp \
    plotview.cpp

HEADERS  += mainwindow.h \
    plotscene.h \
    plotview.h

FORMS    += mainwindow.ui
