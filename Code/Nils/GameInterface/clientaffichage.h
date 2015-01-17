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

/**
 * @class ClientAffichage
 * @brief Menu salon de connexion
 */
class ClientAffichage : public QWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit ClientAffichage(int port, QWidget *parent = 0, bool isHost = false);
    ~ClientAffichage();

    /*SIGNALS/SLOTS*/
private slots:
    void updateScreen();
    void userNameTaken();

private:
    /*INTERFACE*/
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

    /*OUTIL*/
    Client *client;
    Server *server;

    /*METHODE PRIVE*/
    void setUI();

    void setStatusLabel(int status);
    void userNameOk();
};

#endif // CLIENTAFFICHAGE_H
