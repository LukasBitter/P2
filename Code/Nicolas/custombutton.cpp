#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent)
    : QPushButton(parent)
{

}

CustomButton::~CustomButton()
{

}
//Paint event of button
void CustomButton::paintEvent(QPaintEvent *paint)
{
    QPushButton::paintEvent(paint);
    QPainter p(this);
    p.save();

    p.drawText(QPoint(100,100),FirstName); //Simple Text.
    p.setPen(Qt::blue);                       //changing the color of pen.
    p.setFont(QFont("Arial", 30));     //Changing the font.
    p.drawText(QPoint(100,200),MiddleName);
    p.drawText(QPoint(100,300),Lastname);
    p.drawImage(QPoint(300,300),SimileIcon);
    p.restore();
}
