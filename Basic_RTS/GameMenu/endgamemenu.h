#ifndef ENDGAMEMENU_H
#define ENDGAMEMENU_H

#include "global.h"

namespace GameMenu
{
    class EndGameMenu;
}

/**
 * @class EndGameMenu
 * @brief Menu de victoire/défaite
 */
class EndGameMenu : public QWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    EndGameMenu(QWidget *parent = 0);

    /*SURCHARGE*/
    void paintEvent(QPaintEvent *);

    /*SIGNALS/SLOTS*/
signals:
    void returnToMenu();

public slots:
    void enableVictory();
    void enableDefeat();

private slots:
    void onBtReturnPressed();

private:
    /*INTERFACE*/
    QPushButton* btReturn;
    QPixmap background;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // ENDGAMEMENU_H
