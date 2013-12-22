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
#include "packetsscene.h"
#include "logqt.h"
#include "animpacket.h"
#include "graphpacket.h"
#include "animatormode.h"

namespace netanim {
NS_LOG_COMPONENT_DEFINE ("PacketsScene");

PacketsScene * pPacketsScene = 0;
PacketsScene::PacketsScene ():
  QGraphicsScene (-100, -100, 10024, 10024),
  m_interNodeSpacing (100),
  m_maxTime (0)
{

}
PacketsScene *
PacketsScene::getInstance ()
{
  if (!pPacketsScene)
    {
      pPacketsScene = new PacketsScene;
    }
  return pPacketsScene;
}

void
PacketsScene::setUpNodeLines ()
{
  QRectF r = sceneRect ();
  qreal height = r.bottom () - r.top ();
  qreal borderHeight = 0;//0.01 * height;
  r.setWidth(100 * m_interNodeSpacing);
  setSceneRect(r);
  for (uint32_t nodeId = 0; nodeId < 100 ; ++nodeId)
    {
      QGraphicsLineItem * lineItem = addLine (m_interNodeSpacing * nodeId, borderHeight, m_interNodeSpacing * nodeId, r.bottom () - borderHeight);
      //lineItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);

      m_nodeLines[nodeId] = lineItem;
    }
  TimeValue <AnimEvent*> *events = AnimatorMode::getInstance ()->getEvents ();
  m_maxTime = AnimatorMode::getInstance ()->getLastPacketEventTime ();
  for (TimeValue<AnimEvent *>::TimeValue_t::const_iterator i = events->Begin ();
      i != events->End ();
      ++i)
    {
      AnimEvent * ev = i->second;
      if (ev->m_type == AnimEvent::PACKET_EVENT)
        {
          AnimPacketEvent * packetEvent = static_cast<AnimPacketEvent *> (ev);
          addPacket (packetEvent->m_fbTx, packetEvent->m_fbRx, packetEvent->m_fromId, packetEvent->m_toId);
        }
    }


  /*addPacket (5, 50, 0, 5);
  addPacket (10, 50, 0, 5);
  addPacket (100, 50, 0, 5);
  addPacket (100, 50, 5, 1);*/



}


qreal
PacketsScene::timeToY (qreal t)
{
  return t * (1000/m_maxTime);
}

void
PacketsScene::addPacket (qreal tx, qreal rx, uint32_t fromNodeId, uint32_t toNodeId)
{
  qreal fromNodeX = m_interNodeSpacing * fromNodeId;
  qreal toNodeX = m_interNodeSpacing * toNodeId;
  qreal txY = timeToY (tx);
  qreal rxY = timeToY (rx);
  GraphPacket * graphPacket = new GraphPacket (QPointF (fromNodeX, txY), QPointF (toNodeX, rxY));
  addItem (graphPacket);
  graphPacket->setPos (QPointF (fromNodeX, txY));

}

void
PacketsScene::test ()
{
  NS_LOG_DEBUG ("Packets Scene:" << sceneRect ());
  setUpNodeLines ();
  NS_LOG_DEBUG ("Packets Scene After:" << sceneRect ());

}


}

