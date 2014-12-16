#ifndef DELETEGAME_H
#define DELETEGAME_H

#include <QWidget>

class QLabel;
class QPushButton;
class QLCDNumber;

class deleteGame : public QWidget
{
    Q_OBJECT

    QLCDNumber *lPlayer1Text;
    QLCDNumber *lPlayer2Text;
    QPushButton *bAdd;
    QPushButton *bDel;
    int pts;
    int maxPts;
    int playersNb;
    int maxPlayers;
    void init();

public:
    deleteGame(QWidget *parent = 0);
    ~deleteGame();

public slots:
    void delPts();
    void addPts();
    void delPtsOponent();
    void gameEnds(int winner);

signals:
    void endGame(int winner);
};

#endif // DELETEGAME_H
