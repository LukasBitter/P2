#ifndef WELCOMEMENU_H
#define WELCOMEMENU_H

#include <QWidget>

class QPushButton;

namespace GameMenu {
    class WelcomeMenu;
}

class WelcomeMenu : public QWidget
{
    Q_OBJECT

public:
    WelcomeMenu(QWidget *parent = 0);

    QPushButton* btHostGame;
    QPushButton* btJointGame;
    QPushButton* btQuit;

signals:
    void btHostGamePressed();
    void btJointGamePressed();
    void btQuitPressed();

private slots:
    void onBtHostGamePressed();
    void onBtJointGamePressed();
    void onBtQuitPressed();
};

#endif // WELCOMEMENU_H
