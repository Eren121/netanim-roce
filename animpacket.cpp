#include <iostream>
#include <math.h>
#include <QPointF>
#include <QPainter>
#include <QPainterPath>
#include <QStaticText>
#include <QTextItem>
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
                        qreal firstBitRx,
                        bool isWPacket):
    AnimEvent(PACKET_EVENT),
    m_fromNodeId (fromNodeId),
    m_toNodeId (toNodeId),
    m_firstBitTx (firstBitTx),
    m_firstBitRx (firstBitRx),
    m_isWPacket (isWPacket)
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
  setZValue(ANIMPACKET_ZVAVLUE);
  m_infoText = new QGraphicsSimpleTextItem (this);
  m_infoText->setText("hola");
  m_infoText->setFlag(QGraphicsItem::ItemIgnoresTransformations);

  qreal textAngle = m_line.angle ();
  if(textAngle < 90)
  {
      textAngle = 360-textAngle;
  }
  else if (textAngle > 270)
  {
      textAngle = 360-textAngle;
  }
  else
  {
    textAngle = 180-textAngle;
  }
  m_infoText->rotate(textAngle);

}

AnimPacket::~AnimPacket()
{
    if(m_infoText)
    {
        delete m_infoText;
    }
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


bool
AnimPacket::getIsWPacket()
{
    return m_isWPacket;
}

QGraphicsSimpleTextItem *
AnimPacket::getInfoTextItem()
{
    return m_infoText;
}

#if 0
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

#else
void
AnimPacket::update (qreal t)
{
  qreal midPointX = (m_toPos.x() + m_fromPos.x())/2;
  qreal midPointY = (m_toPos.y() + m_fromPos.y())/2;
  m_head = QPointF (midPointX, midPointY);
  //m_head = QPointF (100,100);
  //NS_LOG_DEBUG ("m_head:" << m_head);
}

#endif
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
    //NS_LOG_DEBUG ("Packet Transform:" << transform());
    //NS_LOG_DEBUG ("Device Transform:" << painter->deviceTransform());
    //NS_LOG_DEBUG ("Scene Transform:" << sceneTransform());
    QPen p;
    QTransform viewTransform = AnimatorView::getInstance()->getTransform();

    painter->save();
    QPainterPath arrowTailPath;
    arrowTailPath.moveTo(0, 0);
    arrowTailPath.lineTo (-5 * (10/viewTransform.m22()) , 0);
    p.setColor(Qt::red);
    painter->setPen(p);
    //p.setWidthF(1.0);
    painter->setPen(p);
    painter->rotate (360 - m_line.angle ());
    painter->drawPath(arrowTailPath);
    painter->restore();


    QPolygonF arrowHeadPolygon;

  QPainterPath arrowHeadPath;
  qreal arrowHeadLength = 2 * (10/viewTransform.m22());
  arrowHeadPolygon << QPointF (0, 0) << QPointF (-arrowHeadLength * cos (PI/10), -arrowHeadLength * sin (PI/10)) << QPointF (-arrowHeadLength * cos (PI/10), arrowHeadLength * sin (PI/10));

  arrowHeadPath.lineTo (-arrowHeadLength * cos (PI/10), -arrowHeadLength * sin (PI/10));
  arrowHeadPath.moveTo (0, 0);
  arrowHeadPath.lineTo (-arrowHeadLength * cos (PI/10), arrowHeadLength * sin (PI/10));
  arrowHeadPath.moveTo (0, 0);

  arrowHeadPath.moveTo (0, 0);
  painter->save();
  QPen arrowHeadPen;
  QColor black (0, 0, 5, 130);
  arrowHeadPen.setColor(black);
  //p.setWidthF(1.1);


  painter->setPen(arrowHeadPen);
  painter->rotate (360 - m_line.angle ());
  QBrush brush;
  brush.setColor(black);
  brush.setStyle(Qt::SolidPattern);
  painter->setBrush(brush);
  painter->drawPolygon(arrowHeadPolygon);
  //painter->drawPath(arrowHeadPath);
  painter->restore();




  QPainterPath path;
  path.moveTo(0, 0);
  path.addPath(arrowHeadPath);
  path.moveTo(0, 0);
  path.addPath(arrowTailPath);


  m_boundingRect = path.boundingRect ();
  QTransform t;
  t.rotate(360 - m_line.angle ());
  m_boundingRect = t.mapRect(m_boundingRect);





  painter->save();
  QTransform textTransform;
  qreal textAngle = m_line.angle ();
  if(textAngle < 90)
  {
      textAngle = 360-textAngle;
  }
  else if (textAngle > 270)
  {
      textAngle = 360-textAngle;
  }
  else
  {
    textAngle = 180-textAngle;
  }
  painter->rotate(textAngle);
  textTransform.rotate(textAngle);
  QPainterPath textPath;
  QFont f ;//("Helvetica");//= painter->font();
  f.setKerning(false);
  f.setStyleHint(QFont::Times);
  //f.setPointSizeF(8/viewTransform.m22());
  //f.setPixelSize(5);
  f.setPointSizeF(15/viewTransform.m22());
  f.setFixedPitch(true);

  QPen p1 = painter->pen();
  p1.setColor(Qt::red);
  p1.setStyle(Qt::SolidLine);
  QBrush brush2 = painter->brush();
  brush2.setStyle(Qt::SolidPattern);
  brush2.setColor(Qt::black);
  p1.setWidthF(1/viewTransform.m22());
  p1.setBrush(brush2);
  //p1.setCosmetic(true);
  painter->setBrush(brush2);
  painter->setPen(p1);
  textPath.addText(0, -2/viewTransform.m22(), f, "Jo");


  painter->setTransform(m_infoText->transform());
  //QLineF l (m_fromPos, m_toPos);
  //painter->drawEllipse(m_fromPos, l.length(), l.length());
  //painter->drawText(0, 0, "Jo");


  QRectF textBoundingRect = textTransform.mapRect(textPath.boundingRect());

  painter->restore ();
  m_boundingRect = QRectF(QPointF(qMin (m_boundingRect.left(), textBoundingRect.left()),
                          qMin (m_boundingRect.top(), textBoundingRect.top())),
                          QPointF(qMax (m_boundingRect.right(), textBoundingRect.right()),
                          qMax (m_boundingRect.bottom(), textBoundingRect.bottom())));


  //NS_LOG_DEBUG ("m_boundingRect:" << m_boundingRect);


}


QPointF
AnimPacket::getHead ()
{
  return m_head;
}

QPointF
AnimPacket::getFromPos()
{
    return m_fromPos;
}

QPointF
AnimPacket::getToPos()
{
    return m_toPos;
}

AnimPacketMgr::AnimPacketMgr()
{
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

AnimPacket *
AnimPacketMgr::add(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx, bool isWPacket)
{

    /*if (fromId != 0)
        return;
    if (toId != 3)
        return;
    if (m_packets.getCount())
        return;*/
    AnimPacket * pkt = new AnimPacket(fromId, toId, fbTx, fbRx, isWPacket);
    //NS_LOG_DEBUG ("FbTx:" << fbTx);
    //m_packets.add(fbTx, pkt);
    return pkt;
}



}

