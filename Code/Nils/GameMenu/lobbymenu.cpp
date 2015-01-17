#include "lobbymenu.h"
#include "GameConnexion/client.h"
#include "GameConnexion/server.h"

#include <QPushButton>
#include <QTableView>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>

LobbyMenu::LobbyMenu(QWidget *parent) :  QWidget(parent)
{
    setUpUI();
    disableUI();

    connect(btReturn,SIGNAL(clicked()),this,SLOT(onBtReturnPressed()));
}

void LobbyMenu::connectToServer()
{

}

void LobbyMenu::updateStatusTable()
{

}

void LobbyMenu::updateUI()
{

}

void LobbyMenu::play()
{

}

void LobbyMenu::onBtReturnPressed()
{
    emit returnToMenu();
}

void LobbyMenu::setUpUI()
{
    this->btStart = new QPushButton("Start game", this);
    this->cbbReady = new QCheckBox("Ready", this);
    this->cbxMap = new QComboBox(this);
    this->tblStatus = new QTableView(this);
    this->txtAdressIP = new QLineEdit("Enter host IP",this);
    this->btConnect = new QPushButton("Connection",this);
    this->btReturn = new QPushButton("Return",this);

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(txtAdressIP, 0,0,1,2);
    l->addWidget(btConnect, 0,2);
    l->addWidget(tblStatus, 1,0,1,3);
    l->addWidget(cbxMap, 2,0,1,3);
    l->addWidget(btReturn, 3,0);
    l->addWidget(cbbReady, 3,1);
    l->addWidget(btStart, 3,2);

    this->setLayout(l);
}

void LobbyMenu::enableClientUI()
{
    disableUI();
    cbbReady->setEnabled(true);
    btConnect->setEnabled(true);
    txtAdressIP->setEnabled(true);
}

void LobbyMenu::enableServerUI()
{
    disableUI();
    cbxMap->setEnabled(true);
    btStart->setEnabled(true);
    cbbReady->setEnabled(true);
}

void LobbyMenu::disableUI()
{
    cbxMap->setEnabled(false);
    btStart->setEnabled(false);
    cbbReady->setEnabled(false);
    btConnect->setEnabled(false);
    txtAdressIP->setEnabled(false);
}
