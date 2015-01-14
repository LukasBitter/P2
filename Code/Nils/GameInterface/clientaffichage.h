#ifndef CLIENTAFFICHAGE_H
#define CLIENTAFFICHAGE_H

#include <QWidget>

class QComboBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class Client;
class Server;

namespace GameInterface {
    class ClientAffichage;
}

class ClientAffichage : public QWidget
{
    Q_OBJECT
public:
    explicit ClientAffichage(int port, QWidget *parent = 0, bool isHost = false);
private slots:
    void updateScreen();
private:
    QComboBox *hostCombo;
    QLineEdit *portLineEdit;
    QLineEdit *userNameLineEdit;
    QPushButton *getConnectionButton;
    QPushButton *readyButton;
    QPushButton *runButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QLabel *statusLabel;
    QList<QLabel *> lPlayersNumbers;
    QList<QLabel *> lPlayersNames;
    QList<QLabel *> lPlayersConnected;
    QList<QLabel *> lPlayersReady;
    Client *client;
    Server *server;

    void setUI();
    void initLabels();

};

#endif // CLIENTAFFICHAGE_H
