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
    character.cpp \
    square.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    server.h \
    client.h \
    character.h \
    square.h \
    board.h

FORMS    += mainwindow.ui

LIBS    += -lboost_system \
           -pthread
