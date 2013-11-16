#ifndef ANIMPACKET_H
#define ANIMPACKET_H
#include "qglobal.h"
#include <QGraphicsItem>
#include "animatorconstants.h"
#include "common.h"
#include "timevalue.h"

namespace netanim {

class AnimPacket : public QGraphicsItem
{
public:
  AnimPacket(uint32_t fromNodeId,
             uint32_t toNodeId,
             qreal firstBitTx,
             qreal lastBitTx,
             qreal firstBitRx,
             qreal lastBitRx);
  enum { Type = ANIMPACKET_TYPE };
  int type () const
  {
      return Type;
  }
  qreal getFirstBitTx ();
  qreal getFirstBitRx ();
  qreal getLastBitTx ();
  qreal getLastBitRx ();
  uint32_t getFromNodeId ();
  uint32_t getToNodeId ();
  void update (qreal t);
  virtual QRectF boundingRect () const;
  void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
  QPointF getHead ();

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

class AnimPacketMgr
{
public:
    static AnimPacketMgr * getInstance();
    void add(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx);
    TimeValue<AnimPacket *> * getPackets();
private:
    AnimPacketMgr();
    TimeValue<AnimPacket *> m_packets;


};

}
#endif // ANIMPACKET_H
