#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QDataStream>

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;
class Map;

namespace Connexion {
    class Client;
}

class Client
{
    Q_OBJECT
public:
    explicit Client(bool isHost = 0, int port = 0);
    int getMaxPlayers();
private slots:
    void requestNewConnection();
    void readServerResponse();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetConnectionButton();
    void sessionOpened();
    void ReadyRun();
    void runGame();
    void launchGame();

private:
    int playerNumber;
    int playersInGame;
    const int maxPlayers;
    int gameRunning;
    bool isHost;
    Map *game;
    QDataStream in;
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;

    /*METHODE PRIVE*/
    void init();
    void setPlayerNumber(QString number);
    void setStatus(QString msg);
    void sendServerMessage(QString msg);
    void setUsersStatus(QString msg);
    void endConversation();
    QString parse(QString clientMessage);
    QString checkUserNameString();
    void closeEvent( QCloseEvent * event );

};

#endif // CLIENT_H
