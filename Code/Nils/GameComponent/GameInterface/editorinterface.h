#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H

#include "global.h"
#include "enumlibrary.h"

class Node;
class Button;

namespace GameInterface
{
class EditorInterface;
}

class EditorInterface : public QGraphicsWidget
{
public:
    explicit EditorInterface(QGraphicsItem * parent = 0);

    /*SURCHARGE*/
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void btCreateNodePressed();
    void btRemoveNodePressed();
    void btConnectNodePressed();
    void btDisconnectNodePressed();
private slots:
    void onBtCreateNodePressed();
    void onBtRemoveNodePressed();
    void onBtConnectNodePressed();
    void onBtDisconnectNodePressed();

private:
    /*INTERFACE*/
    Button *btCreateNode;
    Button *btRemoveNode;
    Button *btConnectNode;
    Button *btDisconnectNode;

    /*METHODE PRIVE*/
    void setUpUI();
};

#endif // EDITORINTERFACE_H
