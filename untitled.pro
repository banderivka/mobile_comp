#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T14:31:43
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

SOURCES += main.cpp\
        widget.cpp \
    questionClass.cpp \
    testClass.cpp

HEADERS  += widget.h \
    questionClass.h \
    testClass.h

FORMS    += widget.ui

RESOURCES += \
    icons.qrc \
    files.qrc
