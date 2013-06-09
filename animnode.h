#ifndef ANIMNODE_H
#define ANIMNODE_H

#include <QGraphicsTextItem>
#include "resizeableitem.h"

class AnimNode: public ResizeableItem
{
public:
    AnimNode();
    ~AnimNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setNodeDescription(QString description);
private:
    QGraphicsTextItem * m_nodeDescription;

};

#endif // ANIMNODE_H
