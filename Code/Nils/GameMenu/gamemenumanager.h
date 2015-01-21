#ifndef GAMEMENUMANAGER_H
#define GAMEMENUMANAGER_H

#include <QMainWindow>

class WelcomeMenu;
class LobbyMenu;
class EditorMenu;
class QWidget;
class QStackedLayout;
class GameContext;

namespace GameMenu
{
    class GameMenuManager;
}

class GameMenuManager : public QMainWindow
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    GameMenuManager(QWidget *parent = 0);

    /*SIGNALS/SLOTS*/
public slots:
    void returnToMenu();

private slots:
    void goToLobbyAsHost();
    void goToLobbyAsClient();
    void goToGame(GameContext *gc);
    void goToEditor();

private:
    /*INTERFACE*/
    QWidget *centralWidget;
    QStackedLayout *layout;
    WelcomeMenu *welcomemenu;
    LobbyMenu *lobbymenu;
    EditorMenu *editor;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // GAMEMENUMANAGER_H
