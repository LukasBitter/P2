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
    power.h \
    gamerinterface.h \
    gamescene.h

SOURCES += \
    connexion.cpp \
    gamer.cpp \
    main.cpp \
    node.cpp \
    map.cpp \
    squad.cpp \
    identitytoken.cpp \
    power.cpp \
    gamerinterface.cpp \
    gamescene.cpp

OTHER_FILES += \
    Notes.txt
