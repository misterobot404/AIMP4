#-------------------------------------------------
#
# Project created by QtCreator 2016-06-29T11:25:56
#
#-------------------------------------------------
RC_FILE = app.rc

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AIMP4
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    buttons.qrc
