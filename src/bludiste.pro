#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T14:03:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bludiste
TEMPLATE = app


SOURCES += main.cpp \
           board.cpp \
           graphics/mainwindow.cpp \
    graphics/painter.cpp \
    element.cpp

HEADERS  += board.h \
            element.h \
            player.h \
            sentry.h \
            object.h \
    graphics/painter.h \
    graphics/mainwindow.h

FORMS    += mainwindow.ui
