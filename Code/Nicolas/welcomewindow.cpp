#include "welcomewindow.h"
#include <QPushButton>
WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    lobbyButton = new QPushButton("Lobby",this);
    settingsButton = new QPushButton("Settings",this);
    settingsButton->move(0,30);
}
