QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

TARGET = Basic_RTS
TEMPLATE = app


PRECOMPILED_HEADER = global.h

HEADERS += \
    GameComponent/Logic/connexion.h \
    GameComponent/Logic/squad.h \
    GameComponent/Logic/identitytoken.h \
    GameComponent/Logic/gamescene.h \
    GameComponent/GameInterface/progressbar.h \
    GameComponent/GameInterface/powerinterface.h \
    GameConnexion/client.h \
    GameConnexion/server.h \
    GameConnexion/gameserver.h \
    GameConnexion/gameclient.h \
    GameMenu/gamemenumanager.h \
    GameMenu/lobbymenu.h \
    GameMenu/welcomemenu.h \
    gamerlist.h \
    gamer.h \
    enumlibrary.h \
    GameComponent/GameInterface/gameview.h \
    mapfile.h \
    GameComponent/EditorInterface/editview.h \
    GameComponent/EditorInterface/editorinterface.h \
    GameComponent/GameInterface/powercountdown.h \
    GameComponent/GameInterface/actionmanager.h \
    GameMenu/endgamemenu.h \
    GameComponent/Logic/nodecombat.h \
    GameComponent/Logic/nodemana.h \
    GameComponent/Logic/node.h \
    GameComponent/Logic/nodeconnectable.h \
    GameComponent/GameInterface/ressourcebar.h \
    GameComponent/GameInterface/ressourcesinterface.h \
    GameComponent/GameInterface/buttonpower.h \
    GameComponent/GameInterface/buttonressource.h

SOURCES += \
    GameComponent/Logic/connexion.cpp \
    GameComponent/Logic/squad.cpp \
    GameComponent/Logic/identitytoken.cpp \
    GameComponent/Logic/gamescene.cpp \
    GameComponent/GameInterface/progressbar.cpp \
    GameComponent/GameInterface/powerinterface.cpp \
    GameConnexion/client.cpp \
    GameConnexion/server.cpp \
    GameConnexion/gameserver.cpp \
    GameConnexion/gameclient.cpp \
    GameMenu/gamemenumanager.cpp \
    GameMenu/lobbymenu.cpp \
    GameMenu/welcomemenu.cpp \
    gamerlist.cpp \
    gamer.cpp \
    main.cpp \
    GameComponent/GameInterface/gameview.cpp \
    mapfile.cpp \
    GameComponent/EditorInterface/editview.cpp \
    GameComponent/EditorInterface/editorinterface.cpp \
    GameComponent/GameInterface/powercountdown.cpp \
    GameComponent/GameInterface/actionmanager.cpp \
    GameMenu/endgamemenu.cpp \
    GameComponent/Logic/nodecombat.cpp \
    GameComponent/Logic/nodemana.cpp \
    GameComponent/Logic/node.cpp \
    GameComponent/Logic/nodeconnectable.cpp \
    GameComponent/GameInterface/ressourcebar.cpp \
    GameComponent/GameInterface/ressourcesinterface.cpp \
    GameComponent/GameInterface/buttonpower.cpp \
    GameComponent/GameInterface/buttonressource.cpp

OTHER_FILES += \
    Notes.txt

FORMS +=

RESOURCES += \
    Graphics/graphics.qrc \
    files.qrc

TRANSLATIONS    = basic_RTS_fr.ts \
                  basic_RTS_de.ts
