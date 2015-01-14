#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T16:14:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleRTS
TEMPLATE = app


SOURCES += main.cpp \
    room/client.cpp \
    room/index.cpp \
    room/player.cpp \
    room/server.cpp \
    map/connexion.cpp \
    map/gamer.cpp \
    map/gamerinterface.cpp \
    map/identitytoken.cpp \
    map/map.cpp \
    map/node.cpp \
    map/parsermap.cpp \
    map/power.cpp \
    map/squad.cpp \
    room/clientaffichage.cpp \
    GameInterface/button.cpp \
    GameInterface/gamerinterface.cpp \
    GameInterface/powerinterface.cpp \
    GameInterface/progressbar.cpp \
    GameComponent/connexion.cpp \
    GameComponent/gamer.cpp \
    GameComponent/gamescene.cpp \
    GameComponent/identitytoken.cpp \
    GameComponent/map.cpp \
    GameComponent/node.cpp \
    GameComponent/squad.cpp

HEADERS  += \
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
    map/squad.h \
    room/clientaffichage.h \
    GameInterface/button.h \
    GameInterface/gamerinterface.h \
    GameInterface/powerinterface.h \
    GameInterface/progressbar.h \
    GameComponent/connexion.h \
    GameComponent/gamer.h \
    GameComponent/gamescene.h \
    GameComponent/identitytoken.h \
    GameComponent/map.h \
    GameComponent/node.h \
    GameComponent/squad.h \
    ennum.h
