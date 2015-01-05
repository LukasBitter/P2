#include "gamer.h"

Gamer::Gamer(QColor color, QObject *parent)
    : QObject(parent), color(color)
{

}

Gamer::~Gamer()
{

}

QColor Gamer::getColor() const
{
    return color;
}
