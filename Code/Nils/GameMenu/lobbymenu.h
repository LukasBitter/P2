#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QWidget>
#include "GameConnexion/client.h"
#include "GameConnexion/server.h"
#include "enumlibrary.h"

class QPushButton;
class QTableWidget;
class QCheckBox;
class QComboBox;
class QTextEdit;
class QLineEdit;
class GameClient;
class GameServer;
class GameContext;
class QLabel;

namespace GameMenu {
    class LobbyMenu;
}

class LobbyMenu : public QWidget
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    LobbyMenu(QWidget *parent = 0);

    /*SIGNALS/SLOTS*/
signals:
    void returnToMenu();
    void play(GameContext *gc);
    void mapSelectionUpdate();

public slots:
    void enableClientUI();
    void enableServerUI();

private slots:
    void updateUI();
    void launchGame();
    void showError(QAbstractSocket::SocketError err);
    void showMessage(NETWORK_INFORMATION err);
    void onBtReturnPressed();
    void onBtConnectPressed();
    void onBtStartPressed();
    void onBtChangeNamePressed();
    void onBtReadyPressed();
    void onSuccessfulConnexion();
    void onAddMap(QString s);
    void onCbbColorChanged(int i);
    void onCbbSlotChanged(int i);

private:
    /*INTERFACE*/
    QLineEdit *txtAdressIP;
    QLabel *txtName;
    QPushButton *btChangeName;
    QPushButton *btConnect;
    QTableWidget *tblStatus;
    QComboBox *cbbMap;
    QCheckBox *cbtReady;
    QComboBox *cbbSlot;
    QComboBox *cbbColor;
    QPushButton *btStart;
    QPushButton *btReturn;
    QLabel *txtConnected;

    /*OUTIL*/
    bool host;
    int const maxGamer;
    GameServer *server;
    GameClient *client;

    /*METHODE PRIVE*/
    void setUpUI();
    void disableUI();
    void setClient(GameClient *c);
    void setServer(GameServer* s);

};

#endif // LOBBYMENU_H
