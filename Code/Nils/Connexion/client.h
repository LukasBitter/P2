#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;
class Map;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0, bool isHost = 0, int port = 0);
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
    int playersInGame;
    const int maxPlayers;
    int gameRunning;
    bool isHost;
    Map *game;
    //QString headerOut;
    //QString headerIn;
    void init();
    void setPlayerNumber(QString number);
    void setStatus(QString msg);
    void sendServerMessage(QString msg);
    void setUsersStatus(QString msg);
    void endConversation();
    QString parse(QString clientMessage);
    QString checkUserNameString();
    void closeEvent( QCloseEvent * event );
    QDataStream in;
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;

};

#endif // CLIENT_H
