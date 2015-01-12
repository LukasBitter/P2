QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

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
    power.h \
    powerarmore.h \
    powerdestroy.h \
    powerinvincibility.h \
    powerteleportation.h \
    button.h

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
    power.cpp \
    powerarmore.cpp \
    powerdestroy.cpp \
    powerinvincibility.cpp \
    powerteleportation.cpp \
    button.cpp

OTHER_FILES += \
    Notes.txt
