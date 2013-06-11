#ifndef ANIMNODE_H
#define ANIMNODE_H

#include <QGraphicsTextItem>
#include "resizeableitem.h"



class AnimNode: public ResizeableItem
{
public:
    AnimNode(uint32_t nodeId);
    ~AnimNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setNodeDescription(QString description);
private:
    QGraphicsTextItem * m_nodeDescription;
    uint32_t m_nodeId;

};


class AnimNodeMgr
{
public:
    static AnimNodeMgr * getInstance();
    AnimNode * getNode(uint32_t nodeId);
private:
    AnimNodeMgr();

};

#endif // ANIMNODE_H
