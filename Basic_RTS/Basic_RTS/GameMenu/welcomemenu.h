#ifndef WELCOMEMENU_H
#define WELCOMEMENU_H

#include "global.h"

namespace GameMenu
{
    class WelcomeMenu;
}

/**
 * @class WelcomeMenu
 * @brief Menu principale de l'application
 */
class WelcomeMenu : public QWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    WelcomeMenu(QWidget *parent = 0);

    /*SIGNALS/SLOTS*/
signals:
    void btEditorPressed();
    void btHostGamePressed();
    void btJointGamePressed();
    void btQuitPressed();

private slots:
    void onBtEditorPressed();
    void onBtHostGamePressed();
    void onBtJointGamePressed();
    void onBtQuitPressed();
    void onBtAboutPressed();

private:
    /*INTERFACE*/
    QPushButton* btEditor;
    QPushButton* btHostGame;
    QPushButton* btJoinGame;
    QPushButton* btQuit;
    QPushButton* btAbout;
    QLabel *labelTitle;
    QPixmap background;

    /*METHODE PRIVE*/
    void setUpUI();
    void paintEvent(QPaintEvent *);
};

#endif // WELCOMEMENU_H
