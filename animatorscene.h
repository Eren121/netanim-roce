/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: John Abraham <john.abraham.in@gmail.com>
 */

#ifndef ANIMATORSCENE_H
#define ANIMATORSCENE_H

#include "common.h"
#include "animnode.h"
#include "animlink.h"
#include "resizeableitem.h"
#include "timevalue.h"
#include "animpacket.h"



namespace netanim
{


class AnimInterfaceText : public QGraphicsTextItem
{
public:
  typedef enum textMode
  {
    NONE,
    IPV4,
    MAC,
    BOTH
  } TextMode_t;

  AnimInterfaceText (QString description, bool leftAligned=false);
  ~AnimInterfaceText ();
  enum { Type = ANIMINTERFACE_TEXT_TYPE };
  int type () const
  {
    return Type;
  }
  QPainterPath shape () const;
  bool setLine (QLineF l);
  QGraphicsLineItem * getLine ();
  void setMode (bool showIpv4, bool showMac);
  QString getText () const;
  void setLeftAligned (bool leftAligned);

private:
  bool m_leftAligned;
  QGraphicsLineItem * m_line;
  TextMode_t m_mode;

protected:
  void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};



class AnimatorScene : public QGraphicsScene
{
  Q_OBJECT
public:
  static AnimatorScene * getInstance ();
  AnimatorScene ();
  void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
  void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
  void addPacket (AnimPacket * p);
  void addNode (AnimNode * animNode);
  void addLink (AnimLink * animLink);
  void addWirelessCircle (AnimWirelessCircles * w);
  void purgeAnimatedPackets ();
  void showAnimatedPackets (bool show);
  void purgeAnimatedNodes ();
  void purgeAnimatedLinks ();
  void purgeNodeTrajectories ();
  void setShowInterfaceTexts (bool showIp, bool showMac);
  void addGrid ();
  void resetGrid ();
  void systemReset ();
  QRectF getBoundaryRect ();
  void setGridLinesCount (int nGridLines);
  void setShowNodeTrajectory (AnimNode * animNode);

public slots:
  void testSlot ();
private:
  typedef QVector <AnimInterfaceText *>          AnimInterfaceTextVector_t;
  typedef QVector <QGraphicsLineItem *>          LineItemVector_t;
  typedef QVector <QGraphicsSimpleTextItem*>     GridCoordinatesVector_t;
  typedef std::map <uint32_t, QGraphicsPathItem *>          NodeTrajectoryMap_t;

  TimeValue<AnimPacket *> m_testTimeValue;
  QLabel * m_mousePositionLabel;
  QGraphicsProxyWidget * m_mousePositionProxyWidget;
  QVector <AnimPacket *> m_animatedPackets;
  QVector <AnimWirelessCircles *> m_animatedWirelessCircles;
  QVector <AnimLink *> m_animatedLinks;
  QVector<AnimNode *> m_animatedNodes;
  bool            m_showIpInterfaceTexts;
  bool            m_showMacInterfaceTexts;
  AnimInterfaceTextVector_t    m_interfaceATexts;
  AnimInterfaceTextVector_t    m_interfaceBTexts;
  qreal m_leftTop;
  qreal m_rightTop;
  QList <QGraphicsItem *> getInterfaceTextCollisionList (AnimInterfaceText * text);
  qreal           m_gridStep;
  bool            m_showGrid;
  int             m_nGridLines;
  LineItemVector_t             m_gridLines;
  GridCoordinatesVector_t      m_gridCoordinates;
  QRectF m_boundaryRect;
  NodeTrajectoryMap_t m_nodeTrajectory;


  void repositionInterfaceText (AnimInterfaceText * textItem);
  void resetInterfaceTexts ();
  void removeInterfaceTextCollision ();
  void resetInterfaceTextTop ();

  void markGridCoordinates ();
  void initGridCoordinates ();
  QVector <QGraphicsSimpleTextItem *> getGridCoordinatesItems ();
  void setMousePositionLabel (QPointF pos);
  void showMousePositionLabel (bool show);

};

} // namespace netanim

#endif // ANIMATORSCENE_H
