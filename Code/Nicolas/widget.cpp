#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    bouton = new QPushButton(tr("C&alculer"), this);
    bouton->resize(250, 30);
    bouton->move(20,20);
}

Widget::~Widget()
{

}
