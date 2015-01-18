#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QWidget>
#include "GameConnexion/client.h"
#include "GameConnexion/server.h"

class QPushButton;
class QTableView;
class QCheckBox;
class QComboBox;
class QTextEdit;
class QLineEdit;
class GameClient;
class GameServer;
class GameContext;

namespace GameMenu {
    class LobbyMenu;
}

class LobbyMenu : public QWidget
{
    Q_OBJECT
public:
    LobbyMenu(QWidget *parent = 0);

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
    void onBtReturnPressed();
    void onBtConnectPressed();
    void onBtStartPressed();
    void onSuccessfulConnexion();

private:
    QComboBox *cbxMap;
    QCheckBox *cbbReady;
    QPushButton *btStart;
    QTableView *tblStatus;
    QLineEdit *txtAdressIP;
    QPushButton *btConnect;
    QPushButton *btReturn;

    void setUpUI();
    void disableUI();

    bool host;
    int const maxGamer;
    GameServer *server;
    GameClient *client;
};

#endif // LOBBYMENU_H
