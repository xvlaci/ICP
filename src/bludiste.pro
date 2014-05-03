#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T11:58:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bludiste
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    client.cpp \
    serverwindow.cpp

HEADERS  += mainwindow.h \
    server.h \
    client.h \
    serverwindow.h

FORMS    += mainwindow.ui \
    serverwindow.ui

LIBS    += -lboost_system \
           -pthread
