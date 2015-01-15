#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;
class Map;

namespace Connexions {
    class Client;
}

class Client : QObject
{
    Q_OBJECT
public:
    explicit Client(QString host = "localhost", QObject *parent = 0, int port = 0);
    int getMaxPlayers() const;
    QString *getUserName() const;
    void setUserName(QString *name);
    int getPort() const;
    bool isConnexionOk() const;
    bool isNameOk() const;
    bool isReadyOk() const;

signals:
    void updateClient();
    void errorOccured(QAbstractSocket::SocketError socketError);

public slots:
    void setReady(bool r);
    void requestNewConnection();
    void ReadyRun();

private slots:
    void readServerResponse();
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    //void sessionOpened();

private:
    int playerNumber;
    QString *userName;
    int port;
    QString host;
    bool connexionOk;
    bool nameOk;
    bool readyOk;
    QDataStream in;
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;

    /*METHODE PRIVE*/
    void sendServerMessage(QString msg);
    void setUsersStatus(QString msg);
    void endConversation();
    QString parse(QString serverMessage);
    void closeEvent( QCloseEvent * event );
    void launchGame();

    /*METHODE PRIVE CONSTRUCTION MESSAGE*/
    QString buildStringCheckUserName();
    void buildStringRunGame();
};

#endif // CLIENT_H
