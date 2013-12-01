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
    void setX(qreal x);
    void setY(qreal y);
    uint32_t getNodeId();
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void addIpv4Address(QString ip);
    void addMacAddress(QString mac);
    bool hasIpv4(QString ip);
    bool hasMac(QString mac);
    void showNodeId(bool show);
private:
    typedef QVector <QString> Ipv4Vector_t;
    typedef QVector <QString> MacVector_t;
    QGraphicsTextItem * m_nodeDescription;
    uint32_t m_nodeId;
    qreal m_x;
    qreal m_y;
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    bool m_showNodeId;
    Ipv4Vector_t m_ipv4Vector;
    MacVector_t m_macVector;


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
    void systemReset();
    void addIpv4Address(uint32_t nodeId, QString ip);
    void addMacAddress(uint32_t nodeId, QString mac);
    void setSize(qreal width, qreal height);
    void showNodeId(bool show);
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
