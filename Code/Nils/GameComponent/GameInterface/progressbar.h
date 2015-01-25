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
    ProgressBar(QGraphicsItem* parent, const QPointF& center, qreal width, qreal height);

};

#endif // PROGRESSBAR_H
