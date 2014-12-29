QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nils
TEMPLATE = app

HEADERS += \
    connexion.h \
    gamer.h \
    node.h \
    updatable.h \
    widget.h \
    map.h \
    squad.h

SOURCES += \
    connexion.cpp \
    gamer.cpp \
    main.cpp \
    node.cpp \
    widget.cpp \
    map.cpp \
    updatable.cpp \
    squad.cpp

OTHER_FILES += \
    Notes.txt
