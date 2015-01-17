#include "form.h"
#include <QGridLayout>

Form::Form(bool host, QWidget *parent) :
    QWidget(parent)
{
    b = new QPushButton("send");
    connect(b, SIGNAL(clicked()), this, SLOT(buttonClick()));

    this->host=host;
    if(host)
    {
        l = new QLabel("HOST", this);
        s = new Server(8000, 2,this);
        connect(s, SIGNAL(messageReciveFromClient(QTcpSocket*,QString)),this,SLOT(messageReciveFromClient(QTcpSocket*,QString)));
    }
    else
    {
        l = new QLabel("CLIENT", this);
        c = new Client("127.0.0.1", this, 8000);
        connect(c,SIGNAL(messageReciveFromServeur(QString)), this,SLOT(messageReciveFromServeur(QString)));
    }

    QGridLayout *g = new QGridLayout(this);
    g->addWidget(l,0,0);
    g->addWidget(b,1,0);

    this->setLayout(g);

}

void Form::buttonClick()
{
    if(host)
    {
        s->sendMessageToClient(t, "ENVOI au client");
    }
    else
    {
        c->sendMessageToServer("ENVOI au server");
    }
}

void Form::messageReciveFromClient(QTcpSocket *t, QString msg)
{
    this->t = t;
    l->setText(msg);
}

void Form::messageReciveFromServeur(QString msg)
{
    l->setText(msg);
}
