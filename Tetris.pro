#-------------------------------------------------
#
# Project created by QtCreator 2017-07-07T20:48:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    menuwidget.cpp \
    display.cpp \
    square.cpp \
    minidisplay.cpp \
    figure.cpp

HEADERS  += widget.h \
    menuwidget.h \
    display.h \
    square.h \
    minidisplay.h \
    figure.h
