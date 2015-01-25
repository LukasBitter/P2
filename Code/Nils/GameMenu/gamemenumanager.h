#ifndef GAMEMENUMANAGER_H
#define GAMEMENUMANAGER_H

#include <QMainWindow>

class WelcomeMenu;
class EndGameMenu;
class LobbyMenu;
class EditView;
class QWidget;
class QStackedLayout;
class GameView;

namespace GameMenu
{
    class GameMenuManager;
}

/**
 * @class GameMenuManager
 * @brief Wiget de gestion des menu de l'application
 */
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
    void gameFinished(bool victory);

private:
    /*INTERFACE*/
    QWidget *centralWidget;
    QStackedLayout *layout;
    WelcomeMenu *welcomemenu;
    EndGameMenu *endgamemenu;
    LobbyMenu *lobbymenu;
    EditView *editormenu;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // GAMEMENUMANAGER_H
