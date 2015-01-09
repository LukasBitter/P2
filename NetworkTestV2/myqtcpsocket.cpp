#include "myqtcpsocket.h"

MyQTCPSocket::MyQTCPSocket(int id, QObject *parent)
{
    this->id = id;
}

void MyQTCPSocket::messageRecu(int id)
{
    this->id = id;
}

void MyQTCPSocket::myReadyRead()
{
    emit messageRecu(this->id);
}
