#include "lobbywindow.h"
#include <QPushButton>

LobbyWindow::LobbyWindow(QWidget *parent) :
    QWidget(parent)
{
    startButton = new QPushButton("Start", this);
}
