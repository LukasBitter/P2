#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTcpServer;
class QTcpSocket;
class QNetworkSession;
class QDataStream;
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);

private slots:
    void sessionOpened();
    void onNewClientRequest();
    void readRequest();
    void delPts();
    void addPts();
    //void gameEnds(int winner);

private:
    QLabel *statusLabel;
    //QLabel *lPlayersConnected[];
    //QLabel *lPlayersReady[];
    QList<QLabel> lPlayersConnected;
    QList<QLabel> lPlayersReady;
    int *iPlayersPts[];
    //QLabel *lplayer1Connected;
    //QLabel *lplayer2Connected;
    //QLabel *lplayer3Connected;
    //QLabel *lplayer4Connected;
    QPushButton *quitButton;
    QPushButton *runButton;
    QTcpServer *tcpServer;
    QHash<int, QTcpSocket*> clientConnections;
    //QList<QTcpSocket *> clientConnections;
    //QTcpSocket *clientConnection[];
    QTcpSocket *activeSocket;
    QDataStream in;
    QNetworkSession *networkSession;
    QByteArray block;
    quint16 blockSize;
    QString header;
    QString *tabStr;
    QString msg;
    QString playerId;
    bool gameRunning;
    int clientsConnectedNb;
    int player1ID;
    int player2ID;
    int player3ID;
    int playersInGame;
    int winner;
    int maxPts;
    int maxPlayers;
    void init();
    bool getDataStream();
    void getClientRequest();
    void sendMessage();
    void checkEndGame();
    void sendPlayerStatus();
    void sendClientResponse();
    void buildClientResponse(QString connexionMsg);
    bool checkAvailableSocket();
    void playerReady();

signals:
    void endGame(int winner);
    void playerWinsGame();
};

#endif // SERVER_H
