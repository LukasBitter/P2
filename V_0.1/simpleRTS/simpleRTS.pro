#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T16:14:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleRTS
TEMPLATE = app


SOURCES += main.cpp \
    client.cpp \
    index.cpp \
    player.cpp \
    server.cpp \
    room/client.cpp \
    room/index.cpp \
    room/player.cpp \
    room/server.cpp \
    map/connexion.cpp \
    map/gamer.cpp \
    map/gamerinterface.cpp \
    map/identitytoken.cpp \
    map/main.cpp \
    map/map.cpp \
    map/node.cpp \
    map/parsermap.cpp \
    map/power.cpp \
    map/squad.cpp

HEADERS  += \
    index.h \
    player.h \
    server.h \
    room/client.h \
    room/index.h \
    room/player.h \
    room/server.h \
    map/connexion.h \
    map/gamer.h \
    map/gamerinterface.h \
    map/identitytoken.h \
    map/map.h \
    map/node.h \
    map/parsermap.h \
    map/power.h \
    map/squad.h
