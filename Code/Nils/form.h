#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <GameConnexion/client.h>
#include <GameConnexion/server.h>

class QTcpSocket;

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(bool host, QWidget *parent = 0);

public slots:
    void buttonClick();
    void messageReciveFromClient(QTcpSocket *t, QString msg);
    void messageReciveFromServeur(QString);
private:
    QLabel *l;
    Server *s;
    Client *c;
    QPushButton *b;
    bool host;
    QTcpSocket *t;
};

#endif // FORM_H
