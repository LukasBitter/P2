#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
}

Player::Player(int num, int pts)
{
    this->playerId = 0;
    this->playerStatus = empty;
    this->playerNumber = num;
    this->playerPts = pts;
    this->count = 0;
}

int Player::getPoints()
{
   return playerPts;
}

QString Player::addCount()
{
    return QString::number(this->count++);
}

QString Player::getPlayerName()
{
    return this->playerName;
}

void Player::setPlayerName(QString name)
{
    this->playerName = name;
}

void Player::addPoint()
{
    this->playerPts++;
}

void Player::removePoint()
{
    this->playerPts--;
}


