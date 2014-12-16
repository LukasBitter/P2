#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>

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
    QLabel *statusLabel;
    QPushButton *getConnectionButton;
    QPushButton *runButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    deleteGame *game;
    QString playerId;
    void setPlayerId();

    //QByteArray block;
    QDataStream in;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;

    QNetworkSession *networkSession;
};

#endif // CLIENT_H
