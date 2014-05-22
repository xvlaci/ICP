#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T11:58:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bludiste2014
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    client.cpp \
    character.cpp \
    square.cpp \
    board.cpp \
    serverwindow.cpp \
    clientwindow.cpp \
    connectdialog.cpp \
    controller.cpp \
    selectmapdialog.cpp


HEADERS  += mainwindow.h \
    server.h \
    client.h \
    character.h \
    square.h \
    board.h\
    serverwindow.h \
    clientwindow.h \
    connectdialog.h \
    controller.h \
    client_ask.h \
    selectmapdialog.h

FORMS    += mainwindow.ui\
    serverwindow.ui \
    clientwindow.ui \
    connectdialog.ui \
    selectmapdialog.ui

LIBS    += -lboost_system \
           -lboost_thread-mt \
           -pthread
