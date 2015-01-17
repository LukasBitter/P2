#include "gamecontext.h"
#include "GameConnexion/client.h"
#include "GameConnexion/server.h"
#include "GameConnexion/parser.h"
#include "GameComponent/map.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameContext::GameContext(bool host): QObject(0), maxGamer(4),
    port(8000), numGamer(-1), client(0), server(0), game(0)
{
    parser = new Parser();

    if(host)
    {
        server = new Server(port,maxGamer);
        client = new Client(port);
    }
}


GameContext::~GameContext()
{
    delete game;
    delete parser;
    delete client;
    delete server;
}

/*----------------------------------------------------*/
/*COMMUNICATION AVEC AFFICHAGE*/
/*----------------------------------------------------*/

void GameContext::connectToServer(QString ip)
{
    client = new Client(port, ip);
    connect(client,SIGNAL(connected()),this,SLOT(onClientConnect()));
    connect(client,SIGNAL(errorOccured(QAbstractSocket::SocketError)),this,SLOT(onErrorOccured(QAbstractSocket::SocketError)));
}

void GameContext::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    emit errorOccured(socketError);
}

void GameContext::onClientConnect()
{
    if(server !=0)
    {
        if(server->isConnexionOk())
            emit connexionOk();;
    }
    else
    {
        emit connexionOk();
    }
}

/*----------------------------------------------------*/
/*COMMUNICATION AVEC LE PARSER*/
/*----------------------------------------------------*/

void GameContext::onReciveGameInfo(int gamerId)
{

}

void GameContext::onParserUpdate()
{

}

void GameContext::onTransitToGame()
{

}

void GameContext::onMapCreated()
{

}


