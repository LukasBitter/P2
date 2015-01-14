#ifndef INDEX_H
#define INDEX_H

#include <QDialog>
#include "room/server.h"
#include "room/client.h"
#include "map/map.h"

class QLabel;
class QPushButton;

class index : public QDialog
{
    Q_OBJECT
    QPushButton *pbHostGame;
    QPushButton *pbJoinGame;
    QPushButton *pbQuit;
    Server *server;
    Client * client;

public:
    explicit index(QWidget *parent = 0);

signals:

public slots:
    void hostGame();
    void joinGame();

};

#endif // INDEX_H
