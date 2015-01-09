#ifndef INDEX_H
#define INDEX_H

#include <QDialog>
#include "server.h"
#include "client.h"
#include "deletegame.h"

class QLabel;
class QPushButton;

class index : public QDialog
{
    Q_OBJECT
    QPushButton *pbNewGame;
    QPushButton *pbJoinGame;
    QPushButton *pbQuit;
    Server *server;
    Client * client;

public:
    explicit index(QWidget *parent = 0);

signals:

public slots:
    void initNewgame();
    void joinGame();

};

#endif // INDEX_H
