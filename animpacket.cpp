#include <iostream>
#include <math.h>
#include <QPointF>
#include <QPainter>
#include <QPainterPath>
#include "animpacket.h"
#include "animnode.h"
#include "log.h"
#include "logqt.h"


#define PI 3.14159265
NS_LOG_COMPONENT_DEFINE("AnimPacket");

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
  m_fromPos = AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getCenter ();
  NS_LOG_DEBUG ("From Pos:" << m_fromPos);
  m_toPos = AnimNodeMgr::getInstance ()->getNode (toNodeId)->getCenter ();
  m_line = QLineF (m_fromPos, m_toPos);
  qreal propDelay = m_firstBitRx - m_firstBitTx;
  m_velocity = m_line.length()/propDelay;
  NS_LOG_DEBUG ("Angle:" << m_line.angle());
  m_cos = cos ((360 - m_line.angle ()) * PI/180);
  m_sin = sin ((360 - m_line.angle ()) * PI/180);
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
    m_distanceTraveled = distanceTravelled;
    qreal x = m_distanceTraveled * m_cos;
    qreal y = m_distanceTraveled * m_sin;
    NS_LOG_DEBUG ("Distance moved:" << x << "," << y);
    m_head = QPointF (m_fromPos.x () + x,  m_fromPos.y () + y);
    //NS_LOG_DEBUG ("Length:" << l.length() << " PropDelay" << propDelay << " velocity:" << velocity << " timeElapsed:" << timeElapsed << " distance:" << distanceTravelled);
    //NS_LOG_DEBUG ("x:" << x << " y:" <<y);
    //addEllipse(fromPos.x() + x, fromPos.y() + y, 5, 5);
}

QRectF
AnimPacket::boundingRect() const
{
  return m_boundingRect;
}


void
AnimPacket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPainterPath path;
  painter->save();
  path.lineTo(-10 * sin (PI/4), -10 * sin (PI/4));
  path.moveTo(0, 0);
  path.lineTo(-10 * sin (PI/4), 10 * sin (PI/4));
  path.moveTo(0, 0);
  path.lineTo(-15, 0);
  painter->restore();
  NS_LOG_DEBUG("d:" << -10 * sin (45 * PI/180));
  m_boundingRect = path.boundingRect();
  painter->save();
  painter->rotate(360 - m_line.angle());
  painter->drawPath(path);
  painter->restore();
  painter->save();
  qreal textAngle = m_line.angle();

  //NS_LOG_DEBUG("Text Angle:" << textAngle);
  if(textAngle < 90)
      painter->rotate(360-textAngle);
  else if (textAngle > 270)
      painter->rotate(360-textAngle);
  else
    painter->rotate(180-textAngle);

  painter->drawText(0, 0, QString::number(m_line.angle()));
  painter->restore();
}


QPointF
AnimPacket::getHead()
{
    return m_head;
}
