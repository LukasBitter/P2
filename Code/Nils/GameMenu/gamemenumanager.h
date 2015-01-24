#ifndef GAMEMENUMANAGER_H
#define GAMEMENUMANAGER_H

#include <QMainWindow>

class WelcomeMenu;
class LobbyMenu;
class EditView;
class QWidget;
class QStackedLayout;
class GameView;

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
    void goToGame(GameView *w);
    void goToEditor();

private:
    /*INTERFACE*/
    QWidget *centralWidget;
    QStackedLayout *layout;
    WelcomeMenu *welcomemenu;
    LobbyMenu *lobbymenu;
    EditView *editormenu;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // GAMEMENUMANAGER_H
