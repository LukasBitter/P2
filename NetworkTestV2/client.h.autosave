#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QDataStream>


QT_BEGIN_NAMESPACE
class QComboBox;
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
private slots:
    void requestNewConnection();
    void readServerResponse();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetConnectionButton();
    void sessionOpened();
    void ReadyRun();
    void runGame();

private:
    QComboBox *hostCombo;
    QLineEdit *portLineEdit;
    QLineEdit *userNameLineEdit;
    QLabel *statusLabel;
    QList<QLabel *> lPlayersNumbers;
    QList<QLabel *> lPlayersNames;
    QList<QLabel *> lPlayersConnected;
    QList<QLabel *> lPlayersReady;
    int playersInGame;
    int maxPlayers;
    int gameRunning;
    bool isHost;
    QPushButton *getConnectionButton;
    QPushButton *readyButton;
    QPushButton *runButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    Map *game;
    QString playerNumber;
    QString headerOut;
    QString headerIn;
    void setUI();
    void init();
    void setPlayerNumber(QString number);
    void setStatus(QString msg);
    void sendServerMessage(QString msg);
    void setUsersStatus(QString msg);
    QString parse(QString clientMessage);
    QString checkUserNameString();
    void closeEvent( QCloseEvent * event );
    QDataStream in;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;

};

#endif // CLIENT_H
