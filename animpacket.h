#ifndef ANIMPACKET_H
#define ANIMPACKET_H
#include "qglobal.h"
#include <QGraphicsItem>
#include "animatorconstants.h"
#include "common.h"
#include "timevalue.h"
#include "animevent.h"
namespace netanim {

class AnimPacket : public QObject, public QGraphicsItem, public AnimEvent
{
Q_OBJECT

    Q_PROPERTY (QPointF pos READ pos WRITE setPos)
public:
  AnimPacket(uint32_t fromNodeId,
             uint32_t toNodeId,
             qreal firstBitTx,
             qreal firstBitRx,
             bool isWPacket);
  enum { Type = ANIMPACKET_TYPE };
  int type () const
  {
      return Type;
  }
  qreal getFirstBitTx ();
  qreal getFirstBitRx ();
  uint32_t getFromNodeId ();
  uint32_t getToNodeId ();
  QPointF getFromPos ();
  QPointF getToPos ();
  void update (qreal t);
  virtual QRectF boundingRect () const;
  void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
  QPointF getHead ();
  QGraphicsTextItem * m_testTextItem;


private:
  uint32_t m_fromNodeId;
  uint32_t m_toNodeId;
  qreal m_firstBitTx;
  qreal m_firstBitRx;
  qreal m_velocity;
  qreal m_isWPacket;
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
    AnimPacket * add(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx, bool isWPacket);
private:
    AnimPacketMgr();


};

}
#endif // ANIMPACKET_H
