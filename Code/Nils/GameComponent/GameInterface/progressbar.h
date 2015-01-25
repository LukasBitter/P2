#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QGraphicsItem>

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
