#ifndef ANIMNODE_H
#define ANIMNODE_H

#include <QGraphicsTextItem>
#include "common.h"
#include "resizeableitem.h"

#include <map>



class AnimNode: public ResizeableItem
{
public:
    AnimNode(uint32_t nodeId, QGraphicsScene * scene);
    ~AnimNode();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setNodeDescription(QString description);
    QPointF getCenter();
private:
    QGraphicsTextItem * m_nodeDescription;
    uint32_t m_nodeId;

};


class AnimNodeMgr
{
public:
    typedef std::map <uint32_t, AnimNode *> NodeIdAnimNodeMap_t;
    static AnimNodeMgr * getInstance();
    AnimNode * getNode(uint32_t nodeId);
    AnimNode * add(uint32_t nodeId, QGraphicsScene * scene, qreal x, qreal y);
private:
    AnimNodeMgr();
    NodeIdAnimNodeMap_t m_nodes;

};

#endif // ANIMNODE_H
