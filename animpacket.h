#ifndef ANIMPACKET_H
#define ANIMPACKET_H
#include "common.h"
#include "qglobal.h"
#include <QGraphicsItem>

class AnimPacket : public QGraphicsItem
{
public:
    AnimPacket(uint32_t fromNodeId,
               uint32_t toNodeId,
               qreal firstBitTx,
               qreal lastBitTx,
               qreal firstBitRx,
               qreal lastBitRx);
    qreal getFirstBitTx();
    qreal getFirstBitRx();
    qreal getLastBitTx();
    qreal getLastBitRx();
    uint32_t getFromNodeId();
    uint32_t getToNodeId();
    void update (qreal t);
    virtual QRectF boundingRect () const;
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QPointF getHead();

private:
    uint32_t m_fromNodeId;
    uint32_t m_toNodeId;
    qreal m_firstBitTx;
    qreal m_lastBitTx;
    qreal m_firstBitRx;
    qreal m_lastBitRx;
    qreal m_velocity;
    qreal m_distanceTraveled;
    QLineF m_line;
    qreal m_cos;
    qreal m_sin;
    QPointF m_fromPos;
    QPointF m_toPos;
    QPointF m_head;
    QRectF m_boundingRect;
};

#endif // ANIMPACKET_H
