#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T16:46:22
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkTest
TEMPLATE = app


SOURCES += main.cpp\
        deletegame.cpp \
    server.cpp \
    index.cpp \
    client.cpp

HEADERS  += deletegame.h \
    server.h \
    index.h \
    client.h
