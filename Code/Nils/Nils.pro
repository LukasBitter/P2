QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nils
TEMPLATE = app

HEADERS += \
    connexion.h \
    gamer.h \
    node.h \
    map.h \
    squad.h \
    identitytoken.h \
    gamerinterface.h \
    gamescene.h \
    powerinterface.h \
    power.h

SOURCES += \
    connexion.cpp \
    gamer.cpp \
    main.cpp \
    node.cpp \
    map.cpp \
    squad.cpp \
    identitytoken.cpp \
    gamerinterface.cpp \
    gamescene.cpp \
    powerinterface.cpp \
    power.cpp

OTHER_FILES += \
    Notes.txt
