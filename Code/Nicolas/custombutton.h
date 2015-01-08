#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>

class CustomButton : public QPushButton
    {
    Q_OBJECT

public:
    CustomButton(QWidget *parent = 0);
    ~CustomButton();

public:
    QString FirstName,MiddleName,Lastname;
    QImage SimileIcon;
    bool IsBkColorEnabled;
    QColor Bkclor;

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CUSTOMBUTTON_H
