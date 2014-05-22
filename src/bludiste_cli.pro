#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T11:58:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bludiste2014_cli
TEMPLATE = app


SOURCES += main_cli.cpp\
    server.cpp \
    client.cpp \
    character.cpp \
    square.cpp \
    board.cpp \
    controller.cpp


HEADERS  += server.h \
    client.h \
    character.h \
    square.h \
    board.h\
    controller.h \
    client_ask.h

LIBS    += -lboost_system \
           -lboost_thread-mt \
           -pthread
