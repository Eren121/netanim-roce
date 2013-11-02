#ifndef ANIMNODE_H
#define ANIMNODE_H

#include <QGraphicsTextItem>
#include "common.h"
#include "resizeableitem.h"

#include <map>



class AnimNode: public ResizeableItem
{
public:
    AnimNode(uint32_t nodeId, qreal x, qreal y);
    ~AnimNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setNodeDescription(QString description);
    QPointF getCenter();
    qreal getX();
    qreal getY();
private:
    QGraphicsTextItem * m_nodeDescription;
    uint32_t m_nodeId;
    qreal m_x;
    qreal m_y;

};


class AnimNodeMgr
{
public:
    typedef std::map <uint32_t, AnimNode *> NodeIdAnimNodeMap_t;
    static AnimNodeMgr * getInstance();
    AnimNode * getNode(uint32_t nodeId);
    AnimNode * add(uint32_t nodeId, qreal x, qreal y);
    uint32_t getCount();
private:
    AnimNodeMgr();
    NodeIdAnimNodeMap_t m_nodes;

};

#endif // ANIMNODE_H
