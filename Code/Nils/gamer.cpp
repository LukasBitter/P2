#include "gamer.h"

Gamer::Gamer(QColor color, QObject *parent)
    : Updatable(parent), color(color)
{

}

Gamer::~Gamer()
{

}

void Gamer::tic()
{

}

QColor Gamer::getColor() const
{
    return color;
}
