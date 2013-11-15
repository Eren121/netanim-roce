#include <iostream>
#include <math.h>
#include <QPointF>
#include <QPainter>
#include <QPainterPath>
#include "animpacket.h"
#include "animnode.h"
#include "animatorview.h"
#include "log.h"
#include "logqt.h"


#define PI 3.14159265
NS_LOG_COMPONENT_DEFINE("AnimPacket");

namespace netanim {
AnimPacketMgr * pAnimPacketMgr = 0;

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
  //m_fromPos = QPointF(AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getX(), AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getY());
  //m_toPos = QPointF(AnimNodeMgr::getInstance ()->getNode (toNodeId)->getX(), AnimNodeMgr::getInstance ()->getNode (toNodeId)->getY());

  m_toPos = AnimNodeMgr::getInstance ()->getNode (toNodeId)->getCenter ();
  //NS_LOG_DEBUG ("FromPos:" << m_fromPos);
  //NS_LOG_DEBUG ("ToPos:" << m_toPos);
  m_line = QLineF (m_fromPos, m_toPos);
  qreal propDelay = m_firstBitRx - m_firstBitTx;
  m_velocity = m_line.length ()/propDelay;
  m_cos = cos ((360 - m_line.angle ()) * PI/180);
  m_sin = sin ((360 - m_line.angle ()) * PI/180);
  setVisible(false);
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
  //NS_LOG_DEBUG ("Upd Time:" << t << " Head:" << m_head << " Distance traveled:" << m_distanceTraveled << " time elapsed:" << timeElapsed  << " velocity:" << m_velocity);
}

QRectF
AnimPacket::boundingRect () const
{
  return m_boundingRect;
  //QRectF r = QRectF(-m_boundingRect.width(),  -m_boundingRect.height(), m_boundingRect.width(), m_boundingRect.height());
  //return r;
}


void
AnimPacket::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPainterPath path;
  painter->save ();
  path.lineTo (-5 * cos (PI/8), -5 * sin (PI/8));
  path.moveTo (0, 0);
  path.lineTo (-5 * cos (PI/8), 5 * sin (PI/8));
  path.moveTo (0, 0);
  QTransform viewTransform = AnimatorView::getInstance()->getTransform();

  QFont f = painter->font();
  //NS_LOG_DEBUG ("PointSize:" << f.pointSizeF());
  f.setPointSizeF(10/viewTransform.m22());
  //path.addText(-15, 0, f, "Jo");
  path.moveTo (0, 0);
  path.lineTo (-15, 0);
  painter->restore ();
  painter->save ();
  painter->rotate (360 - m_line.angle ());
  painter->drawPath (path);
  m_boundingRect = path.boundingRect ();
  QTransform t;
  t.rotate(360 - m_line.angle ());
  //t.translate(0, 0);
  m_boundingRect = t.mapRect(m_boundingRect);
  painter->restore();
  NS_LOG_DEBUG ("PacketRect:" << m_boundingRect);
  painter->save();


/*

  qreal textAngle = m_line.angle ();
  if(textAngle < 90)
      painter->rotate (360-textAngle);
  else if (textAngle > 270)
      painter->rotate (360-textAngle);
  else
    painter->rotate (180-textAngle);
  QPainterPath textPath;
  textPath.addText(0, 0, f, "Jo");
  NS_LOG_DEBUG ("TextRect:" << textPath.boundingRect());
  painter->drawPath(textPath);

  painter->restore ();*/


}


QPointF
AnimPacket::getHead ()
{
  return m_head;
}

AnimPacketMgr::AnimPacketMgr()
{
    m_packets.setLookBack(2);
}
AnimPacketMgr *
AnimPacketMgr::getInstance()
{
    if(!pAnimPacketMgr)
    {
        pAnimPacketMgr = new AnimPacketMgr;
    }
    return pAnimPacketMgr;
}

void
AnimPacketMgr::add(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx)
{
    if (fromId == toId)
        return;
    /*if (fromId != 0)
        return;
    if (toId != 3)
        return;
    if (m_packets.getCount())
        return;*/
    AnimPacket * pkt = new AnimPacket(fromId, toId, fbTx, 0, fbRx, 0);
    NS_LOG_DEBUG ("FbTx:" << fbTx);
    m_packets.add(fbTx, pkt);
}


TimeValue<AnimPacket *> *
AnimPacketMgr::getPackets()
{
    return &m_packets;
}


}

