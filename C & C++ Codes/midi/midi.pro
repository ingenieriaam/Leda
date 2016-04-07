#-------------------------------------------------
#
# Project created by QtCreator 2015-11-12T14:38:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = midi
TEMPLATE = app


SOURCES += main.cpp\
        midi.cpp

HEADERS  += midi.h

FORMS    += midi.ui

QT+=multimedia
QT+=serialport
