#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>

class QLabel;
class QPushButton;
class ClientAffichage;

namespace GameInterface {
    class GameMenu;
}

class GameMenu : public QDialog
{
    Q_OBJECT
public:
    explicit GameMenu(QWidget *parent = 0);
public slots:
    void hostGame();
    void joinGame();
private:
    QPushButton *pbHostGame;
    QPushButton *pbJoinGame;
    QPushButton *pbQuit;
    ClientAffichage * affichage;
    const int port;
};

#endif // GAMEMENU_H
