#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

class GameBoard : public QFrame
{
    Q_OBJECT

public:
    GameBoard(QWidget *parent = 0);

signals:

public slots:
    void start();
};

#endif // GAMEBOARD_H
