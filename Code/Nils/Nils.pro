QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

TARGET = Nils
TEMPLATE = app

HEADERS += \
    GameComponent/connexion.h \
    GameComponent/gamer.h \
    GameComponent/node.h \
    GameComponent/map.h \
    GameComponent/squad.h \
    GameComponent/identitytoken.h \
    GameComponent/gamescene.h \
    GameInterface/powerinterface.h \
    GameConnexion/client.h \
    GameConnexion/server.h \
    GameInterface/Powers/power.h \
    GameInterface/Powers/powerarmore.h \
    GameInterface/Powers/powerdestroy.h \
    GameInterface/Powers/powerinvincibility.h \
    GameInterface/Powers/powerteleportation.h \
    GameInterface/button.h \
    GameInterface/ennum.h \
    GameInterface/progressbar.h \
    GameMenu/gamemenumanager.h \
    GameMenu/lobbymenu.h \
    GameMenu/welcomemenu.h \
    gamecontext.h \
    GameConnexion/gameserver.h \
    enumLib.h \
    GameComponent/gamerlist.h \
    GameConnexion/gameclient.h

SOURCES += \
    GameComponent/connexion.cpp \
    GameComponent/gamer.cpp \
    main.cpp \
    GameComponent/node.cpp \
    GameComponent/map.cpp \
    GameComponent/squad.cpp \
    GameComponent/identitytoken.cpp \
    GameComponent/gamescene.cpp \
    GameInterface/powerinterface.cpp \
    GameConnexion/client.cpp \
    GameConnexion/server.cpp \
    GameInterface/Powers/power.cpp \
    GameInterface/Powers/powerarmore.cpp \
    GameInterface/Powers/powerdestroy.cpp \
    GameInterface/Powers/powerinvincibility.cpp \
    GameInterface/Powers/powerteleportation.cpp \
    GameInterface/button.cpp \
    GameInterface/progressbar.cpp \
    GameMenu/gamemenumanager.cpp \
    GameMenu/lobbymenu.cpp \
    GameMenu/welcomemenu.cpp \
    gamecontext.cpp \
    GameConnexion/gameserver.cpp \
    GameComponent/gamerlist.cpp \
    GameConnexion/gameclient.cpp

OTHER_FILES += \
    Notes.txt

FORMS +=
