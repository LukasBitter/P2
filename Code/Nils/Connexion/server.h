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
class QHostAddress;
class Gamer;
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    int getPort();

private slots:
    void sessionOpened();
    void onNewClientRequest();
    void readRequest();
    //void clientClosed(int number);
    //void gameEnds(int winner);

private:
    QLabel *statusLabel;
    QLabel *lPlayerH;
    QLabel *lPlayersConnectedH;
    QLabel *lPlayersReadyH;
    QList<QTcpSocket *> clientConnections;
    QList<QTcpSocket *> clientWaitingList;
    QPushButton *quitButton;
    QPushButton *runButton;
    QTcpServer *tcpServer;
    //QList<QTcpSocket *> clientConnections;
    //QTcpSocket *clientConnection[];
    QTcpSocket *activeSocket;
    QDataStream in;
    QNetworkSession *networkSession;
    QByteArray block;
    quint16 blockSize;
    QString clientMessage;
    QString *tabStr;
    //QString playerId;
    int playerNumber;
    bool gameRunning;
    int clientsConnectedNb;
    int playersInGame;
    int winner;
    int maxPts;
    int maxPlayers;
    void init();
    void setUI();
    bool getDataStream();
    void getClientRequest();
    void sendMessage();
    void sendPlayerStatus();
    void sendClientResponse(QString ConnectionMsg);
    bool checkAvailableSocket();
    QString playerReady();
    QString checkPlayerName(QString msg);
    QString parse(QString clientMessage);
    QString getPlayersStatus();
    void deletePlayer(QString playerNumber);
    void sendAllUsersStatus();
    void endConversation();
    void checkPlayersConnected();
    QString getHostIp();
    bool isLinkLocalAddress(QHostAddress addr);
    bool isLocalIp(QHostAddress addr);

signals:
    void endGame(int winner);
    void playerWinsGame();
};

#endif // SERVER_H
