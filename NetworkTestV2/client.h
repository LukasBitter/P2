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
class deleteGame;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);

private slots:
    void requestNewConnection();
    void readServerResponse();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetConnectionButton();
    void sessionOpened();
    void ReadyRun();
    void runGame();

private:
    QLabel *hostLabel;
    QLabel *portLabel;
    QComboBox *hostCombo;
    QLineEdit *portLineEdit;
    QLineEdit *userNameLineEdit;
    QLabel *statusLabel;
    QPushButton *getConnectionButton;
    QPushButton *readyButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    deleteGame *game;
    QString playerNumber;
    QString headerOut;
    QString headerIn;
    void setPlayerNumber(QString number);
    void setStatus(QString msg);
    void sendServerMessage(QString msg);
    QList<QString> parse(QString clientMessage);

    //QByteArray block;
    QDataStream in;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;

    QNetworkSession *networkSession;
};

#endif // CLIENT_H
