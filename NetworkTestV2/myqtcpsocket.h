#ifndef MYQTCPSOCKET_H
#define MYQTCPSOCKET_H

#include <QTcpSocket>

class MyQTCPSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyQTCPSocket(int id, QObject *parent = 0);

signals:
    void messageRecu(int id);
public slots:
    void myReadyRead();
private:
    int id;

};

#endif // MYQTCPSOCKET_H
