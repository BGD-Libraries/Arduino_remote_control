#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T12:03:13
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = remote_control
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    crc_check.cpp

HEADERS  += widget.h \
    crc_check.h

FORMS    += widget.ui
