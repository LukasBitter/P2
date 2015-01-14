#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>

class QLabel;
class QPushButton;
class ClientAffichage;

namespace GameInterface {
class GameMenu;
}

/**
 * @class GameMenu
 * @brief Menu principal de l'application
 */
class GameMenu : public QDialog
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit GameMenu(QWidget *parent = 0);

    /*SIGNALS/SLOTS*/
public slots:
    void hostGame();
    void joinGame();

private:
    /*OUTIL*/
    QPushButton *pbHostGame;
    QPushButton *pbJoinGame;
    QPushButton *pbQuit;
    ClientAffichage * affichage;
    const int port;
};

#endif // GAMEMENU_H
