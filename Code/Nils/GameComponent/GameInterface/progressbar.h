#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "global.h"

namespace GameInterface
{
    class ProgressBar;
}

class ProgressBar : public QGraphicsItem
{
public:
    ProgressBar(const QRectF &dimension, QGraphicsItem* parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    /*ASSESSEUR / MUTATEUR*/
    void insertPlage(int partNumber, int value, int max, QColor color);
    void removePlage(int partNumber);

    int getMax(int partNumber);
    int getValue(int partNumber);
    bool getFillMode()const;
    bool getVertical()const;
    bool getInverse()const;
    QColor getColor(int partNumber)const;
    QPen &getBorderPen();

    void setMax(int partNumber, int value);
    void setValue(int partNumber, int value);
    void setColor(int partNumber, QColor value);
    void setFillMode(bool b);
    void setVertical(bool b);
    void setInverse(bool b);
private:
    /*OUTIL*/
    QHash<int, int> lstValueMax; ///< Liste des valeur maximale de chaque plage
    QHash<int, int> lstCurrentValue; ///< Liste des valeurs actuelle de chaque plage
    QHash<int, QColor> lstColor; ///< Liste des couleur de chaque plage
    QRectF dimension; ///< Dimension de la progressbar
    bool fillMode;
    bool vertical;
    bool inverse;
    QPen borderPen;

    /*METHODE PRIVE*/
    int sumOfMax() const;
    int sumOfValue() const;
};

#endif // PROGRESSBAR_H
