#ifndef ANIMNODE_H
#define ANIMNODE_H

#include <QGraphicsTextItem>
#include "common.h"
#include "resizeableitem.h"

#include <map>

namespace netanim {


class AnimNode: public ResizeableItem
{
public:
    AnimNode(uint32_t nodeId, qreal x, qreal y, QString nodeDescription);
    ~AnimNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setNodeDescription(QString description);
    QPointF getCenter();
    QGraphicsTextItem * getDescription();
    qreal getX();
    qreal getY();
    uint32_t getNodeId();
    void setWidth(qreal width);
    void setHeight(qreal height);
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
    AnimNode * add(uint32_t nodeId, qreal x, qreal y, QString nodeDescription);
    uint32_t getCount();
    QPointF getMinPoint ();
    QPointF getMaxPoint ();
private:
    AnimNodeMgr();
    NodeIdAnimNodeMap_t m_nodes;
    qreal m_minX;
    qreal m_minY;
    qreal m_maxX;
    qreal m_maxY;

};


}
#endif // ANIMNODE_H
