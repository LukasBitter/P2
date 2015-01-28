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
    void onBtHelpPressed();

private:
    /*INTERFACE*/
    QPushButton* btHostGame;
    QPushButton* btJoinGame;
    QPushButton* btEditor;
    QPushButton* btHelp;
    QPushButton* btAbout;
    QPushButton* btQuit;
    QLabel *labelTitle;
    QPixmap background;

    /*METHODE PRIVE*/
    void setUpUI();
    void paintEvent(QPaintEvent *);
};

#endif // WELCOMEMENU_H
