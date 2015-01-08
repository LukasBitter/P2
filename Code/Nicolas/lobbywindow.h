#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QWidget>

class QPushButton;

class LobbyWindow : public QWidget
{
    Q_OBJECT
public:
    LobbyWindow(QWidget *parent = 0);
    QPushButton* startButton;
private:




};

#endif // LOBBYWINDOW_H
