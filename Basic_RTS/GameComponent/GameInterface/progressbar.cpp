#include "progressbar.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ProgressBar::ProgressBar(const QRectF &dimension, QGraphicsItem* parent):
    QGraphicsItem(parent), fillMode(false), vertical(true), inverse(true)
{
    setX(dimension.x());
    setY(dimension.y());
    this->dimension = QRectF(0,0,dimension.width(), dimension.height());

    borderPen.setWidth(1);
    borderPen.setColor(Qt::black);
    borderPen.setJoinStyle(Qt::RoundJoin);
}

ProgressBar::ProgressBar(int x, int y, int w, int h, QGraphicsItem *parent)
{
    Q_UNUSED(parent);

    setX(x);
    setY(y);

    this->dimension = QRectF(0,0,w, h);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF ProgressBar::boundingRect() const
{
    return dimension;
}

void ProgressBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    Q_UNUSED(option);
    Q_UNUSED(w);

    int max = fillMode ? sumOfValue() : sumOfMax();
    int dimGradiant = vertical ? (int)dimension.height() : (int)dimension.width();
    int dimBase = vertical ? (int)dimension.width() : (int)dimension.height();

    double progress = 0;
    foreach (int i, lstCurrentValue.keys())
    {
        double percent = ((double)lstCurrentValue.value(i) / (double)max) * dimGradiant;

        if(percent >= 0)
        {
            QBrush b = painter->brush();
            b.setColor(lstColor.value(i));
            b.setStyle(Qt::SolidPattern);
            painter->setBrush(b);

            if(inverse)
            {
                if(vertical)
                {
                    painter->drawRect(0, progress, dimBase, percent);
                }
                else
                    painter->drawRect(progress, 0, percent, dimBase);
            }
            else
            {
                if(vertical)
                    painter->drawRect(0, dimension.height()-progress, dimBase, -(percent));
                else
                    painter->drawRect(dimension.width()-progress, 0, -(percent), dimBase);
            }
            progress += percent;
        }
    }

    QBrush b = painter->brush();
    b.setStyle(Qt::NoBrush);
    painter->setBrush(b);
    painter->setPen(borderPen);
    painter->drawRect(boundingRect());
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

int ProgressBar::getMax(int partNumber)
{
    return lstValueMax.value(partNumber, 0);
}

int ProgressBar::getValue(int partNumber)
{
    return lstCurrentValue.value(partNumber, 0);
}

bool ProgressBar::getFillMode() const
{
    return fillMode;
}

bool ProgressBar::getVertical() const
{
    return vertical;
}

bool ProgressBar::getInverse() const
{
    return inverse;
}

QColor ProgressBar::getColor(int partNumber) const
{
    return lstColor.value(partNumber, Qt::white);
}

QPen &ProgressBar::getBorderPen()
{
    return borderPen;
}

void ProgressBar::setMax(int partNumber, int value)
{
    if(!lstValueMax.contains(partNumber)) return;

    lstValueMax.insert(partNumber, value);
}

void ProgressBar::setValue(int partNumber, int value)
{
    if(!lstCurrentValue.contains(partNumber)) return;

    lstCurrentValue.insert(partNumber, value);
}

void ProgressBar::setColor(int partNumber, QColor value)
{
    if(!lstColor.contains(partNumber)) return;

    lstColor.insert(partNumber, value);
}

void ProgressBar::setFillMode(bool b)
{
    fillMode = b;
}

void ProgressBar::setVertical(bool b)
{
    vertical = b;
}

void ProgressBar::setInverse(bool b)
{
    inverse = b;
}

void ProgressBar::insertPlage(int partNumber, int value, int max, QColor color)
{
    lstValueMax.insert(partNumber, max);
    lstCurrentValue.insert(partNumber, value);
    lstColor.insert(partNumber, color);
}

void ProgressBar::removePlage(int partNumber)
{
    lstValueMax.remove(partNumber);
    lstCurrentValue.remove(partNumber);
    lstColor.remove(partNumber);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

int ProgressBar::sumOfMax() const
{
    int sum = 0;
    foreach (int i, lstValueMax)
    {
        sum += i;
    }
    return sum;
}

int ProgressBar::sumOfValue() const
{
    int sum = 0;
    foreach (int i, lstCurrentValue)
    {
        sum += i;
    }
    return sum;
}
