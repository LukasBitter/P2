#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
QPushButton *bouton;
    enum state
          {
             un,
             deux,
             trois,
          };
};

#endif // WIDGET_H
