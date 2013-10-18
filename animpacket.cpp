#include <iostream>
#include <QPointF>
#include "animpacket.h"
#include "animnode.h"
#define PI 3.14159265

AnimPacket::AnimPacket(uint32_t fromNodeId,
                       uint32_t toNodeId,
                       qreal firstBitTx,
                       qreal lastBitTx,
                       qreal firstBitRx,
                       qreal lastBitRx):
    m_fromNodeId(fromNodeId),
    m_toNodeId(toNodeId),
    m_firstBitTx(firstBitTx),
    m_lastBitTx(lastBitTx),
    m_firstBitRx(firstBitRx),
    m_lastBitRx(lastBitRx)
{
  QPointF m_fromPos = AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getCenter ();
  QPointF m_toPos = AnimNodeMgr::getInstance ()->getNode (toNodeId)->getCenter ();
  m_line = QLineF (m_fromPos, m_toPos);
  qreal propDelay = m_firstBitRx - m_firstBitTx;
  m_velocity = m_line.length()/propDelay;
  m_cos = cos (m_line.angle () * PI/180);
  m_sin = sin (m_line.angle () * PI/180);
}

uint32_t
AnimPacket::getFromNodeId()
{
    return m_fromNodeId;
}

uint32_t
AnimPacket::getToNodeId()
{
    return m_toNodeId;
}

qreal
AnimPacket::getFirstBitTx()
{
    return m_firstBitTx;
}

qreal
AnimPacket::getFirstBitRx()
{
    return m_firstBitRx;
}

qreal
AnimPacket::getLastBitRx()
{
    return m_lastBitRx;
}

qreal
AnimPacket::getLastBitTx()
{
    return m_lastBitTx;
}

void
AnimPacket::update (qreal t)
{
    std::cout << "T=" << t << this;
    qreal timeElapsed = t - getFirstBitTx();
    qreal distanceTravelled = m_velocity * timeElapsed;
    qreal x = distanceTravelled * m_cos;
    qreal y = distanceTravelled * m_sin;

    //NS_LOG_DEBUG ("Length:" << l.length() << " PropDelay" << propDelay << " velocity:" << velocity << " timeElapsed:" << timeElapsed << " distance:" << distanceTravelled);
    //NS_LOG_DEBUG ("x:" << x << " y:" <<y);
    //addEllipse(fromPos.x() + x, fromPos.y() + y, 5, 5);
}

QRectF
AnimPacket::boundingRect() const
{
  QRectF r;
  return r;
}

void
AnimPacket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
