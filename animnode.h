#ifndef ANIMNODE_H
#define ANIMNODE_H

#include <QGraphicsTextItem>
#include "resizeableitem.h"

class AnimNode: public ResizeableItem
{
public:
    AnimNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void init();
private:
    QGraphicsTextItem * m_textItem;

};

#endif // ANIMNODE_H
