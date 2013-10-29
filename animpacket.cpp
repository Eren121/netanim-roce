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

AnimPacket::AnimPacket (uint32_t fromNodeId,
                        uint32_t toNodeId,
                        qreal firstBitTx,
                        qreal lastBitTx,
                        qreal firstBitRx,
                        qreal lastBitRx):
    m_fromNodeId (fromNodeId),
    m_toNodeId (toNodeId),
    m_firstBitTx (firstBitTx),
    m_lastBitTx (lastBitTx),
    m_firstBitRx (firstBitRx),
    m_lastBitRx (lastBitRx)
{
  m_fromPos = AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getCenter ();
  m_toPos = AnimNodeMgr::getInstance ()->getNode (toNodeId)->getCenter ();
  m_line = QLineF (m_fromPos, m_toPos);
  qreal propDelay = m_firstBitRx - m_firstBitTx;
  m_velocity = m_line.length ()/propDelay;
  m_cos = cos ((360 - m_line.angle ()) * PI/180);
  m_sin = sin ((360 - m_line.angle ()) * PI/180);
}

uint32_t
AnimPacket::getFromNodeId ()
{
  return m_fromNodeId;
}

uint32_t
AnimPacket::getToNodeId ()
{
  return m_toNodeId;
}

qreal
AnimPacket::getFirstBitTx ()
{
  return m_firstBitTx;
}

qreal
AnimPacket::getFirstBitRx ()
{
  return m_firstBitRx;
}

qreal
AnimPacket::getLastBitRx ()
{
  return m_lastBitRx;
}

qreal
AnimPacket::getLastBitTx ()
{
  return m_lastBitTx;
}

void
AnimPacket::update (qreal t)
{
  qreal timeElapsed = t - getFirstBitTx ();
  qreal distanceTravelled = m_velocity * timeElapsed;
  m_distanceTraveled = distanceTravelled;
  qreal x = m_distanceTraveled * m_cos;
  qreal y = m_distanceTraveled * m_sin;
  m_head = QPointF (m_fromPos.x () + x,  m_fromPos.y () + y);
}

QRectF
AnimPacket::boundingRect () const
{
  return m_boundingRect;
}


void
AnimPacket::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPainterPath path;
  painter->save ();
  path.lineTo (-10 * sin (PI/4), -10 * sin (PI/4));
  path.moveTo (0, 0);
  path.lineTo (-10 * sin (PI/4), 10 * sin (PI/4));
  path.moveTo (0, 0);
  path.lineTo (-15, 0);
  painter->restore ();
  m_boundingRect = path.boundingRect ();
  painter->save ();
  painter->rotate (360 - m_line.angle ());
  painter->drawPath (path);
  painter->restore ();
  painter->save ();
  qreal textAngle = m_line.angle ();
  if(textAngle < 90)
      painter->rotate (360-textAngle);
  else if (textAngle > 270)
      painter->rotate (360-textAngle);
  else
    painter->rotate (180-textAngle);

  painter->drawText (0, 0, QString::number (m_line.angle ()));
  painter->restore ();
}


QPointF
AnimPacket::getHead ()
{
  return m_head;
}
